import random
import re
import time
from urllib.parse import urljoin

import pandas as pd
import requests
from bs4 import BeautifulSoup


CSV_FILE = "imoveis_zapimoveis.csv"

BASE_URL = "https://www.zapimoveis.com.br/venda/imoveis/"

GRANDE_VITORIA = {
    "vitoria": {
        "url": "es+vitoria/",
        "total_pages": 50,
    },
    "serra": {
        "url": "es+serra/",
        "total_pages": 50,
    },
    "vila-velha": {
        "url": "es+vila-velha/",
        "total_pages": 50,
    },
    "fundao": {
        "url": "es+fundao/",
        "total_pages": 7,
    },
    "viana": {
        "url": "es+viana/",
        "total_pages": 8,
    },
    "guarapari": {
        "url": "es+guarapari/",
        "total_pages": 50,
    },
    "cariacica": {
        "url": "es+cariacica/",
        "total_pages": 24,
    },
}

COLUMN_ORDER = [
    "id",
    "title",
    "price",
    "url",
    "category",
    "real_estate_type",
    "location",
    "municipality",
    "neighbourhood",
    "size",
    "rooms",
    "bathrooms",
    "garage_spaces",
    "condominio",
    "iptu",
    "property_features",
    "condominium_features",
    "seller_name",
    "professional_ad",
    "image_count",
    "first_image",
    "date",
    "raw_text",
]

RESIDENTIAL_TYPES = [
    "apartamento",
    "casa",
    "cobertura",
    "studio",
    "kitnet",
    "sobrado",
]

CITY_NAMES = r"Vitória|Vila Velha|Serra|Cariacica|Guarapari|Viana|Fundão"

HEADERS = {
    "User-Agent": (
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/126.0 Safari/537.36"
    ),
    "Accept-Language": "pt-BR,pt;q=0.9,en;q=0.8",
}


def get_html(url: str) -> str | None:
    """
    Baixa o HTML de uma página do ZAP Imóveis usando requests.

    Args:
        url: URL da página a ser acessada.

    Returns:
        HTML retornado pela requisição, ou None em caso de erro.
    """
    try:
        response = requests.get(url, headers=HEADERS, timeout=20)

        if response.status_code != 200:
            print(f"Erro {response.status_code} em {url}")
            return None

        return response.text

    except requests.RequestException as error:
        print(f"Erro ao acessar {url}: {error}")
        return None


def clean_text(text: str | None) -> str | None:
    """
    Normaliza espaços em um texto extraído do HTML.

    Args:
        text: Texto bruto ou None.

    Returns:
        Texto com espaços normalizados, ou None quando vazio.
    """
    if not text:
        return None
    return " ".join(text.split())


def parse_money(value: str | None) -> int | None:
    """
    Converte uma representação monetária em inteiro.

    Args:
        value: Texto contendo valor monetário.

    Returns:
        Valor numérico inteiro, ou None se não houver dígitos.
    """
    if not value:
        return None

    digits = re.sub(r"\D", "", value)

    if not digits:
        return None

    return int(digits)


def normalize_property_type(property_type: str) -> str:
    """
    Remove acentos específicos usados na padronização do tipo de imóvel.

    Args:
        property_type: Tipo de imóvel extraído.

    Returns:
        Tipo de imóvel normalizado.
    """
    return property_type.replace("ã", "a").replace("á", "a")


def extract_property_type(text: str | None, url: str) -> str | None:
    """
    Identifica o tipo de imóvel a partir do texto do card ou da URL.

    Args:
        text: Texto bruto do card do anúncio.
        url: URL do anúncio.

    Returns:
        Tipo de imóvel normalizado, ou None se não for identificado.
    """
    if not text:
        return None

    normalized_url = url.lower()
    normalized_text = text.lower()

    property_types = [
        "apartamento",
        "casa",
        "cobertura",
        "studio",
        "kitnet",
        "sobrado",
        "terreno",
        "lote",
        "galpao",
        "galpão",
        "loja",
        "sala",
        "fazenda",
        "chácara",
        "chacara",
        "comercial",
    ]

    for property_type in property_types:
        normalized = normalize_property_type(property_type)
        if property_type in normalized_text or normalized in normalized_url:
            return normalized

    return None


def extract_price(text: str | None) -> int | None:
    """
    Extrai o preço do imóvel a partir do texto bruto.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Preço como inteiro, ou None se não for encontrado.
    """
    if not text:
        return None

    match = re.search(r"R\$\s*([\d\.]+)", text)

    if not match:
        return None

    return parse_money(match.group(1))


def extract_area(text: str | None) -> int | None:
    """
    Extrai a área do imóvel em metros quadrados.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Área em m² como inteiro, ou None se não for encontrada.
    """
    if not text:
        return None

    match = re.search(r"Tamanho do imóvel\s*(\d+)\s*m²", text, flags=re.IGNORECASE)

    if not match:
        match = re.search(r"(\d+)\s*m²", text, flags=re.IGNORECASE)

    if not match:
        return None

    return int(match.group(1))


def extract_rooms(text: str | None) -> int | None:
    """
    Extrai a quantidade de quartos do imóvel.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Número de quartos, ou None se não for encontrado.
    """
    if not text:
        return None

    match = re.search(r"Quantidade de quartos\s*(\d+)", text, flags=re.IGNORECASE)

    if not match:
        match = re.search(r"(\d+)\s+quartos?", text, flags=re.IGNORECASE)

    if not match:
        return None

    return int(match.group(1))


def extract_bathrooms(text: str | None) -> int | None:
    """
    Extrai a quantidade de banheiros do imóvel.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Número de banheiros, ou None se não for encontrado.
    """
    if not text:
        return None

    match = re.search(r"Quantidade de banheiros\s*(\d+)", text, flags=re.IGNORECASE)

    if not match:
        match = re.search(r"(\d+)\s+banheiros?", text, flags=re.IGNORECASE)

    if not match:
        return None

    return int(match.group(1))


def extract_garage_spaces(text: str | None) -> int | None:
    """
    Extrai a quantidade de vagas de garagem do imóvel.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Número de vagas, ou None se não for encontrado.
    """
    if not text:
        return None

    match = re.search(
        r"Quantidade de vagas de garagem\s*(\d+)",
        text,
        flags=re.IGNORECASE,
    )

    if not match:
        match = re.search(r"(\d+)\s+vagas?", text, flags=re.IGNORECASE)

    if not match:
        return None

    return int(match.group(1))


def extract_condominio(text: str | None) -> int | None:
    """
    Extrai o valor de condomínio do anúncio.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Valor de condomínio como inteiro, ou None se não for encontrado.
    """
    if not text:
        return None

    match = re.search(r"Cond\.\s*R\$\s*([\d\.]+)", text, flags=re.IGNORECASE)

    if not match:
        return None

    return parse_money(match.group(1))


def extract_iptu(text: str | None) -> int | None:
    """
    Extrai o valor de IPTU do anúncio.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Valor de IPTU como inteiro, ou None se não for encontrado.
    """
    if not text:
        return None

    match = re.search(r"IPTU\s*R\$\s*([\d\.]+)", text, flags=re.IGNORECASE)

    if not match:
        return None

    return parse_money(match.group(1))


def extract_neighbourhood(text: str | None) -> str | None:
    """
    Extrai o bairro informado no texto do anúncio.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Nome do bairro, ou None se não for identificado.
    """
    if not text:
        return None

    match = re.search(
        rf" em ([^,]+),\s*({CITY_NAMES})\b",
        text,
        flags=re.IGNORECASE,
    )

    if not match:
        return None

    return match.group(1).strip()


def extract_municipality(text: str | None) -> str | None:
    """
    Extrai o município informado no texto do anúncio.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Nome do município, ou None se não for identificado.
    """
    if not text:
        return None

    match = re.search(rf",\s*({CITY_NAMES})\b", text, flags=re.IGNORECASE)

    if not match:
        return None

    return match.group(1).strip()


def extract_title(text: str | None) -> str | None:
    """
    Extrai um título aproximado a partir do texto do card.

    Args:
        text: Texto bruto do card do anúncio.

    Returns:
        Título do anúncio, ou None quando o texto estiver vazio.
    """
    if not text:
        return None

    match = re.search(r"(.*?)(?:R\$|Tamanho do imóvel|Quantidade de quartos)", text)

    if not match:
        return text[:120].strip()

    title = match.group(1).strip(" -|,")
    return title or None


def extract_listing_id(url: str) -> str | None:
    """
    Extrai o identificador do anúncio a partir da URL.

    Args:
        url: URL do anúncio.

    Returns:
        Identificador do anúncio, ou None se não for encontrado.
    """
    match = re.search(r"id-([^/?]+)", url)

    if match:
        return match.group(1)

    match = re.search(r"-(\d+)/?$", url)

    if match:
        return match.group(1)

    return None


def build_listing(raw_text: str | None, url: str) -> dict:
    """
    Monta um registro de anúncio com colunas compatíveis com o scraper da OLX.

    Args:
        raw_text: Texto bruto extraído do card do ZAP.
        url: URL do anúncio.

    Returns:
        Dicionário com os dados processados do anúncio.
    """
    real_estate_type = extract_property_type(raw_text, url)
    municipality = extract_municipality(raw_text)
    neighbourhood = extract_neighbourhood(raw_text)

    return {
        "id": extract_listing_id(url),
        "title": extract_title(raw_text),
        "price": extract_price(raw_text),
        "url": url,
        "category": "Imóveis",
        "real_estate_type": real_estate_type,
        "location": ", ".join(
            value for value in [neighbourhood, municipality, "ES"] if value
        ) or None,
        "municipality": municipality,
        "neighbourhood": neighbourhood,
        "size": extract_area(raw_text),
        "rooms": extract_rooms(raw_text),
        "bathrooms": extract_bathrooms(raw_text),
        "garage_spaces": extract_garage_spaces(raw_text),
        "condominio": extract_condominio(raw_text),
        "iptu": extract_iptu(raw_text),
        "property_features": None,
        "condominium_features": None,
        "seller_name": None,
        "professional_ad": None,
        "image_count": None,
        "first_image": None,
        "date": None,
        "raw_text": raw_text,
    }


def extract_listings_from_page(html: str) -> list[dict]:
    """
    Extrai anúncios presentes no HTML renderizado de uma página de resultados.

    Args:
        html: HTML renderizado da página de resultados.

    Returns:
        Lista de anúncios processados encontrados na página.
    """
    soup = BeautifulSoup(html, "html.parser")

    listings = []
    cards = soup.select("a[href*='/imovel/']")
    seen_urls = set()

    for card in cards:
        href = card.get("href")
        if not href:
            continue

        url = urljoin("https://www.zapimoveis.com.br", href)

        if url in seen_urls:
            continue

        seen_urls.add(url)
        raw_text = clean_text(card.get_text(" ", strip=True))
        listings.append(build_listing(raw_text, url))

    return listings


def scrape_city(base_url: str, total_pages: int) -> list[dict]:
    """
    Coleta anúncios de uma cidade em múltiplas páginas do ZAP Imóveis.

    Args:
        base_url: URL base da cidade.
        total_pages: Quantidade máxima de páginas a coletar.

    Returns:
        Lista de anúncios coletados para a cidade.
    """
    city_results = []

    for page in range(1, total_pages + 1):
        if page == 1:
            url = base_url
        else:
            url = f"{base_url}?pagina={page}"

        print(f"Coletando: {url}")

        html = get_html(url)

        if not html:
            continue

        listings = extract_listings_from_page(html)

        if not listings:
            print(f"Nenhum anúncio encontrado na página {page}.")
            break

        print(f"Encontrados: {len(listings)} anúncios")
        city_results.extend(listings)

        time.sleep(random.uniform(2, 5))

    return city_results


def clean_results(dataframe: pd.DataFrame) -> pd.DataFrame:
    """
    Remove duplicados, filtra imóveis residenciais e ordena as colunas finais.

    Args:
        dataframe: DataFrame com os anúncios coletados.

    Returns:
        DataFrame processado e pronto para salvar em CSV.
    """
    if dataframe.empty:
        return pd.DataFrame(columns=COLUMN_ORDER)

    dataframe = dataframe.drop_duplicates(subset=["url"]).copy()

    dataframe = dataframe[dataframe["real_estate_type"].isin(RESIDENTIAL_TYPES)].copy()
    dataframe = dataframe[
        (dataframe["price"].between(50_000, 10_000_000))
        & (dataframe["size"].between(20, 1000))
        & (dataframe["rooms"].notna())
    ].copy()

    for column in COLUMN_ORDER:
        if column not in dataframe.columns:
            dataframe[column] = None

    return dataframe[COLUMN_ORDER]


def main() -> None:
    """Executa a coleta da Grande Vitória e salva o CSV processado."""
    all_results = []

    for city, config in GRANDE_VITORIA.items():
        base_url = f"{BASE_URL}{config['url']}"
        total_pages = config["total_pages"]

        print(f"\nCidade: {city}")
        results = scrape_city(base_url, total_pages=total_pages)
        all_results.extend(results)

    df = pd.DataFrame(all_results)
    df_clean = clean_results(df)

    df_clean.to_csv(CSV_FILE, index=False, encoding="utf-8-sig")

    print(f"\nTotal bruto coletado: {len(df)} anúncios")
    print(f"Total processado salvo: {len(df_clean)} anúncios")
    print(f"CSV salvo em: {CSV_FILE}")
    print(df_clean.head())


if __name__ == "__main__":
    main()

