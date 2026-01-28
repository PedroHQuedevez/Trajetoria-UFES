/**
 * @fileoverview Roteador principal da API
 * @description Organiza e centraliza todas as rotas da aplicação
 */

const express = require('express');
const router = express.Router();

// Importar todas as rotas
const authRoutes = require('./auth.js');
const userRoutes = require('./users.js');
const gameRoutes = require('./games.js');
const reviewRoutes = require('./reviews.js');
const catalogRoutes = require('./catalogs.js');

/**
 * Rota de teste e informações da API
 * @route GET /
 * @description Retorna informações básicas da API e endpoints disponíveis
 * @returns {Object} Informações da API
 */
router.get('/', (req, res) => {
    res.json({ 
        message: 'API Playbox funcionando!',
        version: '1.0.0',
        endpoints: {
            auth: '/auth/*',
            users: '/users/*',
            games: '/games/*',
            reviews: '/reviews/*',
            catalogs: '/catalogs/*'
        }
    });
});

// Registrar as rotas com seus prefixos
router.use('/auth', authRoutes);
router.use('/users', userRoutes);
router.use('/games', gameRoutes);
router.use('/reviews', reviewRoutes);
router.use('/catalogs', catalogRoutes);

module.exports = router;
