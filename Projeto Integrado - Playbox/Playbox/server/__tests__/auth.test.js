// TESTES DAS ROTAS DE AUTENTICAÇÃO

const request = require('supertest');           // Para fazer requisições HTTP nos testes
const express = require('express');
const { mockPrisma } = require('./setup');      // Mock do banco de dados

// CONFIGURAÇÃO DOS MOCKS
// Mocks são usados para substituir implementações reais por versões controladas nos testes

// Importa o módulo de serviços de usuário que será mockado
const userServices = require('../services/userServices.js');

// Cria mocks para as funções do userServices
// Isso substitui as funções reais por versões falsas controladas nos testes
jest.mock('../services/userServices.js', () => ({
  // Mock da função de autenticação
  authenticateUser: jest.fn(),
  
  // Mock da função de alteração de senha
  changePassword: jest.fn(),
  
  // Mock do middleware de autenticação de token
  // Simula um usuário autenticado adicionando dados do usuário na requisição
  authenticateToken: jest.fn((req, res, next) => {
    req.user = { id: 1, name: 'Test User', email: 'test@test.com', isAdmin: false };
    next();
  })
}));

// Importa as rotas de autenticação que serão testadas
const authRoutes = require('../routes/auth');

describe('Auth Routes', () => {
  let app; // Variável para armazenar a aplicação Express

  // Configuração executada uma vez antes de todos os testes
  beforeAll(() => {
    // Cria uma aplicação Express para os testes
    app = express();
    app.use(express.json());          // Middleware para interpretar JSON
    app.use('/auth', authRoutes);     // Registra as rotas de autenticação
  });

  // Configuração executada antes de cada teste individual
  beforeEach(() => {
    // Limpa todos os mocks para garantir que cada teste seja independente
    jest.clearAllMocks();
  });

  // TESTES DA ROTA DE LOGIN (POST /auth/login)
  describe('POST /auth/login', () => {
    
    // Teste: Login com credenciais válidas deve funcionar
    it('deve fazer login com credenciais válidas', async () => {

      // Define o resultado esperado quando a autenticação é bem-sucedida
      const mockResult = {
        status: 200,
        success: true,
        message: 'Login realizado com sucesso',
        token: 'fake-jwt-token',
        user: { id: 1, name: 'Test User', email: 'test@test.com' }
      };

      // Configura o mock para retornar sucesso quando chamado
      userServices.authenticateUser.mockResolvedValue(mockResult);

      // Faz uma requisição POST para /auth/login com credenciais válidas
      const response = await request(app)
        .post('/auth/login')
        .send({
          email: 'test@test.com',
          password: 'password123'
        })
        .expect(200);

      // ASSERT: Verifica se o resultado está correto
      expect(response.body.success).toBe(true);                     // Login foi bem-sucedido
      expect(response.body.token).toBe('fake-jwt-token');           // Token foi retornado
      expect(userServices.authenticateUser).toHaveBeenCalledWith(   // Função foi chamada com parâmetros corretos
        'test@test.com', 
        'password123'
      );
    });

    // Teste: Login com credenciais inválidas deve falhar
    it('deve retornar erro para credenciais inválidas', async () => {
      const mockResult = {
        status: 401,
        success: false,
        error: 'Email ou senha incorretos'
      };

      // Configura o mock para retornar erro de autenticação
      userServices.authenticateUser.mockResolvedValue(mockResult);

      //Tenta fazer login com credenciais inválidas
      const response = await request(app)
        .post('/auth/login')
        .send({
          email: 'wrong@test.com',
          password: 'wrongpassword'
        })
        .expect(401);

      //Verifica se o erro foi tratado corretamente
      expect(response.body.success).toBe(false);
      expect(response.body.error).toBe('Email ou senha incorretos');
    });

    // Teste: Validação de campos obrigatórios
    it('deve retornar erro quando email ou senha não são fornecidos', async () => {
      // Tenta fazer login sem fornecer a senha
      const response = await request(app)
        .post('/auth/login')
        .send({
          email: 'test@test.com'
          // senha ausente intencionalmente
        })
        .expect(400);

      expect(response.body.error).toBe('Email e senha são obrigatórios.');
    });
  });

  // TESTES DA ROTA DE VERIFICAÇÃO DE TOKEN (GET /auth/verify)
  describe('GET /auth/verify', () => {
    
    // Teste: Verificação de token válido
    it('deve verificar token válido', async () => {
      // O middleware authenticateToken (mockado) automaticamente adiciona req.user
      const response = await request(app)
        .get('/auth/verify')
        .expect(200);

      // Verifica se o token foi validado corretamente
      expect(response.body.message).toBe('Token válido');
      expect(response.body.user).toHaveProperty('id', 1);
      expect(response.body.user).toHaveProperty('email', 'test@test.com');
    });
  });

  // TESTES DA ROTA DE ALTERAÇÃO DE SENHA (PUT /auth/changePassword)
  describe('PUT /auth/changePassword', () => {
    
    // Teste: Alteração de senha bem-sucedida
    it('deve alterar senha com sucesso', async () => {
      // Prepara resultado de sucesso
      const mockResult = {
        status: 200,
        success: true,
        message: 'Senha alterada com sucesso'
      };

      // Configura o mock para simular alteração bem-sucedida
      userServices.changePassword.mockResolvedValue(mockResult);

      // Faz requisição para alterar senha
      const response = await request(app)
        .put('/auth/changePassword')
        .send({
          currentPassword: 'oldPassword123',
          newPassword: 'newPassword123'
        })
        .expect(200);

      // Verifica se a alteração foi processada corretamente
      expect(response.body.success).toBe(true);
      expect(userServices.changePassword).toHaveBeenCalledWith(
        1,                          // ID do usuário (vem do mock do authenticateToken)
        'oldPassword123',           // Senha atual
        'newPassword123'            // Nova senha
      );
    });

    // Teste: Validação de campos obrigatórios na alteração de senha
    it('deve retornar erro quando senhas não são fornecidas', async () => {
      // Tenta alterar senha sem fornecer nova senha
      const response = await request(app)
        .put('/auth/changePassword')
        .send({
          currentPassword: 'oldPassword123'
          // newPassword ausente intencionalmente
        })
        .expect(400);

      expect(response.body.error).toBe('Senha atual e nova senha são obrigatórias.');
    });
  });
});
