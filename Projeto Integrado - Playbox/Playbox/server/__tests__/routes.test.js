// TESTES DAS ROTAS PRINCIPAIS DA API

const request = require('supertest');
const express = require('express');
const { mockPrisma } = require('./setup');

// CONFIGURAÇÃO DOS MOCKS
// Mock completo dos serviços de usuário
jest.mock('../services/userServices.js', () => ({
  getUserByEmail: jest.fn(),    // Buscar usuário por email
  createAdmin: jest.fn(),       // Criar usuário administrador
  authenticateUser: jest.fn(),  // Autenticar usuário
  createUser: jest.fn(),        // Criar novo usuário
  getAllUsers: jest.fn(),       // Listar todos os usuários
  
  // Simula um usuário comum autenticado
  authenticateToken: jest.fn((req, res, next) => {
    req.user = { id: 1, name: 'Test User', email: 'test@test.com', isAdmin: false };
    next();
  }),
  
  // Mock do middleware de verificação de admin
  // Permite acesso apenas se o usuário for admin
  requireAdmin: jest.fn((req, res, next) => {
    if (req.user && req.user.isAdmin) {
      next();
    } else {
      res.status(403).json({ error: 'Acesso negado. Apenas administradores.' });
    }
  })
}));

// Importa as rotas principais da aplicação
const routes = require('../routes/index');

describe('API Routes', () => {
  let app;

  beforeAll(() => {
    app = express();
    app.use(express.json());  // Middleware para interpretar JSON
    app.use(routes);          // Registra todas as rotas da aplicação
  });

  // TESTE DA ROTA RAIZ (GET /)
  describe('GET /', () => {
    
    // Teste: Verificar se a API retorna informações básicas
    it('deve retornar informações da API', async () => {
      const response = await request(app)
        .get('/')
        .expect(200); // Espera status HTTP 200 (sucesso)

      // Verifica se as informações da API estão corretas
      expect(response.body).toHaveProperty('message', 'API Playbox funcionando!');
      expect(response.body).toHaveProperty('version', '1.0.0');
      expect(response.body).toHaveProperty('endpoints');  // Deve ter lista de endpoints
    });
  });
});
