# Backend Structure - Playbox Server

```
server/
├── __tests__/           # Testes unitários e de integração
│   ├── README.md       # Documentação dos testes
│   ├── auth.test.js    # Testes de autenticação
│   ├── games.test.js   # Testes das funcionalidades de jogos
│   ├── routes.test.js  # Testes das rotas
│   ├── setup.js        # Configuração inicial dos testes
│   └── users.test.js   # Testes das funcionalidades de usuários
├── prisma/             # Configuração do banco de dados
│   ├── migrations/     # Histórico de migrações do banco
│   └── schema.prisma   # Schema do banco de dados
├── routes/             # Definição das rotas da API
│   ├── index.js        # Agregador de todas as rotas
│   ├── auth.js         # Rotas de autenticação (login, registro)
│   ├── catalogs.js     # Rotas de catálogos
│   ├── games.js        # Rotas de jogos
│   ├── reviews.js      # Rotas de avaliações
│   └── users.js        # Rotas de usuários
├── services/           # Lógica de negócio e serviços
│   ├── catalogServices.js # Serviços de catálogos
│   ├── gameServices.js    # Serviços de jogos
│   ├── prisma.js         # Cliente Prisma para banco de dados
│   ├── reviewServices.js # Serviços de avaliações
│   └── userServices.js   # Serviços de usuários
├── .dockerignore       # Arquivos ignorados pelo Docker
├── .gitignore          # Arquivos ignorados pelo Git
├── Dockerfile          # Configuração do container Docker
├── jest.config.js      # Configuração do Jest para testes
├── jsdoc.conf.json     # Configuração do JSDoc para documentação
├── package.json        # Dependências e scripts do Node.js
├── package-lock.json   # Lock file das dependências
└── server.js           # Arquivo principal do servidor Express
```


## Arquitetura

```
Cliente → Rotas → Serviços → Banco de Dados
   ↑         ↓         ↓         ↓
Browser   Express  Business   Prisma
                   Logic      ORM
```
