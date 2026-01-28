import React, { useState } from 'react';
import { userService } from '../services/api';
import '../styles/Register.css';

const Register = ({ onRegisterSuccess, onBackToLogin }) => {
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    password: '',
    confirmPassword: ''
  });
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(false);
  const [success, setSuccess] = useState(false);

  /**
   * Atualiza o valor dos campos do formulário de cadastro.
   * @param {Object} e Evento do input
   */
  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
    setError(''); // Limpar erro quando usuário digita
  };

  /**
   * Valida os dados do formulário de cadastro.
   * @returns {boolean} True se válido, false caso contrário
   */
  const validateForm = () => {
    if (!formData.name || !formData.email || !formData.password || !formData.confirmPassword) {
      setError('Todos os campos são obrigatórios.');
      return false;
    }

    if (formData.password.length < 6) {
      setError('A senha deve ter pelo menos 6 caracteres.');
      return false;
    }

    if (formData.password !== formData.confirmPassword) {
      setError('As senhas não coincidem.');
      return false;
    }

    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailRegex.test(formData.email)) {
      setError('Por favor, insira um email válido.');
      return false;
    }

    return true;
  };

  /**
   * Envia o formulário de cadastro.
   * @async
   * @param {Object} e Evento do formulário
   */
  const handleSubmit = async (e) => {
    e.preventDefault();
    
    if (!validateForm()) {
      return;
    }

    setLoading(true);
    setError('');

    try {
      const userData = {
        name: formData.name,
        email: formData.email,
        password: formData.password
      };

      const response = await userService.createUser(userData);
      setSuccess(true);
      
      // Após 2 segundos, volta para o login ou chama callback
      setTimeout(() => {
        if (onRegisterSuccess && response.user) {
          onRegisterSuccess(response.user);
        } else {
          onBackToLogin();
        }
      }, 2000);

    } catch (error) {
      console.error('Erro no cadastro:', error);
      setError(error.response?.data?.error || 'Erro ao criar conta');
    } finally {
      setLoading(false);
    }
  };

  if (success) {
    return (
      <div className="register-container success-container">
        <div className="success-message">
          <h2>✅ Conta criada com sucesso!</h2>
          <p>Você será redirecionado para o login em alguns segundos...</p>
        </div>
      </div>
    );
  }

  return (
    <div className="register-container">
      <div className="register-left">
        <div className="logo-container">
          <img src="/logo_site.png" alt="Playbox" className="logo" />
        </div>
        <button 
          type="button" 
          className="login-button"
          onClick={onBackToLogin}
          disabled={loading}
        >
          JÁ POSSUO CONTA
        </button>
      </div>
      
      <div className="register-right">
        <div className="register-form">
          <h1>CRIAR A SUA CONTA</h1>
          <p className="form-subtitle">Preencha o formulário</p>
          
          {error && <div className="error-message">{error}</div>}
          
          <form onSubmit={handleSubmit}>
            <div className="form-group">
              <input
                type="text"
                id="name"
                name="name"
                value={formData.name}
                onChange={handleChange}
                required
                disabled={loading}
                placeholder="Nome"
              />
            </div>

            <div className="form-group">
              <input
                type="email"
                id="email"
                name="email"
                value={formData.email}
                onChange={handleChange}
                required
                disabled={loading}
                placeholder="E-mail"
              />
            </div>

            <div className="form-group">
              <input
                type="password"
                id="password"
                name="password"
                value={formData.password}
                onChange={handleChange}
                required
                disabled={loading}
                placeholder="Senha"
              />
            </div>

            <div className="form-group">
              <input
                type="password"
                id="confirmPassword"
                name="confirmPassword"
                value={formData.confirmPassword}
                onChange={handleChange}
                required
                disabled={loading}
                placeholder="Confirmar Senha"
              />
            </div>

            <button 
              type="submit" 
              className="submit-button"
              disabled={loading}
            >
              {loading ? 'CRIANDO...' : 'CRIAR'}
            </button>
          </form>
        </div>
      </div>
    </div>
  );
};

export default Register;
