// TESTES DAS ROTAS DE JOGOS

const request = require('supertest');
const express = require('express');
const { mockPrisma } = require('./setup');

// CONFIGURAÇÃO DOS MOCKS
// Importa o módulo de serviços de jogos que será mockado
const gameServices = require('../services/gameServices.js');

// Mock completo dos serviços de jogos
jest.mock('../services/gameServices.js', () => ({
  createGame: jest.fn(),        // Criar novo jogo
  getGameById: jest.fn(),       // Buscar jogo por ID
  getGameByName: jest.fn(),     // Buscar jogo por nome
  getAllGames: jest.fn(),       // Listar todos os jogos
  searchGames: jest.fn(),       // Buscar jogos por texto
  getRandomGames: jest.fn()     // Buscar jogos aleatórios
}));

// Importa as rotas de jogos que serão testadas
const gameRoutes = require('../routes/games');


// SUÍTE DE TESTES PRINCIPAL
describe('Game Routes', () => {
  let app;

  // Configuração executada uma vez antes de todos os testes
  beforeAll(() => {
    // Cria uma aplicação Express para os testes
    app = express();
    app.use(express.json());          // Middleware para interpretar JSON
    app.use('/games', gameRoutes);
  });

  // Configuração executada antes de cada teste individual
  beforeEach(() => {
    // Limpa todos os mocks para garantir que cada teste seja independente
    jest.clearAllMocks();
  });

  // TESTES DA ROTA DE CRIAÇÃO DE JOGO (POST /games)
  describe('POST /games', () => {
    
    // Teste: Criação bem-sucedida de um novo jogo
    it('deve criar um novo jogo', async () => {
      const mockResult = {
        status: 201,
        success: true,
        message: 'Jogo criado com sucesso',
        game: {
          id: 1,
          name: 'Test Game',
          description: 'A test game',
          platforms: ['PC', 'PlayStation']
        }
      };

      // Configura o mock para retornar sucesso quando chamado
      gameServices.createGame.mockResolvedValue(mockResult);

      // Dados do jogo a ser criado
      const gameData = {
        name: 'Test Game',
        description: 'A test game',
        platforms: ['PC', 'PlayStation']
      };

      const response = await request(app)
        .post('/games')
        .send(gameData)
        .expect(201);

      expect(response.body.success).toBe(true);
      expect(response.body.game.name).toBe('Test Game');
      expect(gameServices.createGame).toHaveBeenCalledWith(gameData);
    });

    // Teste: Falha na criação com dados inválidos
    it('deve retornar erro ao tentar criar jogo com dados inválidos', async () => {
      // Simula cenário de falha (ex: nome do jogo obrigatório)
      const mockResult = {
        status: 400,
        success: false,
        error: 'Nome do jogo é obrigatório'
      };

      // Configura o mock para retornar erro
      gameServices.createGame.mockResolvedValue(mockResult);

      const response = await request(app)
        .post('/games')
        .send({
          description: 'Game without name'
        })
        .expect(400);

      expect(response.body.success).toBe(false);
      expect(response.body.error).toBe('Nome do jogo é obrigatório');
    });
  });

  // TESTES DA ROTA DE BUSCA POR ID (GET /games/:id)
  describe('GET /games/:id', () => {
    
    // Teste: Busca bem-sucedida de jogo por ID
    it('deve buscar jogo por ID', async () => {
      const mockResult = {
        status: 200,
        success: true,
        game: {
          id: 1,
          name: 'Test Game',
          description: 'A test game'
        }
      };

      // Configura o mock para retornar o jogo encontrado
      gameServices.getGameById.mockResolvedValue(mockResult);

      // Busca jogo pelo ID 1
      const response = await request(app)
        .get('/games/1')
        .expect(200); // Espera sucesso

      // Verifica se o jogo foi encontrado corretamente
      expect(response.body.success).toBe(true);
      expect(response.body.game.id).toBe(1);
      expect(gameServices.getGameById).toHaveBeenCalledWith(1); // Verifica se foi chamado com ID correto
    });

  });

  // TESTES DA ROTA DE LISTAGEM (GET /games)
  describe('GET /games', () => {
    
    // Teste: Listagem bem-sucedida de todos os jogos
    it('deve listar todos os jogos', async () => {
      const mockResult = {
        status: 200,
        success: true,
        games: [
          { id: 1, name: 'Game 1' },
          { id: 2, name: 'Game 2' }
        ]
      };

      // Configura o mock para retornar a lista de jogos
      gameServices.getAllGames.mockResolvedValue(mockResult);

      const response = await request(app)
        .get('/games')
        .expect(200);

      // Verifica se a listagem funcionou
      expect(response.body.success).toBe(true);
      expect(response.body.games).toHaveLength(2);
      expect(gameServices.getAllGames).toHaveBeenCalled();
    });
  });
});
