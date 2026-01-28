# Frontend Structure - Playbox Client

```
src/
├── components/          # Componentes reutilizáveis (.jsx)
│   ├── index.js        # Barrel exports dos components
│   ├── GameRadarChart.jsx # Gráfico radar para jogos
│   ├── Header.jsx      # Cabeçalho da aplicação
│   ├── ReviewForm.jsx  # Formulário de avaliações
│   ├── UserForm.jsx    # Formulário de usuários
│   ├── UserList.jsx    # Lista de usuários
│   └── UserProfile.jsx # Perfil do usuário
├── pages/              # Páginas principais (.jsx)
│   ├── index.js        # Barrel exports das pages
│   ├── AdminPanel.jsx  # Painel administrativo
│   ├── App.jsx         # Componente principal
│   ├── ForgotPassword.jsx # Página recuperação de senha
│   ├── GameDetail.jsx  # Detalhes do jogo
│   ├── Home.jsx        # Página inicial
│   ├── Login.jsx       # Página de login
│   └── Register.jsx    # Página de registro
├── services/           # Serviços e APIs (.js)
│   └── api.js          # Configuração da API e endpoints
├── styles/             # Todos os arquivos CSS
│   ├── AdminPanel.css  # Estilos do painel admin
│   ├── App.css         # Estilos globais
│   ├── ForgotPassword.css # Estilos recuperação
│   ├── GameDetail.css  # Estilos detalhes do jogo
│   ├── GameRadarChart.css # Estilos do gráfico radar
│   ├── Header.css      # Estilos do header
│   ├── Home.css        # Estilos da página inicial
│   ├── index.css       # Estilos base
│   ├── Login.css       # Estilos do login
│   ├── Register.css    # Estilos do registro
│   ├── ReviewForm.css  # Estilos do formulário de review
│   ├── UserForm.css    # Estilos do formulário de usuário
│   ├── UserList.css    # Estilos da lista de usuários
│   └── UserProfile.css # Estilos do perfil do usuário
├── utils/              # Utilitários (.js)
│   ├── index.js        # Barrel exports dos utils
│   ├── constants.js    # Constantes da aplicação
│   ├── reportWebVitals.js # Performance metrics
│   ├── setupTests.js   # Configuração de testes
│   └── validation.js   # Funções de validação
├── index.js            # Ponto de entrada da aplicação
└── logo.svg            # Logo da aplicação
```