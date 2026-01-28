/**
 * @fileoverview Rotas de catálogos
 * @description Contém todas as rotas relacionadas ao gerenciamento de catálogos de jogos
 */

const express = require('express');
const catalogServices = require('../services/catalogServices.js');
const router = express.Router();

// === ROTAS DE CATÁLOGOS ===

/**
 * Criar catálogo
 * @route POST /catalogs
 * @param {Object} req.body - Dados do catálogo
 * @param {string} req.body.name - Nome do catálogo
 * @param {number} req.body.userId - ID do usuário proprietário
 * @returns {Object} Dados do catálogo criado
 */
router.post('/', async (req, res) => {
    try {
        const catalogData = req.body;
        const result = await catalogServices.createCatalog(catalogData);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao criar catálogo:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Buscar catálogo por ID
 * @route GET /catalogs/:id
 * @param {string} req.params.id - ID do catálogo
 * @returns {Object} Dados do catálogo com jogos e informações do usuário
 */
router.get('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const result = await catalogServices.getCatalogById(Number(id));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao buscar catálogo:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Listar catálogos por ID de usuário
 * @route GET /catalogs/user/:userId
 * @param {string} req.params.userId - ID do usuário
 * @returns {Object} Lista de catálogos do usuário
 */
router.get('/user/:userId', async (req, res) => {
    try {
        const { userId } = req.params;
        const result = await catalogServices.getCatalogsByUserId(Number(userId));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao listar catálogos:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Atualizar catálogo
 * @route PUT /catalogs/:id
 * @param {string} req.params.id - ID do catálogo
 * @param {Object} req.body - Novos dados do catálogo
 * @returns {Object} Dados do catálogo atualizado
 */
router.put('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const catalogData = req.body;
        const result = await catalogServices.updateCatalog(Number(id), catalogData);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao atualizar catálogo:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Deletar catálogo
 * @route DELETE /catalogs/:id
 * @param {string} req.params.id - ID do catálogo
 * @returns {Object} Mensagem de sucesso
 */
router.delete('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const result = await catalogServices.deleteCatalog(Number(id));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao deletar catálogo:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Adicionar jogo ao catálogo
 * @route POST /catalogs/:catalogId/games
 * @param {string} req.params.catalogId - ID do catálogo
 * @param {Object} req.body - Dados do jogo
 * @param {number} req.body.gameId - ID do jogo a ser adicionado
 * @returns {Object} Mensagem de sucesso
 */
router.post('/:catalogId/games', async (req, res) => {
    try {
        const { catalogId } = req.params;
        const { gameId } = req.body;
        const result = await catalogServices.addGameToCatalog(Number(catalogId), Number(gameId));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao adicionar jogo ao catálogo:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Remover jogo do catálogo
 * @route DELETE /catalogs/:catalogId/games/:gameId
 * @param {string} req.params.catalogId - ID do catálogo
 * @param {string} req.params.gameId - ID do jogo a ser removido
 * @returns {Object} Mensagem de sucesso
 */
router.delete('/:catalogId/games/:gameId', async (req, res) => {
    try {
        const { catalogId, gameId } = req.params;
        const result = await catalogServices.removeGameFromCatalog(Number(catalogId), Number(gameId));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao remover jogo do catálogo:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Listar todos os catálogos
 * @route GET /catalogs
 * @returns {Object} Lista de todos os catálogos com jogos e usuários
 */
router.get('/', async (req, res) => {
    try {
        const result = await catalogServices.getAllCatalogs();
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao listar catálogos:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

module.exports = router;