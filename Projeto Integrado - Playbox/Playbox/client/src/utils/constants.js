/**
 * Constantes globais da aplicação.
 * @module constants
 */
/**
 * URL base da API utilizada pelo frontend.
 * @type {string}
 */
export const API_BASE_URL = 'http://localhost:3000';

/**
 * Rotas principais da aplicação.
 * @type {Object}
 */
export const ROUTES = {
  LOGIN: '/login',
  REGISTER: '/register',
  DASHBOARD: '/dashboard',
  USERS: '/users'
};

/**
 * Mensagens padrão utilizadas na aplicação.
 * @type {Object}
 */
export const MESSAGES = {
  LOADING: 'Carregando...',
  ERROR_GENERIC: 'Erro inesperado. Tente novamente.',
  SUCCESS_CREATE: 'Criado com sucesso!',
  SUCCESS_UPDATE: 'Atualizado com sucesso!',
  SUCCESS_DELETE: 'Removido com sucesso!'
};

/**
 * Regras e expressões de validação utilizadas nos formulários.
 * @type {Object}
 */
export const VALIDATION = {
  MIN_PASSWORD_LENGTH: 6,
  EMAIL_REGEX: /^[^\s@]+@[^\s@]+\.[^\s@]+$/
};
