import React, { useState } from 'react';
import { authService } from '../services/api';
import '../styles/ForgotPassword.css';

const ForgotPassword = ({ onBackToLogin }) => {
  const [step, setStep] = useState(1); // 1: solicitar email, 2: inserir token e nova senha
  const [email, setEmail] = useState('');
  const [token, setToken] = useState('');
  const [newPassword, setNewPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const [error, setError] = useState('');
  const [success, setSuccess] = useState('');
  const [loading, setLoading] = useState(false);
  const [resetToken, setResetToken] = useState('');

  /**
   * Envia o email para recuperação de senha.
   * @async
   * @param {Object} e Evento do formulário
   */
  const handleEmailSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);
    setError('');

    try {
      const response = await authService.forgotPassword(email);
      
      // Em produção, este token seria enviado por email
      setResetToken(response.resetToken);
      setStep(2);
      
    } catch (error) {
      console.error('Erro ao solicitar recuperação:', error);
      setError(error.response?.data?.error || 'Erro ao solicitar recuperação de senha');
    } finally {
      setLoading(false);
    }
  };

  /**
   * Envia o formulário para redefinir a senha.
   * @async
   * @param {Object} e Evento do formulário
   */
  const handlePasswordReset = async (e) => {
    e.preventDefault();
    
    if (newPassword.length < 6) {
      setError('A nova senha deve ter pelo menos 6 caracteres.');
      return;
    }

    if (newPassword !== confirmPassword) {
      setError('As senhas não coincidem.');
      return;
    }

    setLoading(true);
    setError('');
    setSuccess('');

    try {
      const tokenToUse = token || resetToken; // Usar token inserido ou o gerado
      await authService.resetPassword(tokenToUse, newPassword);
      
      // Sucesso - mostrar mensagem de sucesso
      setSuccess('Senha redefinida com sucesso! Você já pode fazer login com a nova senha.');
      
      // Voltar para login após 3 segundos
      setTimeout(() => {
        onBackToLogin();
      }, 3000);
      
    } catch (error) {
      console.error('Erro ao redefinir senha:', error);
      setError(error.response?.data?.error || 'Erro ao redefinir senha');
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="forgot-password-container">
      <div className="forgot-password-left">
        <div className="logo-container">
          <img src="/logo_site.png" alt="Playbox" className="logo" />
        </div>
      </div>
      
      <div className="forgot-password-right">
        <div className="forgot-password-form">
          {step === 1 ? (
            <>
              <h1>Informe seu e-mail para receber as instruções de recuperação da conta</h1>
              
              <form onSubmit={handleEmailSubmit}>
                {error && <div className="error-message">{error}</div>}
                
                <div className="form-group">
                  <input
                    type="email"
                    id="email"
                    value={email}
                    onChange={(e) => setEmail(e.target.value)}
                    required
                    disabled={loading}
                    placeholder="E-mail"
                  />
                </div>

                <div className="form-buttons">
                  <button 
                    type="submit" 
                    className="submit-button"
                    disabled={loading}
                  >
                    {loading ? 'ENVIANDO...' : 'Enviar'}
                  </button>
                  
                  <button 
                    type="button" 
                    className="back-button"
                    onClick={onBackToLogin}
                    disabled={loading}
                  >
                    Voltar ao Login
                  </button>
                </div>
              </form>
            </>
          ) : (
            <>
              <h1>Redefinir Senha</h1>
              <p className="form-subtitle">Use o token abaixo ou insira o token que você recebeu por email.</p>
              
              {resetToken && (
                <div className="token-display">
                  <strong>Token de demonstração:</strong>
                  <code>{resetToken}</code>
                  <small>No mundo real, este token seria enviado por email.</small>
                </div>
              )}
              
              <form onSubmit={handlePasswordReset}>
                {error && <div className="error-message">{error}</div>}
                {success && <div className="success-message">{success}</div>}
                
                <div className="form-group">
                  <input
                    type="text"
                    id="token"
                    value={token}
                    onChange={(e) => setToken(e.target.value)}
                    disabled={loading}
                    placeholder={resetToken ? "Token preenchido automaticamente" : "Cole o token aqui"}
                  />
                  <small>Se você não inserir um token, será utilizado o token gerado automaticamente acima.</small>
                </div>

                <div className="form-group">
                  <input
                    type="password"
                    id="newPassword"
                    value={newPassword}
                    onChange={(e) => setNewPassword(e.target.value)}
                    required
                    disabled={loading}
                    placeholder="Nova Senha"
                  />
                </div>

                <div className="form-group">
                  <input
                    type="password"
                    id="confirmPassword"
                    value={confirmPassword}
                    onChange={(e) => setConfirmPassword(e.target.value)}
                    required
                    disabled={loading}
                    placeholder="Confirmar Nova Senha"
                  />
                </div>

                <div className="form-buttons">
                  <button 
                    type="submit" 
                    className="submit-button"
                    disabled={loading}
                  >
                    {loading ? 'REDEFININDO...' : 'REDEFINIR SENHA'}
                  </button>
                  
                  <button 
                    type="button" 
                    className="back-button"
                    onClick={() => setStep(1)}
                    disabled={loading}
                  >
                    Voltar
                  </button>
                </div>
              </form>
            </>
          )}
        </div>
      </div>
    </div>
  );
};

export default ForgotPassword;
