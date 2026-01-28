# Testes Automatizados - Playbox Backend

Este diretório contém os testes automatizados para o backend da aplicação Playbox.

## Estrutura dos Testes

- `setup.js` - Configuração inicial dos testes, mocks e variáveis de ambiente
- `routes.test.js` - Testes das rotas principais da API
- `auth.test.js` - Testes das rotas de autenticação
- `users.test.js` - Testes das rotas de usuários
- `games.test.js` - Testes das rotas de jogos

## Como Executar os Testes
Assumindo que você já tenha o instalado as dependências do projeto, você pode executar os testes com o seguinte comando:

```bash
npm test
```

## Tecnologias Utilizadas

- **Jest** - Framework de testes
- **Supertest** - Testes de rotas HTTP
- **Mocks** - Simulação do Prisma e outras dependências

## Considerações

- Os testes não fazem conexões reais com o banco de dados
- Todos os serviços externos são mockados
- Os testes são independentes entre si
- Cada teste limpa os mocks antes de executar

## Adicionando Novos Testes

Para adicionar novos testes:

1. Crie um arquivo `*.test.js` no diretório `__tests__`
2. Importe o `setup.js` se precisar dos mocks
3. Use `describe` para agrupar testes relacionados
4. Use `it` para testes individuais

Exemplo:
```javascript
const { mockPrisma } = require('./setup');

describe('Novo Módulo', () => {
  it('deve fazer algo específico', async () => {
    // Teste específico
  });
});
```
