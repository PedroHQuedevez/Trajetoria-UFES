# Predição de Preço de Venda de Imóveis na Grande Vitória

Projeto final da disciplina de Inteligência Artificial. A solução estima o valor de venda de casas, apartamentos e coberturas localizados na Grande Vitória, ES, a partir de dados coletados de portais imobiliários.

## Integrantes do grupo

- Arthur Maciel;
- Pedro Henrique de Castro Cunha Quedevez;
- Renan Campista.

## Link para o relatório final do projeto

[Relatório Final](https://drive.google.com/file/d/1cgCf04009qUolElKZ2YY_qBzhPnIlsK9/view?usp=sharing)

## Sumário

- [Predição de Preço de Venda de Imóveis na Grande Vitória](#predição-de-preço-de-venda-de-imóveis-na-grande-vitória)
  - [Integrantes do grupo](#integrantes-do-grupo)
  - [Link para o relatório final do projeto](#link-para-o-relatório-final-do-projeto)
  - [Sumário](#sumário)
  - [Objetivo](#objetivo)
  - [Fontes de dados](#fontes-de-dados)
  - [Solução desenvolvida](#solução-desenvolvida)
  - [Requisitos](#requisitos)
  - [Como instalar](#como-instalar)
  - [Como reproduzir o treinamento](#como-reproduzir-o-treinamento)
  - [Como executar a inferência](#como-executar-a-inferência)
  - [Formato do arquivo de entrada](#formato-do-arquivo-de-entrada)
  - [Formato do arquivo de saída](#formato-do-arquivo-de-saída)
  - [Arquivos principais](#arquivos-principais)
  - [Estrutura de diretórios](#estrutura-de-diretórios)

## Objetivo

Construir uma solução completa de aprendizado de máquina para prever preço de venda de imóveis na Grande Vitória. O projeto contempla coleta de dados, construção do dataset, limpeza, tratamento de valores faltantes, análise exploratória, engenharia de atributos, treinamento, avaliação e disponibilização de um script de inferência.

## Fontes de dados

Os dados foram coletados de anúncios públicos de imóveis:

- OLX: `datasets/imoveis_olx.csv`
- ZAP Imóveis: `datasets/imoveis_zapimoveis.csv`

O dataset final limpo usado para modelagem está em:

- `datasets/vendas_grande_vitoria_clean.csv`

Durante a limpeza também são gerados relatórios auxiliares em `datasets/cleaning_reports/`, com registros removidos por inconsistências, anomalias ou regras de qualidade.

## Solução desenvolvida

A solução usa modelos supervisionados de regressão para estimar o preço de venda (`price`). O notebook principal compara diferentes algoritmos e permite selecionar o modelo final por meio da variável `modelo_name`.

Modelos avaliados:

- Extra Trees
- KNN Regressor
- Hist Gradient Boosting
- XGBoost
- versões ajustadas por busca rápida de hiperparâmetros, quando executadas

O artefato final salvo para inferência é:

- `modelo_final_imoveis.joblib`

Os metadados do modelo final são salvos em:

- `metadata_modelo_final_imoveis.json`

## Requisitos

O projeto foi desenvolvido em Python 3.11. As dependências estão listadas em `requirements.txt`.

Principais bibliotecas:

- pandas
- numpy
- scikit-learn
- xgboost
- joblib
- matplotlib
- beautifulsoup4
- requests

## Como instalar

Crie e ative um ambiente virtual:

```bash
python -m venv .venv
```

No Windows:

```bash
.venv\Scripts\activate
```

No Linux/macOS:

```bash
source .venv/bin/activate
```

Instale as dependências:

```bash
pip install -r requirements.txt
```

## Como reproduzir o treinamento

1. Execute a limpeza dos dados:

```bash
python data_cleaning/clean_data.py
```

2. Abra e execute o notebook de modelagem:

```text
modelo_venda_imoveis.ipynb
```

3. No notebook, defina o modelo final desejado na variável:

```python
modelo_name = "XGBoost"
```

4. Execute as células de treinamento, avaliação e salvamento do artefato.

Ao final, devem ser gerados ou atualizados:

- `modelo_final_imoveis.joblib`
- `metadata_modelo_final_imoveis.json`

## Como executar a inferência

O arquivo exigido para correção é:

```text
inferencia.py
```

Para executar, coloque o arquivo `entrada.csv` na raiz do projeto e rode:

```bash
python inferencia.py
```

O script carrega o modelo treinado, aplica os pré-processamentos necessários, trata valores faltantes e desconhecidos, realiza a previsão e gera:

```text
resultado.csv
```

Não é necessário executar nenhum tratamento manual antes da inferência, além de fornecer o arquivo `entrada.csv`.

## Formato do arquivo de entrada

O arquivo `entrada.csv` deve conter uma coluna identificadora `id` e os atributos disponíveis para a previsão. O script aceita colunas extras e também trata atributos ausentes, mas recomenda-se fornecer as colunas abaixo para melhor qualidade da estimativa.

| Coluna | Tipo | Descrição |
| --- | --- | --- |
| `id` | texto ou número | Identificador da amostra. |
| `real_estate_type` | texto | Tipo do imóvel. Exemplos: `casa`, `apartamento`, `cobertura`. |
| `municipality` | texto | Município do imóvel. Exemplos: `Vitória`, `Vila Velha`, `Serra`, `Cariacica`, `Guarapari`. |
| `neighbourhood` | texto | Bairro do imóvel. |
| `size` | número | Área do imóvel em m². |
| `rooms` | número | Quantidade de quartos. |
| `bathrooms` | número | Quantidade de banheiros. |
| `garage_spaces` | número | Quantidade de vagas de garagem. |
| `has_condominio` | 0 ou 1 | Indica se o imóvel possui condomínio. Pode ser omitido; nesse caso, o script tenta inferir. |

Exemplo:

```csv
id,real_estate_type,municipality,neighbourhood,size,rooms,bathrooms,garage_spaces,has_condominio
teste1,apartamento,Vila Velha,Praia da Costa,90,2,2,2,1
teste2,casa,Serra,Cidade Continental,120,3,2,1,0
```

O script também consegue usar colunas textuais opcionais como `title`, `description` e `raw_text` para auxiliar a inferência de `has_condominio`, caso elas estejam presentes.

## Formato do arquivo de saída

Após a execução, o script gera `resultado.csv` no formato:

```csv
id,valor_previsto
teste1,850000.0
teste2,430000.0
```

As colunas são:

| Coluna | Descrição |
| --- | --- |
| `id` | Identificador recebido no arquivo de entrada. |
| `valor_previsto` | Preço de venda estimado pelo modelo. |

## Arquivos principais

| Arquivo | Finalidade |
| --- | --- |
| `inferencia.py` | Script autosuficiente de inferência exigido na especificação. |
| `modelo_venda_imoveis.ipynb` | Notebook de treinamento, avaliação e salvamento do modelo. |
| `modelo_final_imoveis.joblib` | Modelo treinado usado na inferência. |
| `metadata_modelo_final_imoveis.json` | Metadados do modelo, features e métricas. |
| `data_cleaning/clean_data.py` | Script de limpeza e construção do dataset final. |
| `data_analisys/analise_exploratoria_imoveis_grande_vitoria.ipynb` | Análise exploratória dos dados. |
| `datasets/vendas_grande_vitoria_clean.csv` | Dataset limpo usado na modelagem. |
| `requirements.txt` | Dependências necessárias para execução. |

## Estrutura de diretórios

```text
.
├── collectors/
│   ├── olx_scraper.py
│   └── zapimoveis_scraper.py
├── data_analisys/
│   └── analise_exploratoria_imoveis_grande_vitoria.ipynb
├── data_cleaning/
│   └── clean_data.py
├── datasets/
│   ├── cleaning_reports/
│   ├── imoveis_olx.csv
│   ├── imoveis_zapimoveis.csv
│   └── vendas_grande_vitoria_clean.csv
├── Cópia de Descrição do Projeto - IA - 2026_2.pdf
├── inferencia.py
├── LICENSE
├── metadata_modelo_final_imoveis.json
├── modelo_final_imoveis.joblib
├── modelo_venda_imoveis.ipynb
├── README.md
└── requirements.txt
```
