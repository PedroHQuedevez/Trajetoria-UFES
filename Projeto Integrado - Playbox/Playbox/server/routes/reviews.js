/**
 * @fileoverview Rotas de avaliações (reviews)
 * @description Contém todas as rotas relacionadas ao gerenciamento de avaliações de jogos
 */

const express = require('express');
const reviewServices = require('../services/reviewServices.js');
const router = express.Router();

// === ROTAS DE AVALIAÇÕES ===

/**
 * Criar avaliação
 * @route POST /reviews
 * @param {Object} req.body - Dados da avaliação
 * @param {number} req.body.gameId - ID do jogo
 * @param {number} req.body.userId - ID do usuário
 * @param {number} req.body.gameplayRating - Avaliação do gameplay (0-5)
 * @param {number} req.body.visualRating - Avaliação visual (0-5)
 * @param {number} req.body.audioRating - Avaliação do áudio (0-5)
 * @param {number} req.body.difficultyRating - Avaliação da dificuldade (0-5)
 * @param {number} req.body.immersionRating - Avaliação da imersão (0-5)
 * @param {number} req.body.historyRating - Avaliação da história (0-5)
 * @param {string} req.body.comment - Comentário da avaliação
 * @returns {Object} Dados da avaliação criada
 */
router.post('/', async (req, res) => {
    try {
        const reviewData = req.body;
        const result = await reviewServices.createReview(reviewData);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao criar avaliação:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Buscar avaliação por ID
 * @route GET /reviews/:id
 * @param {string} req.params.id - ID da avaliação
 * @returns {Object} Dados da avaliação com informações do jogo e usuário
 */
router.get('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const result = await reviewServices.getReviewById(Number(id));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao buscar avaliação:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Listar avaliações por ID de jogo
 * @route GET /reviews/game/:gameId
 * @param {string} req.params.gameId - ID do jogo
 * @returns {Object} Lista de avaliações do jogo ordenadas por data
 * @description Retorna avaliações formatadas ordenadas por data de criação (mais recentes primeiro)
 */
router.get('/game/:gameId', async (req, res) => {
    try {
        const { gameId } = req.params;
        const result = await reviewServices.getReviewsByGameId(Number(gameId));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao listar avaliações:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Listar avaliações por ID de usuário
 * @route GET /reviews/user/:userId
 * @param {string} req.params.userId - ID do usuário
 * @returns {Object} Lista de avaliações do usuário com informações dos jogos
 */
router.get('/user/:userId', async (req, res) => {
    try {
        const { userId } = req.params;
        const result = await reviewServices.getReviewsByUserId(Number(userId));
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao listar avaliações do usuário:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Atualizar avaliação
 * @route PUT /reviews/:id
 * @param {string} req.params.id - ID da avaliação
 * @param {Object} req.body - Novos dados da avaliação
 * @param {number} req.body.gameplayRating - Nova avaliação do gameplay (0-5)
 * @param {number} req.body.visualRating - Nova avaliação visual (0-5)
 * @param {number} req.body.audioRating - Nova avaliação do áudio (0-5)
 * @param {number} req.body.difficultyRating - Nova avaliação da dificuldade (0-5)
 * @param {number} req.body.immersionRating - Nova avaliação da imersão (0-5)
 * @param {number} req.body.historyRating - Nova avaliação da história (0-5)
 * @param {string} req.body.comment - Novo comentário da avaliação
 * @returns {Object} Dados da avaliação atualizada
 */
router.put('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        const reviewData = req.body;
        // Supondo que o userId do usuário autenticado está em req.user.id
        const review = await reviewServices.getReviewById(Number(id));
        if (!review || review.review.userId !== req.body.userId) {
            return res.status(403).json({ error: 'Permissão negada: apenas o autor pode editar.' });
        }
        const result = await reviewServices.updateReview(Number(id), reviewData);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao atualizar avaliação:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Deletar avaliação
 * @route DELETE /reviews/:id
 * @param {string} req.params.id - ID da avaliação
 * @returns {Object} Mensagem de sucesso
 * @description Remove a avaliação e atualiza a média do jogo relacionado
 */
router.delete('/:id', async (req, res) => {
    try {
        const { id } = req.params;
        console.log('Tentando deletar review com ID:', id);
        console.log('req.params:', req.params);
        console.log('req.body:', req.body);
        
        // Verificar se o ID é válido
        if (!id || isNaN(Number(id))) {
            return res.status(400).json({ error: 'ID da avaliação inválido.' });
        }
        
        const review = await reviewServices.getReviewById(Number(id));
        
        if (!review || review.status !== 200) {
            return res.status(404).json({ error: 'Avaliação não encontrada.' });
        }
        
        if (review.review.userId !== req.body.userId) {
            return res.status(403).json({ error: 'Permissão negada: apenas o autor pode deletar.' });
        }
        
        const result = await reviewServices.deleteReview(Number(id), req.body);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao deletar avaliação:', error);
        res.status(400).json({ error: error.message });
    }
});

module.exports = router;