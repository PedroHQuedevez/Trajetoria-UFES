// TESTES DAS ROTAS DE USUÁRIOS

const request = require('supertest');
const express = require('express');
const { mockPrisma } = require('./setup');

// CONFIGURAÇÃO DOS MOCKS
// Importa o módulo de serviços de usuário que será mockado
const userServices = require('../services/userServices.js');

// Mock completo dos serviços de usuário
jest.mock('../services/userServices.js', () => ({
  createUser: jest.fn(),        // Criar novo usuário
  getAllUsers: jest.fn(),       // Listar todos os usuários
  getUserById: jest.fn(),       // Buscar usuário por ID
  updateUser: jest.fn(),        // Atualizar dados do usuário
  deleteUser: jest.fn(),        // Deletar usuário
  
  // Este mock simula um usuário ADMIN autenticado
  authenticateToken: jest.fn((req, res, next) => {
    req.user = { id: 1, name: 'Test User', email: 'test@test.com', isAdmin: true };
    next();
  }),
  
  // Mock do middleware de verificação de admin
  requireAdmin: jest.fn((req, res, next) => {
    if (req.user && req.user.isAdmin) {
      next();
    } else {
      res.status(403).json({ error: 'Acesso negado. Apenas administradores.' });
    }
  })
}));

// Importa as rotas de usuários que serão testadas
const userRoutes = require('../routes/users');

// TESTE PRINCIPAL
describe('User Routes', () => {
  let app;

  // Configuração executada uma vez antes de todos os testes
  beforeAll(() => {
    app = express();
    app.use(express.json());
    app.use('/users', userRoutes);
  });

  beforeEach(() => {
    // Limpa todos os mocks para garantir que cada teste seja independente
    jest.clearAllMocks();
  });

  // TESTES DA ROTA DE CRIAÇÃO DE USUÁRIO (POST /users)
  describe('POST /users', () => {
    
    // Teste: Criação bem-sucedida de um novo usuário
    it('deve criar um novo usuário', async () => {
      const mockResult = {
        status: 201,
        success: true,
        message: 'Usuário criado com sucesso',
        user: {
          id: 1,
          name: 'Novo Usuario',
          email: 'novo@test.com'
        }
      };

      // Configura o mock para retornar sucesso quando chamado
      userServices.createUser.mockResolvedValue(mockResult);

      // Dados do usuário a ser criado
      const userData = {
        name: 'Novo Usuario',
        email: 'novo@test.com',
        password: 'password123'
      };

      // Executa a criação do usuário
      const response = await request(app)
        .post('/users')
        .send(userData)
        .expect(201);

      // Verifica se a criação foi bem-sucedida
      expect(response.body.success).toBe(true);
      expect(response.body.user.name).toBe('Novo Usuario');
      expect(userServices.createUser).toHaveBeenCalledWith(userData);
    });
  });

  // TESTES DA ROTA DE LISTAGEM DE USUÁRIOS (GET /users)
  describe('GET /users', () => {
    
    // Teste: Listagem bem-sucedida (usuário admin)
    it('deve listar todos os usuários (admin)', async () => {
      const mockResult = {
        status: 200,
        success: true,
        users: [
          { id: 1, name: 'User 1', email: 'user1@test.com' },
          { id: 2, name: 'User 2', email: 'user2@test.com' }
        ]
      };

      // Configura o mock para retornar a lista de usuários
      userServices.getAllUsers.mockResolvedValue(mockResult);

      // Faz requisição para listar usuários
      const response = await request(app)
        .get('/users')
        .expect(200);

      expect(response.body.success).toBe(true);
      expect(response.body.users).toHaveLength(2);
      expect(userServices.getAllUsers).toHaveBeenCalled();
    });
  });

  // TESTE DE CONTROLE DE ACESSO (AUTORIZAÇÃO)
  describe('Acesso negado para não-admin', () => {
    
    // Configuração para simular usuário não admin
    beforeAll(() => {
      // Redefine os mocks para simular usuário sem privilégios de admin
      userServices.authenticateToken.mockImplementation((req, res, next) => {
        req.user = { id: 1, name: 'Test User', email: 'test@test.com', isAdmin: false };
        next();
      });

      userServices.requireAdmin.mockImplementation((req, res, next) => {
        if (req.user && req.user.isAdmin) {
          next();
        } else {
          // Bloqueia acesso para não-admin
          res.status(403).json({ error: 'Acesso negado. Apenas administradores.' });
        }
      });
    });

    // Teste: Verificar se usuário comum é bloqueado
    it('deve negar acesso para usuário não-admin', async () => {
      const response = await request(app)
        .get('/users')
        .expect(403);

      // Verifica se o acesso foi negado
      expect(response.body.error).toBe('Acesso negado. Apenas administradores.');
    });
  });
});
