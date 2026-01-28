import React, { useState } from 'react';
import { authService } from '../services/api';
import '../styles/Login.css';

const Login = ({ onLoginSuccess, onShowRegister, onShowForgotPassword }) => {
  const [formData, setFormData] = useState({
    email: '',
    password: ''
  });
  const [error, setError] = useState('');
  const [loading, setLoading] = useState(false);

  /**
   * Atualiza o valor dos campos do formulário de login.
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
   * Envia o formulário de login.
   * @async
   * @param {Object} e Evento do formulário
   */
  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);
    setError('');

    console.log('Tentando fazer login...');

    try {
      const response = await authService.login(formData.email, formData.password);
      console.log('Login bem-sucedido:', response.user);
      
      // Notificar componente pai sobre o login bem-sucedido
      if (onLoginSuccess) {
        onLoginSuccess(response.user);
      }
    } catch (error) {
      console.error('Erro no login:', error);
      setError(error.response?.data?.error || 'Erro ao fazer login');
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="login-container">
      <div className="login-left">
        <div className="logo-container">
          <img src="/logo_site.png" alt="Playbox" className="logo" />
        </div>
      </div>
      
      <div className="login-right">
        <div className="login-form">
          <h1>Preencha o formulário</h1>
          
          {error && <div className="error-message">{error}</div>}
          
          <form onSubmit={handleSubmit}>
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

            <div className="forgot-password-links">
              <button 
                type="button" 
                className="forgot-password-button"
                onClick={onShowForgotPassword}
                disabled={loading}
              >
                Esqueceu a sua senha ?
              </button>
              <button 
                type="button" 
                className="no-account-button"
                onClick={onShowRegister}
                disabled={loading}
              >
                Não possui conta?
              </button>
            </div>

            <button 
              type="submit" 
              className="submit-button"
              disabled={loading}
            >
              {loading ? 'ENTRANDO...' : 'Entrar'}
            </button>
          </form>
        </div>
      </div>
    </div>
  );
};

export default Login;
