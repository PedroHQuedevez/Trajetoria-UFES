import React, { useState, useEffect, useCallback } from 'react';
import { catalogService } from '../services/api';
import '../styles/UserProfile.css';

const UserProfile = ({ currentUser, onEditProfile, onGameSelect }) => {
  /**
   * Perfil do usuário.
   * Exibe informações detalhadas do usuário.
   * @module UserProfile
   * @param {Object} props Propriedades do componente
   * @param {Object} props.user Dados do usuário
   * @returns {JSX.Element} Elemento React do perfil de usuário
   */
  const [activeTab, setActiveTab] = useState('info');
  const [favoriteGames, setFavoriteGames] = useState([]);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);
  const [showDeleteConfirm, setShowDeleteConfirm] = useState(false);

  /**
   * Carrega os jogos favoritos do usuário.
   * @async
   * @returns {Promise<void>}
   */
  const loadFavoriteGames = useCallback(async () => {
    if (!currentUser) return;
    
    try {
      setLoading(true);
      setError(null);
      const response = await catalogService.getFavoriteGames(currentUser.id);
      setFavoriteGames(response.games || []);
    } catch (err) {
      setError('Erro ao carregar jogos favoritos: ' + (err.response?.data?.error || err.message));
      console.error('Erro ao carregar favoritos:', err);
    } finally {
      setLoading(false);
    }
  }, [currentUser]);

  useEffect(() => {
    if (currentUser) {
      loadFavoriteGames();
    }
  }, [currentUser, loadFavoriteGames]);

  useEffect(() => {
    if (activeTab === 'favorites' && currentUser && favoriteGames.length === 0 && !loading) {
      loadFavoriteGames();
    }
  }, [activeTab, currentUser, favoriteGames.length, loading, loadFavoriteGames]);

  /**
   * Chama o callback ao selecionar um jogo favorito.
   * @param {Object} game Objeto do jogo selecionado
   */
  const handleGameClick = (game) => {
    if (onGameSelect) {
      onGameSelect(game);
    }
  };

  /**
   * Realiza a exclusão da conta do usuário.
   * @async
   * @returns {Promise<void>}
   */
  const handleDeleteAccount = async () => {
    try {
      const { userService, authService } = await import('../services/api');
      await userService.deleteOwnAccount();
      // Só remove o token após exclusão bem-sucedida
      await authService.logout();
      window.location.href = '/login';
    } catch (err) {
      alert('Erro ao excluir conta: ' + (err.response?.data?.error || err.message));
      setShowDeleteConfirm(false);
    }
  };

  /**
   * Cancela a exclusão da conta do usuário.
   */
  const cancelDeleteAccount = () => {
    setShowDeleteConfirm(false);
  };

  if (!currentUser) {
    return (
      <div className="user-profile-container">
        <div className="loading">Carregando dados do usuário...</div>
      </div>
    );
  }

  return (
    <div className="user-profile-container">
      <div className="profile-header">
        <h2>Meu Perfil</h2>
        <div className="user-avatar">
          <div className="avatar-circle">
            {currentUser.name.charAt(0).toUpperCase()}
          </div>
          <div className="user-info">
            <h3>{currentUser.name}</h3>
            <span className="user-role">
              {currentUser.isAdmin ? 'Administrador' : 'Usuário'}
            </span>
          </div>
        </div>
      </div>

      <div className="profile-tabs">
        <button 
          className={`tab-button ${activeTab === 'info' ? 'active' : ''}`}
          onClick={() => setActiveTab('info')}
        >
          <span className="tab-icon">👤</span>
          Informações
        </button>
        <button 
          className={`tab-button ${activeTab === 'favorites' ? 'active' : ''}`}
          onClick={() => setActiveTab('favorites')}
        >
          <span className="tab-icon">❤️</span>
          Favoritos ({favoriteGames.length})
        </button>
      </div>

      <div className="profile-content">
        {activeTab === 'info' && (
          <div className="profile-info-tab">
            <div className="info-section">
              <h3>Informações Pessoais</h3>
              <div className="info-grid">
                <div className="info-item">
                  <label>Nome:</label>
                  <span>{currentUser.name}</span>
                </div>
                <div className="info-item">
                  <label>Email:</label>
                  <span>{currentUser.email}</span>
                </div>
                <div className="info-item">
                  <label>Tipo de Conta:</label>
                  <span className={`account-type ${currentUser.isAdmin ? 'admin' : 'user'}`}>
                    {currentUser.isAdmin ? 'Administrador' : 'Usuário'}
                  </span>
                </div>
                <div className="info-item">
                  <label>Membro desde:</label>
                  <span>
                    {new Date(currentUser.createdAt).toLocaleDateString('pt-BR', {
                      year: 'numeric',
                      month: 'long',
                      day: 'numeric'
                    })}
                  </span>
                </div>
              </div>
            </div>
            
            <div className="profile-actions">
              <button 
                onClick={onEditProfile}
                className="btn btn-primary"
              >
                Editar Perfil
              </button>
              <button
                onClick={() => setShowDeleteConfirm(true)}
                className="btn btn-danger"
                style={{ marginLeft: '1rem' }}
              >
                Excluir Conta
              </button>
            </div>
          </div>
        )}

        {activeTab === 'favorites' && (
          <div className="favorites-tab">
            <div className="favorites-header">
              <h3>Meus Jogos Favoritos</h3>
              <p>Jogos que você marcou como favoritos</p>
            </div>

            {error && (
              <div className="error-message">
                {error}
                <button onClick={loadFavoriteGames} className="btn btn-small">
                  Tentar Novamente
                </button>
              </div>
            )}

            {loading ? (
              <div className="loading">Carregando jogos favoritos...</div>
            ) : favoriteGames.length === 0 ? (
              <div className="no-favorites">
                <div className="no-favorites-icon">💔</div>
                <h4>Nenhum jogo favorito ainda</h4>
                <p>Explore nossa biblioteca e marque jogos como favoritos!</p>
              </div>
            ) : (
              <div className="favorites-grid">
                {favoriteGames.map((game) => (
                  <div 
                    key={game.id} 
                    className="favorite-game-card"
                    onClick={() => handleGameClick(game)}
                  >
                    <div className="game-image">
                      {game.backgroundImage ? (
                        <img 
                          src={game.backgroundImage} 
                          alt={game.name}
                          onError={(e) => {
                            e.target.src = '/placeholder-game.png';
                          }}
                        />
                      ) : (
                        <div className="placeholder-image">
                          <span>Sem Imagem</span>
                        </div>
                      )}
                    </div>
                    
                    <div className="game-info">
                      <h4 className="game-title">{game.name}</h4>
                      
                      <div className="game-meta">      
                        <div className="game-ratings">
                          {game.metacriticScore && (
                            <span className="game-score">
                              Crítica: {game.metacriticScore}/100
                            </span>
                          )}
                          <span className="game-user-rating">
                            ★ {game.averageReviewRating ? `${game.averageReviewRating}/5` : '-/5'}
                          </span>
                        </div>
                      </div>
                    </div>

                    <div className="favorite-badge">
                      ❤️
                    </div>
                  </div>
                ))}
              </div>
            )}
          </div>
        )}

        {/* Modal de confirmação de exclusão */}
        {showDeleteConfirm && (
          <div className="delete-modal-overlay">
            <div className="delete-modal">
              <div className="delete-modal-header">
                <h3>Confirmar Exclusão da Conta</h3>
              </div>
              <div className="delete-modal-content">
                <p>Tem certeza que deseja excluir sua conta?</p>
                <div className="user-to-delete">
                  <strong>{currentUser.name}</strong>
                  <br />
                  <span>{currentUser.email}</span>
                </div>
                <p className="warning-text">
                  ⚠️ Esta ação não pode ser desfeita! Todos os seus dados, incluindo reviews e listas de favoritos, serão permanentemente removidos.
                </p>
              </div>
              <div className="delete-modal-actions">
                <button
                  onClick={cancelDeleteAccount}
                  className="btn btn-secondary"
                >
                  Cancelar
                </button>
                <button
                  onClick={handleDeleteAccount}
                  className="btn btn-danger"
                >
                  Confirmar Exclusão
                </button>
              </div>
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default UserProfile;
