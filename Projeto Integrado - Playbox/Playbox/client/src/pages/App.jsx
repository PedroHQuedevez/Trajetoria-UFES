import React, { useState, useEffect } from 'react';
import '../styles/App.css';
import { UserForm, Header } from '../components';
import UserProfile from '../components/UserProfile';
import { Login, Register, ForgotPassword, Home, GameDetail, AdminPanel } from './';
import { userService, authService } from '../services/api';

function App() {
/**
 * Componente principal da aplicação.
 * Gerencia rotas e contexto global.
 * @module App
 * @returns {JSX.Element} Elemento React da aplicação
 */
  const [editingUser, setEditingUser] = useState(null);
  const [showForm, setShowForm] = useState(false);
  const [error, setError] = useState(null);
  const [isLoggedIn, setIsLoggedIn] = useState(false);
  const [currentUser, setCurrentUser] = useState(null);
  const [checkingAuth, setCheckingAuth] = useState(true);
  const [showRegister, setShowRegister] = useState(false);
  const [showForgotPassword, setShowForgotPassword] = useState(false);
  
  // Estados para navegação
  const [currentPage, setCurrentPage] = useState('home'); // 'home', 'admin', 'profile', 'game-detail'
  const [selectedGame, setSelectedGame] = useState(null);
  const [searchTerm, setSearchTerm] = useState('');

  // Verificar autenticação ao carregar o app
  useEffect(() => {
    checkAuthentication();
  }, []);

  /**
   * Verifica autenticação do usuário ao carregar o app.
   * @async
   * @returns {Promise<void>}
   */
  const checkAuthentication = async () => {
    try {
      setCheckingAuth(true);
      
      if (!authService.isLoggedIn()) {
        setIsLoggedIn(false);
        setCurrentUser(null);
        return;
      }

      // Verificar se o token é válido
      const response = await authService.verifyToken();
      setIsLoggedIn(true);
      setCurrentUser(response.user);
    } catch (error) {
      console.error('Erro na verificação de autenticação:', error);
      setIsLoggedIn(false);
      setCurrentUser(null);
      // Token inválido será removido automaticamente pelo interceptor
    } finally {
      setCheckingAuth(false);
    }
  };

  /**
   * Manipula login bem-sucedido.
   * @param {Object} user Usuário logado
   */
  const handleLoginSuccess = (user) => {
    console.log('Login success, setting user:', user);
    setIsLoggedIn(true);
    setCurrentUser(user);
    setShowRegister(false);
    setShowForgotPassword(false);
    setCurrentPage('home'); // Redirecionar para Home após login
    setError(null);
  };

  /**
   * Realiza logout do usuário.
   */
  const handleLogout = () => {
    setIsLoggedIn(false);
    setCurrentUser(null);
    setEditingUser(null);
    setShowForm(false);
    setShowRegister(false);
    setShowForgotPassword(false);
    setError(null);
  };

  /**
   * Exibe tela de registro.
   */
  const handleShowRegister = () => {
    setShowRegister(true);
    setShowForgotPassword(false);
    setError(null);
  };

  /**
   * Exibe tela de recuperação de senha.
   */
  const handleShowForgotPassword = () => {
    setShowForgotPassword(true);
    setShowRegister(false);
    setError(null);
  };

  /**
   * Retorna para tela de login.
   */
  const handleBackToLogin = () => {
    setShowRegister(false);
    setShowForgotPassword(false);
    setError(null);
  };

  /**
   * Manipula registro bem-sucedido.
   * @param {Object} user Usuário registrado
   */
  const handleRegisterSuccess = (user) => {
    console.log('Register success, setting user:', user);
    setIsLoggedIn(true);
    setCurrentUser(user);
    setShowRegister(false);
    setShowForgotPassword(false);
    setCurrentPage('home'); // Redirecionar para Home após registro
    setError(null);
  };

  // Funções de navegação
  /**
   * Seleciona um jogo para exibir detalhes.
   * @param {Object} game Jogo selecionado
   */
  const handleGameSelect = (game) => {
    setSelectedGame(game);
    setCurrentPage('game-detail');
  };

  /**
   * Retorna para tela inicial.
   */
  const handleBackToHome = () => {
    setSelectedGame(null);
    setCurrentPage('home');
  };

  /**
   * Exibe painel de administração.
   */
  const handleShowAdmin = () => {
    setCurrentPage('admin');
  };

  /**
   * Exibe perfil do usuário.
   */
  const handleShowProfile = () => {
    setCurrentPage('profile');
  };

  /**
   * Exibe tela inicial.
   */
  const handleShowHome = () => {
    setCurrentPage('home');
  };

  /**
   * Cria novo usuário.
   * @async
   * @param {Object} userData Dados do usuário
   * @returns {Promise<void>}
   */
  const handleCreateUser = async (userData) => {
    try {
      await userService.createUser(userData);
      setShowForm(false);
      setError(null);
    } catch (err) {
      setError('Erro ao criar usuário: ' + (err.response?.data?.error || err.message));
      console.error('Erro ao criar usuário:', err);
    }
  };

  /**
   * Atualiza dados do usuário.
   * @async
   * @param {Object} userData Dados do usuário
   * @returns {Promise<void>}
   */
  const handleUpdateUser = async (userData) => {
    try {
      await userService.updateUser(editingUser.id, userData);
      setEditingUser(null);
      setShowForm(false);
      setError(null);
    } catch (err) {
      setError('Erro ao atualizar usuário: ' + (err.response?.data?.error || err.message));
      console.error('Erro ao atualizar usuário:', err);
    }
  };

  /**
   * Envia dados do formulário de usuário.
   * @param {Object} userData Dados do usuário
   */
  const handleFormSubmit = (userData) => {
    if (editingUser) {
      handleUpdateUser(userData);
    } else {
      handleCreateUser(userData);
    }
  };

  /**
   * Cancela edição/criação de usuário.
   */
  const handleCancelForm = () => {
    setEditingUser(null);
    setShowForm(false);
  };

  /**
   * Atualiza termo de busca global.
   * @param {string} term Termo de busca
   */
  const handleSearchChange = (term) => {
    setSearchTerm(term);
  };

  return (
    <div className="App">
      {checkingAuth ? (
        <div className="loading-screen">
          <div className="loading">Verificando autenticação...</div>
        </div>
      ) : !isLoggedIn ? (
        showForgotPassword ? (
          <ForgotPassword 
            onBackToLogin={handleBackToLogin}
          />
        ) : showRegister ? (
          <Register 
            onRegisterSuccess={handleRegisterSuccess}
            onBackToLogin={handleBackToLogin}
          />
        ) : (
          <Login 
            onLoginSuccess={handleLoginSuccess}
            onShowRegister={handleShowRegister}
            onShowForgotPassword={handleShowForgotPassword}
          />
        )
      ) : (
        <>
          <Header 
            user={currentUser} 
            onLogout={handleLogout}
            onNavigate={(page) => {
              if (page === 'home') handleShowHome();
              else if (page === 'admin') handleShowAdmin();
              else if (page === 'profile') handleShowProfile();
            }}
            currentPage={currentPage}
            onSearchChange={handleSearchChange}
          />
          
          <main className="App-main">
            {currentPage === 'home' && (
              <Home onGameSelect={handleGameSelect} searchTerm={searchTerm} />
            )}

            {currentPage === 'game-detail' && selectedGame && (
              <GameDetail 
                game={selectedGame} 
                onBack={handleBackToHome}
                currentUser={currentUser}
              />
            )}

            {currentPage === 'admin' && currentUser?.isAdmin && (
              <AdminPanel 
                currentUser={currentUser}
                onBack={handleBackToHome}
              />
            )}

            {currentPage === 'profile' && (
              <>
                {error && (
                  <div className="error-message">
                    {error}
                  </div>
                )}
                
                {showForm ? (
                  <UserForm
                    user={editingUser}
                    onSubmit={handleFormSubmit}
                    onCancel={handleCancelForm}
                  />
                ) : (
                  <UserProfile
                    currentUser={currentUser}
                    onEditProfile={() => setEditingUser(currentUser) || setShowForm(true)}
                    onGameSelect={handleGameSelect}
                  />
                )}
              </>
            )}
          </main>
        </>
      )}
    </div>
  );
}

export default App;
