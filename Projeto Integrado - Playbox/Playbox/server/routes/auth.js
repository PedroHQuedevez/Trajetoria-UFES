/**
 * @fileoverview Rotas de autenticação
 * @description Contém todas as rotas relacionadas à autenticação e recuperação de senha
 */

const express = require('express');
const userServices = require('../services/userServices.js');
const { authenticateToken } = require('../services/userServices.js');
const router = express.Router();

// Chave secreta para JWT
const JWT_SECRET = process.env.JWT_SECRET || 'chave-secreta';

// === ROTAS DE AUTENTICAÇÃO ===

/**
 * Login do usuário
 * @route POST /auth/login
 * @param {Object} req.body - Dados de login
 * @param {string} req.body.email - Email do usuário
 * @param {string} req.body.password - Senha do usuário
 * @returns {Object} Token JWT e dados do usuário
 */
router.post('/login', async (req, res) => {
    const { email, password } = req.body;

    if (!email || !password) {
        return res.status(400).json({ error: 'Email e senha são obrigatórios.' });
    }

    try {
        const result = await userServices.authenticateUser(email, password);
        res.status(result.status).json(result);
    } catch (error) {
        console.error('Erro ao autenticar usuário:', error);
        res.status(400).json({ error: error.message });
    }
});

/**
 * Verificar se o token é válido
 * @route GET /auth/verify
 * @middleware authenticateToken
 * @returns {Object} Dados do usuário logado
 */
router.get('/verify', authenticateToken, (req, res) => {
    res.json({
        message: 'Token válido',
        user: {
            id: req.user.id,
            name: req.user.name,
            email: req.user.email,
            isAdmin: req.user.isAdmin
        }
    });
});

/**
 * Alterar senha do usuário logado
 * @route PUT /auth/changePassword
 * @middleware authenticateToken
 * @param {Object} req.body - Dados para alteração de senha
 * @param {string} req.body.currentPassword - Senha atual
 * @param {string} req.body.newPassword - Nova senha
 * @returns {Object} Mensagem de sucesso
 */
router.put('/changePassword', authenticateToken, async (req, res) => {
    try {
        const { currentPassword, newPassword } = req.body;

        if (!currentPassword || !newPassword) {
            return res.status(400).json({ error: 'Senha atual e nova senha são obrigatórias.' });
        }

        const result = await userServices.changePassword(req.user.id, currentPassword, newPassword);
        res.status(result.status).json(result);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
});

/**
 * Logout (opcional - no frontend, basta remover o token do localStorage)
 * @route POST /auth/logout
 * @returns {Object} Mensagem de logout
 */
router.post('/logout', (req, res) => {
    res.json({ message: 'Logout realizado com sucesso!' });
});

// === ROTAS DE RECUPERAÇÃO DE SENHA ===

/**
 * Solicitar recuperação de senha
 * @route POST /auth/forgotPassword
 * @param {Object} req.body - Dados para recuperação
 * @param {string} req.body.email - Email do usuário
 * @returns {Object} Token de recuperação (desenvolvimento) ou mensagem
 */
router.post('/forgotPassword', async (req, res) => {
    try {
        const { email } = req.body;

        if (!email) {
            return res.status(400).json({ error: 'Email é obrigatório.' });
        }

        const result = await userServices.requestPasswordReset(email, JWT_SECRET);
        res.status(result.status).json(result);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

/**
 * Redefinir senha com token
 * @route POST /auth/resetPassword
 * @param {Object} req.body - Dados para redefinição
 * @param {string} req.body.token - Token de recuperação
 * @param {string} req.body.newPassword - Nova senha
 * @returns {Object} Mensagem de sucesso
 */
router.post('/resetPassword', async (req, res) => {
    try {
        const { token, newPassword } = req.body;

        if (!token || !newPassword) {
            return res.status(400).json({ error: 'Token e nova senha são obrigatórios.' });
        }

        const result = await userServices.resetPassword(token, newPassword, JWT_SECRET);
        res.status(result.status).json(result);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
});

module.exports = router;
