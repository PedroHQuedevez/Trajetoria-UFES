import React, { useState } from 'react';
import { authService } from '../services/api';
import '../styles/Header.css';

const Header = ({ user, onLogout, onNavigate, currentPage, onSearchChange }) => {
/**
 * Componente de cabeçalho do site.
 * Exibe o logo e navegação principal.
 * @module Header
 * @returns {JSX.Element} Elemento React do cabeçalho
 */
  const [searchTerm, setSearchTerm] = useState('');

  /**
   * Realiza o logout do usuário e chama o callback de logout.
   * @async
   * @returns {Promise<void>}
   */
  const handleLogout = async () => {
    try {
      await authService.logout();
      if (onLogout) {
        onLogout();
      }
    } catch (error) {
      console.error('Erro no logout:', error);
    }
  };

  /**
   * Atualiza o termo de busca e chama o callback de busca.
   * @param {Object} e Evento do input
   */
  const handleSearchInput = (e) => {
    const value = e.target.value;
    setSearchTerm(value);
    if (onSearchChange) {
      onSearchChange(value);
    }
  };

  return (
    <header className="header">
      <div className="header-content">
        <div 
          onClick={() => onNavigate && onNavigate('home')}
          className="header-logo"
        >
          <img src="/header_logo.png" alt="Playbox" className="logo-image" />
        </div>
        
        {currentPage === 'home' && (
          <div className="search-container">
            <input
              type="text"
              placeholder="Buscar jogos..."
              value={searchTerm}
              onChange={handleSearchInput}
              className="search-input"
            />
          </div>
        )}
        
        <nav className="header-nav">
          <button 
            onClick={() => onNavigate && onNavigate('home')}
            className={`nav-button ${currentPage === 'home' ? 'active' : ''}`}
          >
            Home
          </button>
          {user?.isAdmin && (
            <button 
              onClick={() => onNavigate && onNavigate('admin')}
              className={`nav-button ${currentPage === 'admin' ? 'active' : ''}`}
            >
              Admin
            </button>
          )}
          <button 
            onClick={() => onNavigate && onNavigate('profile')}
            className={`nav-button ${currentPage === 'profile' ? 'active' : ''}`}
          >
            Perfil
          </button>
        </nav>
        
        {user && (
          <div className="user-info">
            <span className="welcome-text">
              <strong>{user.name}</strong>
              {user.isAdmin && <span className="admin-badge">Admin</span>}
            </span>
            <button onClick={handleLogout} className="logout-button">
              Sair
            </button>
          </div>
        )}
      </div>
    </header>
  );
};

export default Header;
