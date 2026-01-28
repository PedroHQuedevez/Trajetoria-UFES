# Coletor de dados de jogos
Script para coletar dados de jogos usando a [RAWG Video Games Database API (v1.0)](https://api.rawg.io/docs/) e enviá-los diretamente para a API do backend.

## Requisitos
- [Python 3.8](https://www.python.org/downloads/) ou superior.
- [Pip](https://pip.pypa.io/en/stable/installation/) (gerenciador de pacotes do Python).
- Servidor backend rodando (PlayboxBase API).

## Instalação
1. Instale as dependências:
    ```bash
    pip install -r requirements.txt
    ```

2. Configure as variáveis de ambiente no arquivo `.env` na raiz do projeto:
    ```bash
    RAWG_API_KEY=your_rawg_api_key
    BACKEND_URL=http://localhost:5000  # URL do seu backend
    ```

## Uso
1. Certifique-se de que o servidor backend está rodando na porta especificada.

2. No terminal, execute o script:
    ```bash
    python main.py
    ```
    