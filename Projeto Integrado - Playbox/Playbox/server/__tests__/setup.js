// CONFIGURAÇÃO GLOBAL PARA TESTES

require('dotenv').config({ path: '../.env' });

// MOCK DO PRISMA (BANCO DE DADOS SIMULADO)
// Cria um objeto mock que simula todas as operações do Prisma
const mockPrisma = {
  // Simula conexão e desconexão com o banco
  $connect: jest.fn().mockResolvedValue(undefined),
  $disconnect: jest.fn().mockResolvedValue(undefined),
  
  // Mock das operações da tabela 'user'
  user: {
    findUnique: jest.fn(),    // Buscar um usuário específico
    findMany: jest.fn(),      // Buscar múltiplos usuários
    create: jest.fn(),        // Criar novo usuário
    update: jest.fn(),        // Atualizar usuário existente
    delete: jest.fn(),        // Deletar usuário
  },
  
  // Mock das operações da tabela 'game'
  game: {
    findMany: jest.fn(),      // Buscar múltiplos jogos
    findUnique: jest.fn(),    // Buscar um jogo específico
    create: jest.fn(),        // Criar novo jogo
    upsert: jest.fn(),        // Criar ou atualizar jogo
  },
  
  // Mock das operações da tabela 'review'
  review: {
    findMany: jest.fn(),      // Buscar múltiplas avaliações
    create: jest.fn(),        // Criar nova avaliação
    update: jest.fn(),        // Atualizar avaliação existente
    delete: jest.fn(),        // Deletar avaliação
  }
};

// Substitui o módulo real do Prisma pelo mock em todos os testes
jest.mock('../services/prisma.js', () => mockPrisma);

// CONFIGURAÇÃO DO AMBIENTE DE TESTE
process.env.NODE_ENV = 'test';
process.env.JWT_SECRET = 'test-secret-key';
process.env.ADMIN_EMAIL = 'admin@test.com';
process.env.ADMIN_PASSWORD = 'admin123';

module.exports = { mockPrisma };
