# PlayBox
Plataforma web de avaliação de jogos desenvolvido na disciplina de Projeto Integrado.

# Sumário
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Diagrama de Classes](#diagrama-de-classes)
- [Ferramentas Utilizadas](#ferramentas-utilizadas)
- [Framewoks utilizados](#framewoks-utilizados)
- [Gerar documentação de código](#gerar-documentação-de-código)
- [Instalação e Execução](#instalação-e-execução)
- [Testes](#testes)
- [Licença](#licença)

# Estrutura do Projeto
O projeto é dividido em duas partes principais: client (frontend) e server (backend). A estrutura do frontend é explicada em [client/STRUCTURE.md](client/STRUCTURE.md) e a do backend em [server/STRUCTURE.md](server/STRUCTURE.md).

Há também o diretório [scripts](scripts), que contém scripts úteis como instalação de dependências, envio de jogos para o banco de dados e geração de reviews aleatórias.

# Diagrama de Classes
Clique no link para acessar o diagrama de classes do projeto no figma: [Diagrama de Classes](https://www.figma.com/proto/QDnrFeOwIcdeOkrhybck0W/Trabalho-PI?node-id=51-180&t=V2FmtJweQSe3p507-1)

Um jogo pode estar associado a um ou mais gêneros. Além disso, ele pode receber diversos reviews publicados pelos usuários da plataforma. Ao criar uma conta, o usuário recebe automaticamente um catálogo vazio, que funciona como uma lista de favoritos, onde poderá adicionar os jogos do seu interesse.

# Ferramentas Utilizadas
#### **Git**
- **GitHub**: Repositório remoto utilizado para versionamento do código e colaboração entre os membros da equipe.

#### **Build e Gerenciamento de Pacotes**
- **Npm**: Gerenciador de pacotes utilizado para instalar dependências do projeto.
- **Nodemon**: Ferramenta de desenvolvimento para reinicialização automática do servidor durante o desenvolvimento.

#### **Testes**
- **Jest**: Framework de testes utilizado para executar os testes automatizados.
- **Supertest**: Biblioteca para testes de APIs HTTP.

#### **Issue Tracking**
- **GitHub Issues**: Utilizado para rastreamento de problemas e gerenciamento de tarefas.

#### **CI/CD**
- **Vercel**: Configurado para implementar integração contínua e entrega contínua (CI/CD) do projeto, automatizando o processo de build e deploy do frontend.
- **GitHub Actions**: Configurado para implementar integração contínua e entrega contínua (CI/CD) do projeto, automatizando o processo de build.
- **Render**: Utilizado para implantar o backend do projeto, permitindo que a API esteja disponível online.


#### **Containerização**
- **Docker**: Utilizado para criar contêineres do projeto, facilitando o ambiente de desenvolvimento e implantação.

#### **Banco de Dados**
- **PostgreSQL**: Sistema de gerenciamento de banco de dados relacional utilizado para armazenar os dados do projeto.
Observação: Na primeira etapa do trabalho havia sido mencionado o uso do MySQL, mas foi alterado para PostgreSQL.

#### **Documentação de código**
- **JSDoc**: Utilizado para gerar documentação do código JavaScript tanto no backend quanto no frontend.

#### **Scripts Python**
- **Requests**: Biblioteca Python para requisições HTTP.
- **Python-dotenv**: Para gerenciamento de variáveis de ambiente nos scripts Python.

### **Outras ferramentas**
- **Figma**: Utilizado para design de interfaces e prototipagem.
- **Makefile**: Arquivo utilizado para automatizar tarefas comuns do projeto, como instalação de dependências e execução de scripts.
- **Bash**: Utilizado para executar scripts e comandos no terminal.

# Frameworks e Bibliotecas utilizados
- **React**: Biblioteca JavaScript para construção de interfaces de usuário.
- **Express.js**: Framework para construção de APIs em Node.js.
- **Node.js**: Ambiente de execução JavaScript no lado do servidor.
- **Prisma**: ORM utilizado para interagir com o banco de dados PostgreSQL.
- **Chart.js**: Biblioteca para criação de gráficos e visualizações (usado no GameRadarChart).
- **Axios**: Cliente HTTP para realizar requisições à API.
- **bcryptjs**: Biblioteca para hash de senhas.
- **jsonwebtoken**: Implementação de JWT para autenticação.
- **cors**: Middleware para habilitar CORS no Express.

# Gerar documentação de código
Para gerar a documentação do código, execute o seguinte comando no terminal:
```bash
make docs
```
Isso irá gerar a documentação do backend e do frontend, utilizando o JSDoc para ambos. A documentação será gerada nos diretórios `server/docs` e `client/docs`, respectivamente.

# Instalação e Execução
Durante o desenvolvimento, é possível executar o projeto de duas maneiras: utilizando o Docker ou diretamente no ambiente local.
Em ambos os casos, você precisará clonar o repositório:
   ```bash
   git clone https://github.com/RenanCampista/Playbox.git
   ```

## Opção 1: Utilizando Docker (Recomendado)
1. Certifique-se de que o Docker esteja instalado e em execução no seu sistema.

2. Navegue até o diretório do projeto:
   ```bash
   cd Playbox
   ```
3. Crie um arquivo `.env` na raiz do projeto e configure as variáveis de ambiente necessárias. Um exemplo de arquivo `.env` pode ser encontrado em `.env.example`.
   ```bash
   cp .env.example .env
   ```
   Edite o arquivo `.env` com as configurações apropriadas para o seu ambiente.

4. Execute o seguinte comando para construir e iniciar os contêineres do Docker:
   ```bash
   make docker
   ```
5. Após a construção, os contêineres serão iniciados e a aplicação estará disponível em [http://localhost:3000](http://localhost:3000).

6. Para parar os contêineres, execute:
   ```bash
   make down
   ```

7. Para executar as migrações do banco de dados, utilize o seguinte comando:
   ```bash
   make migrate
   ```

## Opção 2: Ambiente Local
Para executar o projeto diretamente no ambiente local, siga os passos abaixo:
1. Certifique-se de que o Node.js esteja instalado no seu sistema.

2. Navegue até o diretório do projeto:
   ```bash
   cd Playbox
   ```

3. Crie um arquivo `.env` na raiz do projeto e configure as variáveis de ambiente necessárias. Um exemplo de arquivo `.env` pode ser encontrado em `.env.example`.
   ```bash
   cp .env.example .env
   ```
   Edite o arquivo `.env` com as configurações apropriadas para o seu ambiente.

4. Execute o seguinte comando para instalar as dependências do projeto:
   ```bash
   make install
   ```

5. Para iniciar o servidor Express, execute o seguinte comando:
   ```bash
   make start_server
   ```

6. Para iniciar a aplicação React, em outro terminal, execute o seguinte comando:
   ```bash
   make start_frontend
   ```
7. Acesse a aplicação no navegador em [http://localhost:3000](http://localhost:3000).


# Testes
Para executar os testes do projeto, você pode utilizar o seguinte comando:
```bash
make test
```
Isso irá executar os testes automatizados utilizando o Jest e o Supertest, garantindo que a API esteja funcionando corretamente.

# Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

## Autores

- **Renan Campista** - [RenanCampista](https://github.com/RenanCampista)
- **Artur Mendes de Moraes** - [ArturMendesMoraes](https://github.com/Arturmmoraes)
- **Pedro Henrique Queiroz** - [PedroHQuedevez](https://github.com/PedroHQuedevez)

   