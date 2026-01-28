/**
 * @fileoverview Rotas de jogos
 * @description Contém todas as rotas relacionadas ao gerenciamento de jogos
 */

const express = require('express');
const gameServices = require('../services/gameServices.js');
const router = express.Router();

// === ROTAS DE JOGOS ===

/**
 * Criar jogo
 * @route POST /games
 * @param {Object} req.body - Dados do jogo
 * @returns {Object} Dados do jogo criado
 */
router.post('/', async (req, res) => {
    try {
        const gameData = req.body;
        const result = await gameServices.createGame(gameData);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao criar jogo:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Buscar jogo por ID
 * @route GET /games/:id
 * @param {string} req.params.id - ID do jogo
 * @returns {Object} Dados do jogo
 */
router.get('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const result = await gameServices.getGameById(Number(id));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao buscar jogo:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Buscar jogo por nome
 * @route GET /games/search
 * @param {string} req.query.name - Nome do jogo para busca
 * @returns {Object} Dados do jogo encontrado
 */
router.get('/search', async (req, res) => {
    try {
        const { name } = req.query;
        if (!name) {
            return res.status(400).json({ error: 'Nome do jogo é obrigatório.' });
        }
        const result = await gameServices.getGameByName(name);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao buscar jogo por nome:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Listar todos os jogos
 * @route GET /games
 * @returns {Object} Lista de todos os jogos
 */
router.get('/', async (req, res) => {
    try {
        const result = await gameServices.getAllGames();
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao listar jogos:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Atualizar jogo
 * @route PUT /games/:id
 * @param {string} req.params.id - ID do jogo
 * @param {Object} req.body - Novos dados do jogo
 * @returns {Object} Dados do jogo atualizado
 */
router.put('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const gameData = req.body;
        const result = await gameServices.updateGame(Number(id), gameData);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao atualizar jogo:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Deletar jogo
 * @route DELETE /games/:id
 * @param {string} req.params.id - ID do jogo
 * @returns {Object} Mensagem de sucesso
 */
router.delete('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const result = await gameServices.deleteGame(Number(id));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao deletar jogo:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Buscar jogos por gênero
 * @route GET /games/genre/:genre
 * @param {string} req.params.genre - Gênero para filtrar
 * @returns {Object} Lista de jogos do gênero especificado
 */
router.get('/genre/:genre', async (req, res) => {
    try {
        const { genre } = req.params;
        const result = await gameServices.getGamesByGenre(genre);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao buscar jogos por gênero:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Rota para recalcular todas as médias de avaliação (rota administrativa)
 * @route POST /games/admin/recalculateAverages
 * @returns {Object} Resultado da operação de recálculo
 */
router.post('/admin/recalculateAverages', async (req, res) => {
    try {
        const result = await gameServices.recalculateAllGameAverages();
        res.status(200).json({ 
            message: 'Médias de avaliação recalculadas com sucesso',
            ...result
        });
    } catch (error) {
        console.error('Erro ao recalcular médias:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

module.exports = router;