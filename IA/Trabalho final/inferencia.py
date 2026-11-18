import json
import re
import sys
import unicodedata
from pathlib import Path

import joblib
import pandas as pd


INPUT_FILE = Path("entrada.csv")
OUTPUT_FILE = Path("resultado.csv")
MODEL_FILE = Path("modelo_final_imoveis.joblib")
METADATA_FILE = Path("metadata_modelo_final_imoveis.json")

DEFAULT_METADATA = {
    "raw_features": [
        "real_estate_type",
        "municipality",
        "neighbourhood",
        "size",
        "rooms",
        "bathrooms",
        "garage_spaces",
        "has_condominio",
    ],
    "categorical_features": [
        "real_estate_type",
        "municipality",
        "neighbourhood",
    ],
    "numeric_features": [
        "size",
        "rooms",
        "bathrooms",
        "garage_spaces",
        "has_condominio",
    ],
}

CONDOMINIO_INDICATOR_PATTERN = (
    r"\b(condominio|condomínio|cond\.|portaria|porteiro|elevador|predio|prédio|"
    r"edificio|edifício|residencial|lazer|clube|playground|sal[aã]o de festas|"
    r"area de lazer|área de lazer|piscina|churrasqueira)\b"
)


def normalize_label(value: object) -> str:
    """Normaliza um valor textual para o mesmo padrão usado no treinamento."""
    if pd.isna(value):
        return "nao informado"

    text = str(value).lower().strip()
    text = unicodedata.normalize("NFKD", text)
    text = "".join(char for char in text if not unicodedata.combining(char))
    text = re.sub(r"\s+", " ", text).strip()
    return text or "nao informado"


def infer_has_condominio(samples: pd.DataFrame) -> pd.Series:
    """Infere a feature `has_condominio` a partir do tipo, valor e textos do anúncio."""
    condominio = pd.Series(0, index=samples.index)
    if "condominio" in samples.columns:
        condominio = pd.to_numeric(samples["condominio"], errors="coerce").fillna(0)

    real_estate_type = pd.Series("", index=samples.index)
    if "real_estate_type" in samples.columns:
        real_estate_type = samples["real_estate_type"].fillna("").astype(str).map(normalize_label)

    text = pd.Series("", index=samples.index)
    for column in ["title", "raw_text", "description"]:
        if column in samples.columns:
            text = text + " " + samples[column].fillna("").astype(str)

    return (
        (condominio > 0)
        | real_estate_type.isin(["apartamento", "cobertura"])
        | text.str.contains(CONDOMINIO_INDICATOR_PATTERN, case=False, regex=True)
    ).astype(int)


def load_metadata_from_json() -> dict:
    """Carrega os metadados do modelo quando o arquivo JSON está disponível."""
    if not METADATA_FILE.exists():
        return {}

    with open(METADATA_FILE, "r", encoding="utf-8") as file:
        return json.load(file)


def load_solution() -> tuple[object, dict]:
    """Carrega o modelo treinado e os metadados necessários para inferência."""
    if not MODEL_FILE.exists():
        raise FileNotFoundError(f"Arquivo do modelo não encontrado: {MODEL_FILE}")

    loaded = joblib.load(MODEL_FILE)
    metadata = load_metadata_from_json()

    if isinstance(loaded, dict) and "model" in loaded:
        model = loaded["model"]
        metadata = {**metadata, **loaded}
    else:
        model = loaded

    for key, value in DEFAULT_METADATA.items():
        metadata.setdefault(key, value)

    missing_keys = [
        key
        for key in ["raw_features", "categorical_features", "numeric_features"]
        if key not in metadata
    ]
    if missing_keys:
        raise ValueError(f"Metadados ausentes: {missing_keys}")

    return model, metadata


def prepare_new_samples(samples: pd.DataFrame, metadata: dict) -> pd.DataFrame:
    """Prepara as amostras de entrada com as mesmas features usadas no treinamento."""
    samples = samples.copy()

    if (
        "has_condominio" in metadata["numeric_features"]
        or "has_condominio" in metadata["categorical_features"]
    ):
        inferred_has_condominio = infer_has_condominio(samples)

        if "has_condominio" not in samples.columns:
            samples["has_condominio"] = inferred_has_condominio
        else:
            current_has_condominio = pd.to_numeric(samples["has_condominio"], errors="coerce")
            samples["has_condominio"] = current_has_condominio.fillna(inferred_has_condominio)

    for column in metadata["categorical_features"]:
        if column not in samples.columns:
            samples[column] = "nao informado"
        samples[column] = samples[column].fillna("nao informado").map(normalize_label)

    for column in metadata["numeric_features"]:
        if column not in samples.columns:
            samples[column] = 0
        samples[column] = pd.to_numeric(samples[column], errors="coerce").fillna(0)

    return samples[metadata["raw_features"]]


def read_input() -> pd.DataFrame:
    """Lê o arquivo `entrada.csv` esperado pela especificação do trabalho."""
    if not INPUT_FILE.exists():
        raise FileNotFoundError(f"Arquivo de entrada não encontrado: {INPUT_FILE}")

    return pd.read_csv(INPUT_FILE)


def main() -> None:
    """Executa o fluxo completo de inferência e grava `resultado.csv`."""
    try:
        df_entrada = read_input()
        model, metadata = load_solution()

        ids = df_entrada["id"] if "id" in df_entrada.columns else range(1, len(df_entrada) + 1)
        df_preparado = prepare_new_samples(df_entrada, metadata)
        previsoes = pd.Series(model.predict(df_preparado)).round().astype("int64")

        df_resultado = pd.DataFrame(
            {
                "id": ids,
                "valor_previsto": previsoes,
            }
        )
        df_resultado.to_csv(OUTPUT_FILE, index=False)
        print(f"Resultados salvos em: {OUTPUT_FILE}")
    except Exception as exc:
        print(f"Erro na inferência: {exc}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
