// Funções utilitárias para validação
/**
 * Funções utilitárias para validação de dados de formulários.
 * @module validation
 */
/**
 * Valida se o email possui formato válido.
 * @param {string} email Email a ser validado
 * @returns {boolean} True se válido, false caso contrário
 */
export const validateEmail = (email) => {
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return emailRegex.test(email);
};

/**
 * Valida se a senha possui o tamanho mínimo.
 * @param {string} password Senha a ser validada
 * @returns {boolean} True se válido, false caso contrário
 */
export const validatePassword = (password) => {
  return password && password.length >= 6;
};

/**
 * Valida se o campo é obrigatório e não está vazio.
 * @param {string} value Valor a ser validado
 * @returns {boolean} True se válido, false caso contrário
 */
export const validateRequired = (value) => {
  return value && value.trim().length > 0;
};

/**
 * Valida um formulário com base nas regras fornecidas.
 * @param {Object} formData Dados do formulário
 * @param {Object} rules Regras de validação
 * @returns {Object} Objeto com isValid e errors
 */
export const validateForm = (formData, rules) => {
  const errors = {};
  
  for (const [field, validations] of Object.entries(rules)) {
    for (const validation of validations) {
      const result = validation(formData[field]);
      if (result !== true) {
        errors[field] = result;
        break;
      }
    }
  }
  
  return {
    isValid: Object.keys(errors).length === 0,
    errors
  };
};
