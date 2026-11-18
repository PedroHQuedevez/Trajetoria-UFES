import json
from typing import Any

import pandas as pd
from playwright.sync_api import Page, TimeoutError as PlaywrightTimeoutError
from playwright.sync_api import sync_playwright


CSV_FILE = "imoveis_olx.csv"

BASE_URL = "https://www.olx.com.br/imoveis/venda/"

GRANDE_VITORIA = {
    "vitoria": {
        "url": "estado-es/norte-do-espirito-santo/vitoria",
        "total_pages": 100
    },
    "serra": {
        "url": "estado-es/norte-do-espirito-santo/outras-cidades/serra",
        "total_pages": 100
    },
    "vila-velha": {
        "url": "estado-es/norte-do-espirito-santo/vila-velha",
        "total_pages": 100
    },
    "fundao": {
        "url": "estado-es/norte-do-espirito-santo/outras-cidades/fundao",
        "total_pages": 2
    },
    "viana": {
        "url": "estado-es/norte-do-espirito-santo/outras-cidades/viana",
        "total_pages": 8
    },
    "guarapari": {
        "url": "estado-es/norte-do-espirito-santo/guarapari-e-regiao/guarapari",
        "total_pages": 100
    },
    "cariacica": {
        "url": "estado-es/norte-do-espirito-santo/outras-cidades/cariacica",
        "total_pages": 31
    }
}

AdItem = dict[str, Any]


def get_property(properties: list[dict[str, Any]], name: str) -> Any | None:
    """
    Busca uma propriedade específica dentro da lista de propriedades do anúncio.

    Args:
        properties: Lista de propriedades retornadas pela OLX.
        name: Nome da propriedade desejada.

    Returns:
        Valor da propriedade caso exista, caso contrário None.
    """
    for prop in properties:
        if prop.get("name") == name:
            return prop.get("value")

    return None


def extract_ads_from_page(page: Page, url: str) -> list[AdItem]:
    """
    Coleta todos os anúncios presentes em uma página de resultados da OLX.

    Args:
        page: Instância da página do Playwright.
        url: URL da página a ser processada.

    Returns:
        Lista contendo os anúncios encontrados.
    """
    try:
        page.goto(url, wait_until="domcontentloaded", timeout=60_000)

    except PlaywrightTimeoutError:
        print(f"Timeout em {url}. Tentando extrair os dados mesmo assim...")

    page.wait_for_timeout(5_000)

    next_data = page.locator("#__NEXT_DATA__").text_content()

    if not next_data:
        print(f"Sem __NEXT_DATA__: {url}")
        return []

    html = json.loads(next_data)
    ads = html.get("props", {}).get("pageProps", {}).get("ads", [])

    items: list[AdItem] = []

    for ad in ads:
        properties = ad.get("properties") or []
        location_details = ad.get("locationDetails") or {}
        olx_pay = ad.get("olxPay") or {}
        images = ad.get("images") or []

        list_id = ad.get("listId")

        item: AdItem = {
            "id": str(list_id) if list_id is not None else None,
            "title": ad.get("subject"),
            "price": ad.get("price") or ad.get("priceValue"),
            "url": ad.get("url"),
            "category": ad.get("category") or ad.get("categoryName"),
            "real_estate_type": get_property(properties, "real_estate_type"),
            "location": ad.get("location"),
            "municipality": location_details.get("municipality"),
            "neighbourhood": location_details.get("neighbourhood"),
            "size": get_property(properties, "size"),
            "rooms": get_property(properties, "rooms"),
            "bathrooms": get_property(properties, "bathrooms"),
            "garage_spaces": get_property(properties, "garage_spaces"),
            "condominio": get_property(properties, "condominio"),
            "iptu": get_property(properties, "iptu"),
            "property_features": get_property(properties, "re_features"),
            "condominium_features": get_property(
                properties,
                "re_complex_features",
            ),
            "seller_name": olx_pay.get("transactionalSellerName"),
            "professional_ad": ad.get("professionalAd"),
            "image_count": ad.get("imageCount") or len(images),
            "first_image": images[0].get("original") if images else None,
            "date": ad.get("date"),
        }

        items.append(item)

    return items


def save_results(items: list[AdItem]) -> None:
    """
    Salva os anúncios coletados em CSV.

    Args:
        items: Lista de anúncios coletados.
    """
    dataframe = pd.DataFrame(items)
    dataframe.to_csv(CSV_FILE, index=False, encoding="utf-8-sig")


def main() -> None:
    all_items: list[AdItem] = []

    with sync_playwright() as playwright:
        browser = playwright.chromium.launch(headless=False)
        page = browser.new_page()

        for city, config in GRANDE_VITORIA.items():
            city_url = config["url"]
            total_pages = config["total_pages"]

            for page_number in range(1, total_pages + 1):
                url = f"{BASE_URL}{city_url}?o={page_number}"

                print(f"Coletando {city} - página {page_number}: {url}")

                items = extract_ads_from_page(page, url)

                print(f"Encontrados: {len(items)} anúncios")

                all_items.extend(items)

        browser.close()

    save_results(all_items)

    print(f"\nTotal coletado: {len(all_items)} anúncios")
    print(f"CSV salvo em: {CSV_FILE}")


if __name__ == "__main__":
    main()


