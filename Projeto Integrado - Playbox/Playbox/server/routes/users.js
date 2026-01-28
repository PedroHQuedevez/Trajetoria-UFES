/**
 * @fileoverview Rotas de usuários
 * @description Contém todas as rotas relacionadas ao gerenciamento de usuários
 */

const express = require('express');
const userServices = require('../services/userServices.js');
const authenticateToken = userServices.authenticateToken;
const requireAdmin = userServices.requireAdmin;
const router = express.Router();

// === ROTAS DE USUÁRIOS ===

/**
 * Criar usuário
 * @route POST /users
 * @param {Object} req.body - Dados do usuário
 * @param {string} req.body.name - Nome do usuário
 * @param {string} req.body.email - Email do usuário
 * @param {string} req.body.password - Senha do usuário
 * @returns {Object} Dados do usuário criado
 */
router.post('/', async (req, res) => {
    try {
        const userData = req.body;
        const result = await userServices.createUser(userData);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao criar usuário:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Listar todos os usuários (apenas admins)
 * @route GET /users
 * @middleware authenticateToken, requireAdmin
 * @returns {Object} Lista de todos os usuários
 */
router.get('/', authenticateToken, requireAdmin, async (req, res) => {
    try {
        const result = await userServices.getAllUsers();
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao listar usuários:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Buscar usuário por ID
 * @route GET /users/:id
 * @middleware authenticateToken
 * @param {string} req.params.id - ID do usuário
 * @returns {Object} Dados do usuário
 * @description Usuário pode ver seu próprio perfil ou admin pode ver qualquer um
 */
router.get('/:id', authenticateToken, async (req, res) => {
    try {
        const { id } = req.params;
        const userId = Number(id);

        // Verificar se o usuário está tentando acessar seu próprio perfil ou se é admin
        if (req.user.id !== userId && !req.user.isAdmin) {
            return res.status(403).json({ error: 'Acesso negado. Você só pode ver seu próprio perfil.' });
        }

        const user = await userServices.getUserById(userId);
        res.status(user.status).json(user);
    } catch (error) {
        console.error('Erro ao buscar usuário:', error);
        res.status(500).json({ error: 'Erro interno do servidor.' });
    }
});

/**
 * Atualizar usuário
 * @route PUT /users/:id
 * @middleware authenticateToken
 * @param {string} req.params.id - ID do usuário
 * @param {Object} req.body - Novos dados do usuário
 * @returns {Object} Dados do usuário atualizado
 * @description Usuário pode atualizar seu próprio perfil ou admin pode atualizar qualquer um
 */
router.put('/:id', authenticateToken, async (req, res) => {
    try {
        const { id } = req.params;
        const userId = Number(id);

        // Verificar se o usuário está tentando atualizar seu próprio perfil ou se é admin
        if (req.user.id !== userId && !req.user.isAdmin) {
            return res.status(403).json({ error: 'Acesso negado. Você só pode atualizar seu próprio perfil.' });
        }

        const result = await userServices.updateUser(userId, req.body);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao atualizar usuário:', error);
        res.status(400).json({ error: error.message });
    }
});

// Rota para excluir a própria conta
router.delete('/me', authenticateToken, async (req, res) => {
    try {
        const userId = req.user.id;
        const result = await userServices.deleteOwnUser(userId);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao excluir a própria conta:', error);
        res.status(400).json({ error: error.message });
    }
});

// Rota para admin excluir qualquer usuário (exceto 'me')
router.delete('/:id', authenticateToken, requireAdmin, async (req, res) => {
    try {
        const { id } = req.params;
        if (id === 'me') {
            return res.status(400).json({ error: "Use a rota /users/me para excluir a própria conta." });
        }
        const userId = Number(id);
        const result = await userServices.deleteUser(userId);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao deletar usuário:', error);
        res.status(400).json({ error: error.message });
    }
});

module.exports = router;
