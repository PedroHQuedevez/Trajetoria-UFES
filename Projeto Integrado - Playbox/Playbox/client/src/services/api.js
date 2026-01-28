import axios from 'axios';

/**
 * API Service para Playbox
 * 
 * Estrutura de Rotas:
 * - /auth/*    - Autenticação (login, logout, verificação, recuperação de senha)
 * - /users/*   - Operações com usuários (CRUD)
 * - /admin/*   - Operações administrativas
 * - /games/*   - Operações com jogos (futuro)
 */
/**
 * Serviço de comunicação com a API backend.
 * Define métodos para requisições HTTP.
 * @module api
 */

const API_BASE_URL = process.env.REACT_APP_API_URL || 'http://localhost:5000';

const api = axios.create({
  baseURL: API_BASE_URL,
  headers: {
    'Content-Type': 'application/json',
  },
});

// Interceptador para adicionar o token de autenticação automaticamente
api.interceptors.request.use(
  (config) => {
    const token = localStorage.getItem('token');
    if (token) {
      config.headers.Authorization = `Bearer ${token}`;
    }
    return config;
  },
  (error) => {
    return Promise.reject(error);
  }
);

// Interceptador para lidar com respostas de erro de autenticação
api.interceptors.response.use(
  (response) => response,
  (error) => {
    if (error.response?.status === 401 || error.response?.status === 403) {
      // Token inválido ou expirado, fazer logout apenas se não for uma tentativa de login
      const isLoginAttempt = error.config?.url?.includes('/auth/login');
      if (!isLoginAttempt) {
        localStorage.removeItem('token');
        localStorage.removeItem('user');
        // Não redirecionar automaticamente, deixar o App.js gerenciar isso
      }
    }
    return Promise.reject(error);
  }
);

// Serviços de autenticação
export const authService = {
  // Login
  /**
   * Realiza login do usuário.
   * @async
   * @param {string} email Email do usuário
   * @param {string} password Senha do usuário
   * @returns {Promise<Object>} Dados do usuário e token
   */
  login: async (email, password) => {
    const response = await api.post('/auth/login', { email, password });
    if (response.data.token) {
      localStorage.setItem('token', response.data.token);
      localStorage.setItem('user', JSON.stringify(response.data.user));
    }
    return response.data;
  },

  // Logout
  /**
   * Realiza logout do usuário.
   * @async
   * @returns {Promise<void>}
   */
  logout: async () => {
    try {
      await api.post('/auth/logout');
    } catch (error) {
      console.log('Erro no logout:', error);
    } finally {
      localStorage.removeItem('token');
      localStorage.removeItem('user');
    }
  },

  // Verificar se está logado
  /**
   * Verifica se o token do usuário é válido.
   * @async
   * @returns {Promise<Object>} Dados do usuário
   */
  verifyToken: async () => {
    const response = await api.get('/auth/verify');
    return response.data;
  },

  // Alterar senha
  /**
   * Altera a senha do usuário.
   * @async
   * @param {string} currentPassword Senha atual
   * @param {string} newPassword Nova senha
   * @returns {Promise<Object>} Dados da resposta
   */
  changePassword: async (currentPassword, newPassword) => {
    const response = await api.put('/auth/changePassword', {
      currentPassword,
      newPassword
    });
    return response.data;
  },

  // Verificar se está logado (local)
  /**
   * Verifica se o usuário está logado.
   * @returns {boolean}
   */
  isLoggedIn: () => {
    return !!localStorage.getItem('token');
  },

  // Obter usuário atual
  /**
   * Retorna o usuário atual salvo localmente.
   * @returns {Object|null} Usuário ou null
   */
  getCurrentUser: () => {
    const user = localStorage.getItem('user');
    return user ? JSON.parse(user) : null;
  },

  // Solicitar recuperação de senha
  /**
   * Solicita recuperação de senha.
   * @async
   * @param {string} email Email do usuário
   * @returns {Promise<Object>} Dados da resposta
   */
  forgotPassword: async (email) => {
    const response = await api.post('/auth/forgotPassword', { email });
    return response.data;
  },

  // Redefinir senha com token
  /**
   * Redefine a senha usando token.
   * @async
   * @param {string} token Token de recuperação
   * @param {string} newPassword Nova senha
   * @returns {Promise<Object>} Dados da resposta
   */
  resetPassword: async (token, newPassword) => {
    const response = await api.post('/auth/resetPassword', { token, newPassword });
    return response.data;
  }
};

// Serviços para usuários
export const userService = {
  // Listar todos os usuários (admin)
  /**
   * Lista todos os usuários (admin).
   * @async
   * @returns {Promise<Object>} Lista de usuários
   */
  getAllUsers: async () => {
    const response = await api.get('/users');
    return response.data;
  },

  // Obter usuário por ID
  /**
   * Busca usuário por ID.
   * @async
   * @param {number} id ID do usuário
   * @returns {Promise<Object>} Dados do usuário
   */
  getUserById: async (id) => {
    const response = await api.get(`/users/${id}`);
    return response.data;
  },

  // Criar usuário
  /**
   * Cria novo usuário.
   * @async
   * @param {Object} userData Dados do usuário
   * @returns {Promise<Object>} Dados do usuário criado
   */
  createUser: async (userData) => {
    const response = await api.post('/users', userData);
    return response.data;
  },

  // Atualizar usuário
  /**
   * Atualiza dados do usuário.
   * @async
   * @param {number} id ID do usuário
   * @param {Object} userData Dados do usuário
   * @returns {Promise<Object>} Dados do usuário atualizado
   */
  updateUser: async (id, userData) => {
    const response = await api.put(`/users/${id}`, userData);
    return response.data;
  },

  // Deletar usuário (admin)
  /**
   * Deleta usuário (admin).
   * @async
   * @param {number} id ID do usuário
   * @returns {Promise<Object>} Dados da resposta
   */
  deleteUser: async (id) => {
    const response = await api.delete(`/users/${id}`);
    return response.data;
  },

  // Deletar a própria conta
  /**
   * Deleta a própria conta do usuário.
   * @async
   * @returns {Promise<Object>} Dados da resposta
   */
  deleteOwnAccount: async () => {
    const response = await api.delete('/users/me');
    return response.data;
  }
};

// Serviços para jogos
export const gameService = {
  // Listar todos os jogos
  /**
   * Lista todos os jogos.
   * @async
   * @returns {Promise<Object>} Lista de jogos
   */
  getGames: async () => {
    const response = await api.get('/games');
    return response.data;
  },

  // Obter um jogo específico
  /**
   * Busca jogo por ID.
   * @async
   * @param {number} id ID do jogo
   * @returns {Promise<Object>} Dados do jogo
   */
  getGame: async (id) => {
    const response = await api.get(`/games/${id}`);
    return response.data;
  },

  // Criar um novo jogo (admin)
  /**
   * Cria novo jogo (admin).
   * @async
   * @param {Object} gameData Dados do jogo
   * @returns {Promise<Object>} Dados do jogo criado
   */
  createGame: async (gameData) => {
    const response = await api.post('/games', gameData);
    return response.data;
  },

  // Atualizar um jogo (admin)
  /**
   * Atualiza dados do jogo (admin).
   * @async
   * @param {number} id ID do jogo
   * @param {Object} gameData Dados do jogo
   * @returns {Promise<Object>} Dados do jogo atualizado
   */
  updateGame: async (id, gameData) => {
    const response = await api.put(`/games/${id}`, gameData);
    return response.data;
  },

  // Deletar um jogo (admin)
  /**
   * Deleta jogo (admin).
   * @async
   * @param {number} id ID do jogo
   * @returns {Promise<Object>} Dados da resposta
   */
  deleteGame: async (id) => {
    const response = await api.delete(`/games/${id}`);
    return response.data;
  },

  // Buscar jogos por gênero
  /**
   * Busca jogos por gênero.
   * @async
   * @param {string} genre Nome do gênero
   * @returns {Promise<Object>} Lista de jogos
   */
  getGamesByGenre: async (genre) => {
    const response = await api.get(`/games/genre/${genre}`);
    return response.data;
  }
};

// Serviços de desenvolvimento/debug
export const devService = {
  // Listar todos os endpoints disponíveis
  /**
   * Lista todos os endpoints disponíveis.
   * @returns {Object} Endpoints agrupados
   */
  listEndpoints: () => {
    return {
      auth: [
        'POST /auth/login - Fazer login',
        'GET /auth/verify - Verificar token',
        'PUT /auth/changePassword - Alterar senha',
        'POST /auth/logout - Fazer logout',
        'POST /auth/forgotPassword - Solicitar recuperação de senha',
        'POST /auth/resetPassword - Redefinir senha com token'
      ],
      users: [
        'GET /users - Listar todos os usuários (admin)',
        'GET /users/:id - Buscar usuário por ID',
        'POST /users - Criar usuário',
        'PUT /users/:id - Atualizar usuário',
        'DELETE /users/:id - Deletar usuário (admin)',
        'DELETE /users/me - Deletar a própria conta'
      ],
      games: [
        'GET /games - Listar todos os jogos',
        'GET /games/:id - Obter um jogo específico',
        'POST /games - Criar um novo jogo (admin)',
        'PUT /games/:id - Atualizar um jogo (admin)',
        'DELETE /games/:id - Deletar um jogo (admin)',
        'GET /games/genre/:genre - Buscar jogos por gênero'
      ],
      general: [
        'GET / - Informações da API'
      ]
    };
  },

  // Testar todas as rotas públicas
  /**
   * Testa todas as rotas públicas da API.
   * @async
   * @returns {Promise<Object>} Resultados dos testes
   */
  testPublicRoutes: async () => {
    const results = {};
    
    try {
      const apiInfo = await api.get('/');
      results.api = { status: 'OK', data: apiInfo.data };
    } catch (error) {
      results.api = { status: 'ERROR', error: error.message };
    }

    return results;
  }
};

// Serviços para reviews
export const reviewService = {
  // Criar nova review
  /**
   * Cria nova review.
   * @async
   * @param {Object} reviewData Dados da review
   * @returns {Promise<Object>} Dados da review criada
   */
  createReview: async (reviewData) => {
    const response = await api.post('/reviews', reviewData);
    return response.data;
  },

  // Buscar reviews por ID do jogo
  /**
   * Busca reviews por ID do jogo.
   * @async
   * @param {number} gameId ID do jogo
   * @returns {Promise<Object>} Lista de reviews
   */
  getReviewsByGame: async (gameId) => {
    const response = await api.get(`/reviews/game/${gameId}`);
    return response.data;
  },

  // Buscar reviews por ID do usuário
  /**
   * Busca reviews por ID do usuário.
   * @async
   * @param {number} userId ID do usuário
   * @returns {Promise<Object>} Lista de reviews
   */
  getReviewsByUser: async (userId) => {
    const response = await api.get(`/reviews/user/${userId}`);
    return response.data;
  },

  // Atualizar review
  /**
   * Atualiza uma review.
   * @async
   * @param {number} reviewId ID da review
   * @param {Object} reviewData Dados da review
   * @returns {Promise<Object>} Dados da review atualizada
   */
  updateReview: async (reviewId, reviewData) => {
    const response = await api.put(`/reviews/${reviewId}`, reviewData);
    return response.data;
  },

  // Deletar review
  /**
   * Deleta uma review.
   * @async
   * @param {number} reviewId ID da review
   * @param {Object} reviewData Dados da review
   * @returns {Promise<Object>} Dados da resposta
   */
  deleteReview: async (reviewId, reviewData) => {
    const response = await api.delete(`/reviews/${reviewId}`, { data: reviewData });
    return response.data;
  }
};

// Serviços para catálogos (favoritos)
export const catalogService = {
  // Buscar catálogos do usuário
  /**
   * Busca catálogos do usuário.
   * @async
   * @param {number} userId ID do usuário
   * @returns {Promise<Object>} Lista de catálogos
   */
  getUserCatalogs: async (userId) => {
    const response = await api.get(`/catalogs/user/${userId}`);
    return response.data;
  },

  // Criar catálogo
  /**
   * Cria novo catálogo.
   * @async
   * @param {Object} catalogData Dados do catálogo
   * @returns {Promise<Object>} Dados do catálogo criado
   */
  createCatalog: async (catalogData) => {
    const response = await api.post('/catalogs', catalogData);
    return response.data;
  },

  // Buscar catálogo por ID
  /**
   * Busca catálogo por ID.
   * @async
   * @param {number} catalogId ID do catálogo
   * @returns {Promise<Object>} Dados do catálogo
   */
  getCatalogById: async (catalogId) => {
    const response = await api.get(`/catalogs/${catalogId}`);
    return response.data;
  },

  // Adicionar jogo aos favoritos
  /**
   * Adiciona jogo aos favoritos do usuário.
   * @async
   * @param {number} userId ID do usuário
   * @param {number} gameId ID do jogo
   * @returns {Promise<Object>} Dados da resposta
   */
  addGameToFavorites: async (userId, gameId) => {
    // Primeiro, verificar se já existe um catálogo "Favoritos" para o usuário
    const catalogs = await api.get(`/catalogs/user/${userId}`);
    let favoritesCatalog = catalogs.data.catalogs.find(catalog => catalog.userId === userId);
    
    // Se não existir, criar o catálogo "Favoritos"
    if (!favoritesCatalog) {
      const newCatalog = await api.post('/catalogs', {
        name: 'Favoritos',
        userId: userId
      });
      favoritesCatalog = newCatalog.data.catalog;
    }
    
    // Adicionar o jogo ao catálogo de favoritos
    const response = await api.post(`/catalogs/${favoritesCatalog.id}/games`, {
      gameId: gameId
    });
    return response.data;
  },

  // Remover jogo dos favoritos
  /**
   * Remove jogo dos favoritos do usuário.
   * @async
   * @param {number} userId ID do usuário
   * @param {number} gameId ID do jogo
   * @returns {Promise<Object>} Dados da resposta
   */
  removeGameFromFavorites: async (userId, gameId) => {
    // Buscar o catálogo "Favoritos" do usuário
    const catalogs = await api.get(`/catalogs/user/${userId}`);
    const favoritesCatalog = catalogs.data.catalogs.find(catalog => catalog.userId === userId);
    
    if (!favoritesCatalog) {
      throw new Error('Catálogo de favoritos não encontrado');
    }
    
    // Remover o jogo do catálogo de favoritos
    const response = await api.delete(`/catalogs/${favoritesCatalog.id}/games/${gameId}`);
    return response.data;
  },

  // Verificar se jogo está nos favoritos
  /**
   * Verifica se o jogo está nos favoritos do usuário.
   * @async
   * @param {number} userId ID do usuário
   * @param {number} gameId ID do jogo
   * @returns {Promise<boolean>} True se estiver nos favoritos
   */
  isGameInFavorites: async (userId, gameId) => {
    try {
      const catalogs = await api.get(`/catalogs/user/${userId}`);
      const favoritesCatalog = catalogs.data.catalogs.find(catalog => catalog.userId === userId);
      
      if (!favoritesCatalog) {
        return false;
      }
      
      return favoritesCatalog.games.some(game => game.id === gameId);
    } catch (error) {
      console.error('Erro ao verificar favoritos:', error);
      return false;
    }
  },

  // Buscar jogos favoritos do usuário
  /**
   * Busca jogos favoritos do usuário.
   * @async
   * @param {number} userId ID do usuário
   * @returns {Promise<Object>} Lista de jogos favoritos
   */
  getFavoriteGames: async (userId) => {
    try {
      const catalogs = await api.get(`/catalogs/user/${userId}`);
      const favoritesCatalog = catalogs.data.catalogs.find(catalog => catalog.userId === userId);
      
      if (!favoritesCatalog) {
        return { games: [] };
      }
      
      const catalogDetails = await api.get(`/catalogs/${favoritesCatalog.id}`);
      return { games: catalogDetails.data.catalog.games || [] };
    } catch (error) {
      console.error('Erro ao buscar jogos favoritos:', error);
      return { games: [] };
    }
  }
};

export default api;
