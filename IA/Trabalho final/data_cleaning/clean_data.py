import re
import time
import unicodedata
from difflib import SequenceMatcher
from pathlib import Path

import pandas as pd


DATASET_DIR = Path("datasets")
OLX_FILE = DATASET_DIR / "imoveis_olx.csv"
ZAP_FILE = DATASET_DIR / "imoveis_zapimoveis.csv"
OUTPUT_FILE = DATASET_DIR / "vendas_grande_vitoria_clean.csv"
REPORT_DIR = DATASET_DIR / "cleaning_reports"

MIN_PRICE = 120_000
MAX_PRICE = 10_000_000
MIN_SIZE = 15
MAX_SIZE = 1_000
MIN_PRICE_M2 = 1_000
MAX_PRICE_M2 = 35_000

# Cidades usadas na coleta.
GRANDE_VITORIA_MUNICIPALITIES = {
    "vitoria",
    "vila velha",
    "serra",
    "cariacica",
    "viana",
    "fundao",
    "guarapari",
}

# O modelo final usa apenas estas categorias.
ALLOWED_PROPERTY_TYPES = ["apartamento", "casa", "cobertura"]

MIN_PRICE_M2_BY_MUNICIPALITY_TYPE = {
    ("vitoria", "apartamento"): 2_500,
    ("vitoria", "cobertura"): 4_500,
    ("vitoria", "casa"): 2_500,
    ("vila velha", "apartamento"): 2_200,
    ("vila velha", "cobertura"): 4_000,
    ("vila velha", "casa"): 2_200,
    ("guarapari", "apartamento"): 2_500,
    ("guarapari", "cobertura"): 4_000,
    ("guarapari", "casa"): 2_200,
    ("serra", "apartamento"): 1_800,
    ("serra", "cobertura"): 2_500,
    ("serra", "casa"): 1_800,
    ("cariacica", "apartamento"): 1_800,
    ("cariacica", "cobertura"): 2_200,
    ("cariacica", "casa"): 1_500,
    ("fundao", "apartamento"): 2_000,
    ("fundao", "cobertura"): 2_500,
    ("fundao", "casa"): 2_000,
    ("viana", "apartamento"): 1_800,
    ("viana", "cobertura"): 2_200,
    ("viana", "casa"): 1_800,
}

BLACKLIST_PATTERN = (
    r"alugo|aluguel|temporada|diária|diaria|troca|troco|repasse|passo|"
    r"lote|terreno|fração|fracao|cota|cortina|máquina|maquina|carro|moto|"
    r"prédio|predio|galpão|galpao|loja|comercial|pousada|hotel"
)

OFF_PLAN_PATTERN = (
    r"na planta|lançamento|lancamento|pré lançamento|pre lancamento|breve lançamento|"
    r"breve lancamento|em construção|em construcao|obra em andamento|entrega prevista|"
    r"previsão de entrega|previsao de entrega|minha casa minha vida|mcmv"
)

STOPWORDS_PATTERN = r"\b(do|da|de|em|com|o|a|os|as|um|uma|para|no|na|nos|nas)\b"

FINAL_COLUMNS = [
    "id",
    "price",
    "real_estate_type",
    "municipality",
    "neighbourhood",
    "size",
    "rooms",
    "bathrooms",
    "garage_spaces",
    "has_condominio",
]

CONDOMINIO_INDICATOR_PATTERN = (
    r"\b(?:condominio|condomínio|cond\.|portaria|porteiro|elevador|predio|prédio|"
    r"edificio|edifício|residencial|lazer|clube|playground|sal[aã]o de festas|"
    r"area de lazer|área de lazer|piscina|churrasqueira)\b"
)
NO_CONDOMINIO_PATTERN = r"\b(?:sem|nao possui|não possui|isento de|nao tem|não tem)\s+(?:condominio|condomínio)\b"

NEIGHBOURHOOD_DESCRIPTION_PATTERN = (
    r"\b(condominio|condomínio|piscina|churrasqueira|elevador|suite|suíte|"
    r"quarto|quartos|vaga|vagas|apartamento|casa|imovel|imóvel|mobiliado|"
    r"mobiliada|vista|lazer|varanda|sacada)\b"
)
NEIGHBOURHOOD_MAX_LENGTH = 60
NEIGHBOURHOOD_MAX_WORDS = 7
FIVE_OR_MORE_COUNT_PATTERN = r"^\s*5\s+ou\s+mais\s*$"
HOUSE_TITLE_PATTERN = r"\b(?:casa|sobrado)\b"
APARTMENT_TITLE_PATTERN = r"\b(?:apartamento|apto|apt|kitnet|quitinete|studio|loft)\b"
PENTHOUSE_TITLE_PATTERN = r"\b(?:cobertura|penthouse)\b"


def log_step(name: str, start_time: float, timings: dict[str, float]) -> float:
    timings[name] = time.time() - start_time
    return time.time()


def read_source(path: Path, source: str) -> pd.DataFrame:
    if not path.exists():
        print(f"Aviso: arquivo não encontrado: {path}")
        return pd.DataFrame()

    df = pd.read_csv(path, low_memory=False)
    df["source"] = source
    df["source_id"] = source + ":" + df.get("id", "").astype(str)
    print(f"- {source}: {len(df)} anúncios carregados de {path}")
    return df


def ensure_columns(df: pd.DataFrame, columns: list[str]) -> pd.DataFrame:
    for column in columns:
        if column not in df.columns:
            df[column] = pd.NA
    return df


def normalize_text(value: object) -> str:
    if pd.isna(value):
        return ""

    text = str(value).lower().strip()
    text = unicodedata.normalize("NFKD", text)
    text = "".join(char for char in text if not unicodedata.combining(char))
    text = re.sub(r"[^\w\s]", " ", text, flags=re.UNICODE)
    text = re.sub(STOPWORDS_PATTERN, " ", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


def normalize_municipality(value: object) -> str:
    if pd.isna(value):
        return ""

    text = str(value).lower().strip()
    text = unicodedata.normalize("NFKD", text)
    text = "".join(char for char in text if not unicodedata.combining(char))
    text = re.sub(r"[^\w\s]", " ", text, flags=re.UNICODE)
    text = re.sub(r"\s+", " ", text).strip()
    return text


def municipality_to_label(value: str) -> str:
    mapping = {
        "vitoria": "Vitória",
        "vila velha": "Vila Velha",
        "serra": "Serra",
        "cariacica": "Cariacica",
        "viana": "Viana",
        "fundao": "Fundão",
        "guarapari": "Guarapari",
    }
    return mapping.get(value, value.title())


def extract_grande_vitoria_municipality(value: object) -> str:
    text = normalize_municipality(value)
    if not text:
        return ""

    for municipality in sorted(GRANDE_VITORIA_MUNICIPALITIES, key=len, reverse=True):
        if re.search(rf"\b{re.escape(municipality)}\b", text):
            return municipality

    return text


def parse_money(series: pd.Series) -> pd.Series:
    if pd.api.types.is_numeric_dtype(series):
        return pd.to_numeric(series, errors="coerce")

    cleaned = series.astype(str).str.replace(r"\D", "", regex=True)
    cleaned = cleaned.replace("", pd.NA)
    return pd.to_numeric(cleaned, errors="coerce")


def parse_measure(series: pd.Series) -> pd.Series:
    if pd.api.types.is_numeric_dtype(series):
        return pd.to_numeric(series, errors="coerce")

    extracted = series.astype(str).str.extract(r"(\d+(?:[\.,]\d+)?)", expand=False)
    extracted = extracted.str.replace(",", ".", regex=False)
    return pd.to_numeric(extracted, errors="coerce")


def parse_count(series: pd.Series) -> pd.Series:
    if pd.api.types.is_numeric_dtype(series):
        return pd.to_numeric(series, errors="coerce")

    text = series.fillna("").astype(str)
    extracted = text.str.extract(r"(\d+)", expand=False)
    parsed = pd.to_numeric(extracted, errors="coerce")
    parsed = parsed.mask(has_five_or_more_count(series))
    return parsed


def has_five_or_more_count(series: pd.Series) -> pd.Series:
    if pd.api.types.is_numeric_dtype(series):
        return pd.Series(False, index=series.index)

    return series.fillna("").astype(str).str.contains(
        FIVE_OR_MORE_COUNT_PATTERN,
        case=False,
        regex=True,
    )


def standardize_property_type(value: object) -> str:
    """
    Padroniza o tipo do imóvel para as categorias finais do modelo.

    Regras:
    - casa e sobrado são agrupados como casa;
    - apartamento, kitnet, quitinete, studio e loft são agrupados como apartamento;
    - cobertura fica separada.
    """
    text = normalize_text(value)

    if not text:
        return ""

    if "cobertura" in text:
        return "cobertura"

    if "sobrado" in text or "casa" in text:
        return "casa"

    if any(alias in text for alias in ["apartamento", "apto", "kitnet", "quitinete", "studio", "loft"]):
        return "apartamento"

    return ""


def infer_property_type_from_title(value: object) -> str:
    text = normalize_text(value)

    if not text:
        return ""

    if re.search(PENTHOUSE_TITLE_PATTERN, text):
        return "cobertura"

    has_house = bool(re.search(HOUSE_TITLE_PATTERN, text))
    has_apartment = bool(re.search(APARTMENT_TITLE_PATTERN, text))

    if has_house and not has_apartment:
        return "casa"

    if has_apartment and not has_house:
        return "apartamento"

    return ""


def minimum_price_m2_for_row(row: pd.Series) -> float:
    key = (
        normalize_municipality(row.get("municipality_key", "")),
        str(row.get("real_estate_type", "")).lower().strip(),
    )
    return float(MIN_PRICE_M2_BY_MUNICIPALITY_TYPE.get(key, MIN_PRICE_M2))


def clean_title(series: pd.Series) -> pd.Series:
    cleaned = series.fillna("").astype(str)
    cleaned = cleaned.str.replace(r"^\+\s*\d+\s*fotos?\s*", "", regex=True, case=False)
    cleaned = cleaned.str.replace(
        r"\b(super destaque|destaque|festival da mudança)\b",
        "",
        regex=True,
        case=False,
    )
    cleaned = cleaned.str.replace(r"\s+", " ", regex=True).str.strip(" -|,")
    return cleaned.replace("", pd.NA)


def compact_text(value: object) -> str:
    return normalize_text(value).replace(" ", "")


def normalize_output_label(value: object) -> str:
    if pd.isna(value):
        return "nao informado"

    text = str(value).lower().strip()
    text = unicodedata.normalize("NFKD", text)
    text = "".join(char for char in text if not unicodedata.combining(char))
    text = re.sub(r"\s+", " ", text).strip()
    return text or "nao informado"


def clean_neighbourhood(value: object) -> str:
    if pd.isna(value):
        return "Não informado"

    text = re.sub(r"\s+", " ", str(value)).strip(" -|,")
    if not text:
        return "Não informado"

    normalized = normalize_municipality(text)

    # Alguns anúncios trazem descrição no campo de bairro, mas deixam o bairro real no final.
    # Ex.: "condomínio com piscina e churrasqueira em Jardim Limoeiro".
    if re.search(NEIGHBOURHOOD_DESCRIPTION_PATTERN, normalized, flags=re.IGNORECASE):
        match = re.search(r"\bem\s+(.+)$", text, flags=re.IGNORECASE)
        if match:
            candidate = re.sub(r"\s+", " ", match.group(1)).strip(" -|,")
            if candidate:
                return candidate

    return text


def is_invalid_neighbourhood(value: object) -> bool:
    if pd.isna(value):
        return False

    text = re.sub(r"\s+", " ", str(value)).strip()
    normalized = normalize_municipality(text)

    if not normalized or normalized == "nao informado":
        return False

    if len(text) > NEIGHBOURHOOD_MAX_LENGTH or len(normalized.split()) > NEIGHBOURHOOD_MAX_WORDS:
        return True

    has_description_term = re.search(
        NEIGHBOURHOOD_DESCRIPTION_PATTERN,
        normalized,
        flags=re.IGNORECASE,
    )
    has_phrase_connector = re.search(r"\b(com|em)\b", normalized)

    return bool(has_description_term and has_phrase_connector)


def parse_dates(series: pd.Series) -> pd.Series:
    numeric = pd.to_numeric(series, errors="coerce")
    parsed = pd.to_datetime(numeric, unit="s", errors="coerce")
    fallback = pd.to_datetime(series, errors="coerce")
    parsed = parsed.fillna(fallback)
    return parsed.dt.date


def load_data() -> pd.DataFrame:
    frames = [read_source(OLX_FILE, "olx"), read_source(ZAP_FILE, "zapimoveis")]
    frames = [frame for frame in frames if not frame.empty]

    if not frames:
        return pd.DataFrame()

    return pd.concat(frames, ignore_index=True, sort=False)


def standardize_data(df: pd.DataFrame) -> pd.DataFrame:
    expected_columns = [
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
        "seller_name",
        "date",
        "raw_text",
        "source",
        "source_id",
    ]

    df = ensure_columns(df.copy(), expected_columns)

    df["id"] = df["id"].astype(str).replace({"nan": pd.NA, "None": pd.NA})
    df["title"] = clean_title(df["title"])
    df["price"] = parse_money(df["price"])
    df["size"] = parse_measure(df["size"])
    df["has_five_or_more_count"] = (
        has_five_or_more_count(df["rooms"])
        | has_five_or_more_count(df["bathrooms"])
        | has_five_or_more_count(df["garage_spaces"])
    )
    df["rooms"] = parse_count(df["rooms"])
    df["bathrooms"] = parse_count(df["bathrooms"])
    df["garage_spaces"] = parse_count(df["garage_spaces"]).fillna(0)
    df["condominio"] = parse_money(df["condominio"]).fillna(0)
    df["date"] = parse_dates(df["date"])

    for column in ["category", "real_estate_type", "location", "municipality", "neighbourhood"]:
        df[column] = df[column].fillna("").astype(str).str.strip().replace("", pd.NA)

    type_from_listing = (
        df["category"].fillna("").astype(str)
        + " "
        + df["real_estate_type"].fillna("").astype(str)
    ).apply(standardize_property_type)
    type_from_title = df["title"].apply(infer_property_type_from_title)

    df["property_type_from_listing"] = type_from_listing.replace("", pd.NA)
    df["property_type_from_title"] = type_from_title.replace("", pd.NA)
    df["property_type_conflict"] = (
        df["property_type_from_title"].notna()
        & df["property_type_from_listing"].notna()
        & (df["property_type_from_title"] != df["property_type_from_listing"])
    )

    keep_listing_penthouse = type_from_listing.eq("cobertura") & type_from_title.eq("apartamento")
    resolved_type = type_from_title.where(type_from_title.ne(""), type_from_listing)
    resolved_type = resolved_type.mask(keep_listing_penthouse, "cobertura")

    df["property_type_resolution"] = "listing"
    df.loc[type_from_title.ne(""), "property_type_resolution"] = "title"
    df.loc[keep_listing_penthouse, "property_type_resolution"] = "listing_cobertura"
    df.loc[type_from_listing.eq("") & type_from_title.eq(""), "property_type_resolution"] = "unresolved"
    df["real_estate_type"] = resolved_type.replace("", pd.NA)

    type_conflicts = df[df["property_type_conflict"]].copy()
    if not type_conflicts.empty:
        save_report(type_conflicts, "conflitos_tipo_titulo.csv")

    municipality_from_column = df["municipality"].apply(extract_grande_vitoria_municipality)
    municipality_from_location = df["location"].apply(extract_grande_vitoria_municipality)

    df["municipality_key"] = municipality_from_column.where(
        municipality_from_column.isin(GRANDE_VITORIA_MUNICIPALITIES),
        municipality_from_location,
    )

    df["municipality"] = df["municipality_key"].apply(municipality_to_label)
    df["neighbourhood"] = (
        df["neighbourhood"]
        .fillna("Não informado")
        .apply(clean_neighbourhood)
        .astype(str)
        .str.strip()
    )

    df["title_key"] = df["title"].apply(compact_text)
    df["title_words_key"] = df["title"].apply(normalize_text)
    df["neighbourhood_key"] = df["neighbourhood"].apply(normalize_text)

    return df


def save_report(df: pd.DataFrame, filename: str) -> None:
    if df.empty:
        return

    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    df.to_csv(REPORT_DIR / filename, index=False, encoding="utf-8-sig")


def remove_empty_and_exact_duplicates(df: pd.DataFrame) -> pd.DataFrame:
    initial = len(df)

    missing_required = df[df[["id", "price", "title"]].isna().any(axis=1)].copy()
    df = df.dropna(subset=["id", "price", "title"]).copy()
    print(f"- {initial - len(df)} linhas sem id, preço ou título removidas")
    save_report(missing_required, "linhas_sem_campos_essenciais.csv")

    before = len(df)
    duplicated_id = df[df.duplicated(subset=["source", "id"], keep="first")].copy()
    df = df.drop_duplicates(subset=["source", "id"], keep="first").copy()
    print(f"- {before - len(df)} duplicatas por source + id removidas")
    save_report(duplicated_id, "duplicatas_source_id.csv")

    before = len(df)
    duplicated_url = df[df["url"].notna() & df.duplicated(subset=["url"], keep="first")].copy()

    df_with_url = df[df["url"].notna()].drop_duplicates(subset=["url"], keep="first").copy()
    df_without_url = df[df["url"].isna()].copy()
    df = pd.concat([df_with_url, df_without_url], ignore_index=True)

    print(f"- {before - len(df)} duplicatas por URL removidas")
    save_report(duplicated_url, "duplicatas_url.csv")

    return df


def apply_quality_filters(df: pd.DataFrame) -> pd.DataFrame:
    removed_frames = []

    def apply_filter(mask: pd.Series, label: str, filename: str) -> None:
        nonlocal df
        removed = df[~mask].copy()
        removed_frames.append(removed.assign(removal_reason=label))
        before = len(df)
        df = df[mask].copy()
        print(f"- {before - len(df)} linhas removidas: {label}")
        save_report(removed, filename)

    apply_filter(df["price"].between(MIN_PRICE, MAX_PRICE), "preço fora da faixa", "precos_removidos.csv")
    apply_filter(df["size"].between(MIN_SIZE, MAX_SIZE), "área fora da faixa", "areas_removidas.csv")
    apply_filter(
        df["municipality_key"].isin(GRANDE_VITORIA_MUNICIPALITIES),
        "município fora da região de interesse",
        "municipios_fora_regiao.csv",
    )

    neighbourhood_ok = ~df["neighbourhood"].apply(is_invalid_neighbourhood)
    apply_filter(neighbourhood_ok, "bairro com texto descritivo", "bairros_invalidos.csv")

    title_blacklist = df["title"].fillna("").astype(str).str.contains(
        BLACKLIST_PATTERN,
        case=False,
        regex=True,
    )
    apply_filter(~title_blacklist, "palavras proibidas no título", "blacklist_titulo.csv")

    title_ok = df["title"].fillna("").astype(str).str.strip().str.len() >= 5
    apply_filter(title_ok, "título curto ou vazio", "titulos_invalidos.csv")

    off_plan_text = (
        df["title"].fillna("").astype(str)
        + " "
        + df["raw_text"].fillna("").astype(str)
    )
    off_plan = off_plan_text.str.contains(OFF_PLAN_PATTERN, case=False, regex=True)
    apply_filter(~off_plan, "imóvel na planta ou lançamento", "imoveis_na_planta.csv")

    residential = df["real_estate_type"].isin(ALLOWED_PROPERTY_TYPES)
    apply_filter(residential, "tipo não residencial", "tipos_nao_residenciais.csv")

    five_or_more_ok = ~df["has_five_or_more_count"].fillna(False)
    apply_filter(five_or_more_ok, '"5 ou mais" em quartos, banheiros ou vagas', "cinco_ou_mais_comodos.csv")

    df["rooms"] = pd.to_numeric(df["rooms"], errors="coerce").fillna(0).astype(int)
    df["bathrooms"] = pd.to_numeric(df["bathrooms"], errors="coerce").fillna(0).astype(int)
    df["garage_spaces"] = pd.to_numeric(df["garage_spaces"], errors="coerce").fillna(0).astype(int)
    df["condominio"] = pd.to_numeric(df["condominio"], errors="coerce").fillna(0)

    rooms_ok = (df["rooms"] > 0) & (df["bathrooms"] > 0) & (df["garage_spaces"] >= 0)
    apply_filter(rooms_ok, "cômodos inválidos", "comodos_invalidos.csv")

    size_per_room = df["size"] / df["rooms"].replace(0, 1)
    size_per_room_bath = df["size"] / (df["rooms"] + df["bathrooms"]).replace(0, 1)

    apartment_too_many_rooms = (
        df["real_estate_type"].eq("apartamento")
        & (df["size"] < 60)
        & (df["rooms"] >= 4)
    )
    rooms_too_dense = size_per_room < 12
    bathrooms_too_many = df["bathrooms"] > (df["rooms"] + 2)
    garages_too_many = df["garage_spaces"] > (df["rooms"] + 2)
    rooms_bathrooms_too_dense = size_per_room_bath < 5

    df["physical_filter_reason"] = pd.NA
    df.loc[apartment_too_many_rooms, "physical_filter_reason"] = "apartamento pequeno com quartos demais"
    df.loc[rooms_too_dense, "physical_filter_reason"] = "área por quarto muito baixa"
    df.loc[bathrooms_too_many, "physical_filter_reason"] = "banheiros demais para a quantidade de quartos"
    df.loc[garages_too_many, "physical_filter_reason"] = "vagas demais para a quantidade de quartos"
    df.loc[rooms_bathrooms_too_dense, "physical_filter_reason"] = "área por quartos e banheiros muito baixa"

    physical_ok = df["physical_filter_reason"].isna()
    apply_filter(physical_ok, "anomalia física", "anomalias_fisicas.csv")

    df["price_m2"] = df["price"] / df["size"]
    df["min_price_m2_contextual"] = df.apply(minimum_price_m2_for_row, axis=1)
    price_m2_ok = (df["price_m2"] >= df["min_price_m2_contextual"]) & (df["price_m2"] <= MAX_PRICE_M2)
    df["price_m2_filter_reason"] = pd.NA
    df.loc[df["price_m2"] < df["min_price_m2_contextual"], "price_m2_filter_reason"] = "abaixo do mínimo contextual"
    df.loc[df["price_m2"] > MAX_PRICE_M2, "price_m2_filter_reason"] = "acima do máximo global"
    apply_filter(price_m2_ok, "preço por m² fora da faixa contextual", "anomalias_preco_m2.csv")

    if removed_frames:
        save_report(pd.concat(removed_frames, ignore_index=True), "todos_removidos.csv")

    return df


def find_duplicate_pairs(df: pd.DataFrame) -> list[tuple[int, int, float]]:
    pairs: list[tuple[int, int, float]] = []
    work = df.copy()
    work["price_bin"] = (work["price"] / 50_000).round().astype("Int64")

    block_cols = [
        "municipality_key",
        "neighbourhood_key",
        "size",
        "rooms",
        "bathrooms",
        "garage_spaces",
        "price_bin",
    ]

    for _, group in work.groupby(block_cols, dropna=False):
        if len(group) < 2 or len(group) > 200:
            continue

        indices = group.index.tolist()
        for left_pos, idx1 in enumerate(indices):
            row1 = group.loc[idx1]

            for idx2 in indices[left_pos + 1:]:
                row2 = group.loc[idx2]
                max_price = max(row1["price"], row2["price"])

                if pd.isna(max_price) or max_price <= 0:
                    continue

                price_diff = abs(row1["price"] - row2["price"]) / max_price
                if price_diff > 0.05:
                    continue

                similarity = SequenceMatcher(
                    None,
                    row1["title_words_key"],
                    row2["title_words_key"],
                ).ratio()

                threshold = 0.60 if row1["source"] != row2["source"] else 0.85

                if similarity >= threshold:
                    pairs.append((idx1, idx2, similarity))

    return pairs


def build_components(pairs: list[tuple[int, int, float]]) -> list[set[int]]:
    parent: dict[int, int] = {}

    def find(item: int) -> int:
        parent.setdefault(item, item)
        if parent[item] != item:
            parent[item] = find(parent[item])
        return parent[item]

    def union(left: int, right: int) -> None:
        root_left = find(left)
        root_right = find(right)
        if root_left != root_right:
            parent[root_right] = root_left

    for idx1, idx2, _ in pairs:
        union(idx1, idx2)

    components: dict[int, set[int]] = {}
    for item in parent:
        components.setdefault(find(item), set()).add(item)

    return [component for component in components.values() if len(component) > 1]


def completeness_score(row: pd.Series) -> int:
    relevant_columns = [
        "title",
        "price",
        "real_estate_type",
        "location",
        "municipality",
        "neighbourhood",
        "size",
        "rooms",
        "bathrooms",
        "garage_spaces",
        "condominio",
        "date",
    ]
    return int(row[relevant_columns].notna().sum())


def merge_duplicate_components(
    df: pd.DataFrame,
    components: list[set[int]],
    label: str,
    report_filename: str,
) -> pd.DataFrame:
    if not components:
        print(f"- 0 {label} encontradas")
        return df

    df = df.copy()
    indices_to_drop: set[int] = set()
    audit_rows = []

    for component in components:
        component_df = df.loc[list(component)].copy()
        keep_idx = component_df.apply(completeness_score, axis=1).sort_values(ascending=False).index[0]
        duplicate_indices = [idx for idx in component if idx != keep_idx]

        for duplicate_idx in duplicate_indices:
            for column in df.columns:
                keep_value = df.at[keep_idx, column]
                duplicate_value = df.at[duplicate_idx, column]
                if (pd.isna(keep_value) or keep_value == "") and pd.notna(duplicate_value):
                    df.at[keep_idx, column] = duplicate_value

            indices_to_drop.add(duplicate_idx)
            audit_rows.append(
                {
                    "kept_index": keep_idx,
                    "removed_index": duplicate_idx,
                    "kept_title": df.at[keep_idx, "title"],
                    "removed_title": df.at[duplicate_idx, "title"],
                    "price": df.at[keep_idx, "price"],
                    "size": df.at[keep_idx, "size"],
                    "municipality": df.at[keep_idx, "municipality"],
                    "neighbourhood": df.at[keep_idx, "neighbourhood"],
                }
            )

    if audit_rows:
        save_report(pd.DataFrame(audit_rows), report_filename)

    print(f"- {len(indices_to_drop)} {label} consolidadas")
    return df.drop(index=list(indices_to_drop)).copy()


def deduplicate_properties(df: pd.DataFrame) -> pd.DataFrame:
    strict_cols = [
        "title_key",
        "price",
        "size",
        "rooms",
        "bathrooms",
        "garage_spaces",
        "neighbourhood_key",
    ]

    strict_components = [
        set(group.index)
        for _, group in df.groupby(strict_cols, dropna=False)
        if len(group) > 1
    ]

    df = merge_duplicate_components(
        df,
        strict_components,
        label="duplicatas estritas por características",
        report_filename="duplicatas_estritas.csv",
    )

    pairs = find_duplicate_pairs(df)
    components = build_components(pairs)

    return merge_duplicate_components(
        df,
        components,
        label="duplicatas fuzzy/entre fontes",
        report_filename="duplicatas_consolidadas.csv",
    )


def eliminate_suspects(df: pd.DataFrame) -> pd.DataFrame:
    suspects = [
        "Adalton Ferreira Da Silva",
        "Gustavo Silveira Da Silva",
        "Izabel da Silva Paula",
        "Evelin",
        "Carpe Diem Serviços Especiais Lt",
        "Saulo Luciano",
        "Araujo Imóveis",
        "Claudianaferreira771",
        "karlosalexsandro",
        "Afonso Neto",
        "Mikaella#",
    ]
    before = len(df)
    df = df[~df["seller_name"].isin(suspects)].copy()
    print(f"- {before - len(df)} anúncios de vendedores suspeitos removidos")
    return df


def add_model_features(df: pd.DataFrame) -> pd.DataFrame:
    df = df.copy()

    title_text = (
        df["title"].fillna("").astype(str)
        + " "
        + df["raw_text"].fillna("").astype(str)
    )

    condominio_informado = pd.to_numeric(df["condominio"], errors="coerce").fillna(0) > 0
    tipo_normalizado = df["real_estate_type"].fillna("").astype(str).str.lower().str.strip()
    tipo_indica_condominio = tipo_normalizado.isin(["apartamento", "cobertura"])
    texto_indica_condominio = title_text.str.contains(
        CONDOMINIO_INDICATOR_PATTERN,
        case=False,
        regex=True,
    ) & ~title_text.str.contains(
        NO_CONDOMINIO_PATTERN,
        case=False,
        regex=True,
    )

    df["has_condominio"] = (
        condominio_informado
        | tipo_indica_condominio
        | texto_indica_condominio
    ).astype(int)

    return df


def finalize_dataset(df: pd.DataFrame) -> pd.DataFrame:
    df = df.copy()

    # Mantém apenas as colunas necessárias para o treinamento final.
    df = df[FINAL_COLUMNS].copy()

    numeric_columns = [
        "price",
        "size",
        "rooms",
        "bathrooms",
        "garage_spaces",
        "has_condominio",
    ]

    for column in numeric_columns:
        df[column] = pd.to_numeric(df[column], errors="coerce")

    for column in ["real_estate_type", "municipality", "neighbourhood"]:
        df[column] = df[column].apply(normalize_output_label)

    df["rooms"] = df["rooms"].astype("Int64")
    df["bathrooms"] = df["bathrooms"].astype("Int64")
    df["garage_spaces"] = df["garage_spaces"].astype("Int64")
    df["has_condominio"] = df["has_condominio"].fillna(0).astype("Int64")

    return df.sort_values(by=["municipality", "neighbourhood", "real_estate_type"], na_position="last")


def main() -> None:
    start_total = time.time()
    timings: dict[str, float] = {}
    step_start = start_total

    print("Iniciando o processamento de dados...")
    REPORT_DIR.mkdir(parents=True, exist_ok=True)

    df = load_data()
    if df.empty:
        print("Nenhum dado encontrado para processar.")
        return

    print(f"Total inicial de linhas carregadas: {len(df)}")
    step_start = log_step("Carga de dados", step_start, timings)

    df = standardize_data(df)
    step_start = log_step("Padronização", step_start, timings)

    df = remove_empty_and_exact_duplicates(df)
    step_start = log_step("Remoção de lixo estrutural", step_start, timings)

    df = apply_quality_filters(df)
    step_start = log_step("Filtros de qualidade", step_start, timings)

    df = deduplicate_properties(df)
    step_start = log_step("Deduplicação entre fontes", step_start, timings)

    df = eliminate_suspects(df)
    step_start = log_step("Eliminação de suspeitos", step_start, timings)

    df = add_model_features(df)
    df = finalize_dataset(df)
    step_start = log_step("Engenharia e finalização", step_start, timings)

    OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    df.to_csv(OUTPUT_FILE, index=False, encoding="utf-8-sig")

    print("\n--- RESUMO FINAL ---")
    print(f"Total de linhas remanescentes: {len(df)}")
    print(f"Shape final: {df.shape}")
    print(f"Arquivo salvo em: {OUTPUT_FILE}")
    print(f"Relatórios salvos em: {REPORT_DIR}")

    print("\n--- DISTRIBUIÇÃO FINAL ---")
    print(df["real_estate_type"].value_counts(dropna=False))
    print(df["municipality"].value_counts(dropna=False))

    print("\n--- RELATÓRIO DE TEMPO DE EXECUÇÃO ---")
    for step, seconds in timings.items():
        print(f"[{seconds:05.2f}s] {step}")
    print(f"[{time.time() - start_total:05.2f}s] TEMPO TOTAL")


if __name__ == "__main__":
    main()
