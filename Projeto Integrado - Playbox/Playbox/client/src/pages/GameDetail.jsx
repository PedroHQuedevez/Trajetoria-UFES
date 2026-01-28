import React, { useState, useEffect, useCallback } from 'react';
import { gameService, reviewService, catalogService } from '../services/api';
import ReviewForm from '../components/ReviewForm';
import GameRadarChart from '../components/GameRadarChart';
import '../styles/GameDetail.css';
import '../styles/GameRadarChart.css';

const GameDetail = ({ game, onBack, currentUser }) => {
  const [editingReview, setEditingReview] = useState(null);
  const [deleteConfirm, setDeleteConfirm] = useState(null);
  const [deletingReview, setDeletingReview] = useState(false);

  // Função para editar review
  /**
   * Inicia a edição de uma review.
   * @param {Object} review Review a ser editada
   */
  const handleEditReview = (review) => {
    setEditingReview(review);
    setShowReviewForm(true);
  };

  // Função para deletar review
  /**
   * Deleta uma review do jogo.
   * @async
   * @param {number} reviewId ID da review
   */
  const handleDeleteReview = async (reviewId) => {
    if (deletingReview) return; // Prevenir múltiplas execuções
    
    try {
      setDeletingReview(true);
      await reviewService.deleteReview(reviewId, { userId: currentUser.id });
      await loadReviews(gameDetails.id);
      await loadGameDetails(gameDetails.id);
      setDeleteConfirm(null);
    } catch (error) {
      alert('Erro ao deletar avaliação: ' + (error.response?.data?.error || error.message));
      setDeleteConfirm(null);
    } finally {
      setDeletingReview(false);
    }
  };

  /**
   * Exibe modal de confirmação para deletar review.
   * @param {Object} review Review a ser deletada
   */
  const confirmDeleteReview = (review) => {
    if (deletingReview) return; // Prevenir abertura do modal durante deleção
    setDeleteConfirm(review);
  };

  /**
   * Cancela a exclusão da review.
   */
  const cancelDeleteReview = () => {
    if (deletingReview) return; // Prevenir fechamento durante deleção
    setDeleteConfirm(null);
  };
  const [gameDetails, setGameDetails] = useState(game);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);
  const [showReviewForm, setShowReviewForm] = useState(false);
  const [reviews, setReviews] = useState([]);
  const [reviewsLoading, setReviewsLoading] = useState(false);
  const [isFavorite, setIsFavorite] = useState(false);
  const [favoriteLoading, setFavoriteLoading] = useState(false);

  /**
   * Verifica se o jogo está nos favoritos do usuário.
   * @async
   * @param {number} gameId ID do jogo
   * @returns {Promise<void>}
   */
  const checkIfFavorite = useCallback(async (gameId) => {
    if (!currentUser) return;
    
    try {
      const isFav = await catalogService.isGameInFavorites(currentUser.id, gameId);
      setIsFavorite(isFav);
    } catch (err) {
      console.error('Erro ao verificar favoritos:', err);
    }
  }, [currentUser]);

  useEffect(() => {
    if (game && game.id) {
      loadGameDetails(game.id);
      loadReviews(game.id);
      if (currentUser) {
        checkIfFavorite(game.id);
      }
    }
  }, [game, currentUser, checkIfFavorite]);

  /**
   * Carrega detalhes do jogo da API.
   * @async
   * @param {number} gameId ID do jogo
   * @returns {Promise<void>}
   */
  const loadGameDetails = async (gameId) => {
    try {
      setLoading(true);
      setError(null);
      const response = await gameService.getGame(gameId);
      setGameDetails(response.game);
    } catch (err) {
      setError('Erro ao carregar detalhes do jogo: ' + (err.response?.data?.error || err.message));
      console.error('Erro ao carregar detalhes:', err);
    } finally {
      setLoading(false);
    }
  };

  /**
   * Carrega reviews do jogo da API.
   * @async
   * @param {number} gameId ID do jogo
   * @returns {Promise<void>}
   */
  const loadReviews = async (gameId) => {
    try {
      setReviewsLoading(true);
      const response = await reviewService.getReviewsByGame(gameId);
      setReviews(response.reviews || []);
    } catch (err) {
      // Se não há reviews, não é um erro crítico
      console.log('Nenhuma review encontrada ou erro ao carregar:', err.message);
      setReviews([]);
    } finally {
      setReviewsLoading(false);
    }
  };

  /**
   * Adiciona ou remove o jogo dos favoritos do usuário.
   * @async
   * @returns {Promise<void>}
   */
  const handleToggleFavorite = async () => {
    if (!currentUser) return;
    
    try {
      setFavoriteLoading(true);
      
      if (isFavorite) {
        await catalogService.removeGameFromFavorites(currentUser.id, gameDetails.id);
        setIsFavorite(false);
      } else {
        await catalogService.addGameToFavorites(currentUser.id, gameDetails.id);
        setIsFavorite(true);
      }
    } catch (err) {
      console.error('Erro ao atualizar favoritos:', err);
      setError('Erro ao atualizar favoritos: ' + (err.response?.data?.error || err.message));
    } finally {
      setFavoriteLoading(false);
    }
  };

  /**
   * Cria uma nova review para o jogo.
   * @async
   * @param {Object} reviewData Dados da review
   * @returns {Promise<void>}
   */
  const handleCreateReview = async (reviewData) => {
    try {
      await reviewService.createReview(reviewData);
      setShowReviewForm(false);
      // Recarregar reviews e detalhes do jogo para atualizar a média
      await loadReviews(game.id);
      await loadGameDetails(game.id);
    } catch (error) {
      throw error; // Repassar erro para o componente de formulário
    }
  };

  /**
   * Formata uma data para o padrão pt-BR.
   * @param {string} dateString Data em formato string
   * @returns {string} Data formatada
   */
  const formatDate = (dateString) => {
    if (!dateString) return 'Data não disponível';
    const date = new Date(dateString);
    return date.toLocaleDateString('pt-BR');
  };

  if (loading) {
    return (
      <div className="game-detail-container">
        <div className="loading">Carregando detalhes do jogo...</div>
      </div>
    );
  }

  if (error) {
    return (
      <div className="game-detail-container">
        <div className="error-message">{error}</div>
        <button onClick={onBack} className="btn btn-secondary">
          Voltar
        </button>
      </div>
    );
  }

  if (!gameDetails) {
    return (
      <div className="game-detail-container">
        <div className="error-message">Jogo não encontrado</div>
        <button onClick={onBack} className="btn btn-secondary">
          Voltar
        </button>
      </div>
    );
  }

  return (
    <div className="game-detail-container">
      <div className="game-detail-header">
        <button onClick={onBack} className="btn btn-secondary back-button">
          ← Voltar
        </button>
      </div>

      <div className="game-detail-content">
        <div className="game-hero">
          <div className="game-image-large">
            {gameDetails.backgroundImage ? (
              <img 
                src={gameDetails.backgroundImage} 
                alt={gameDetails.name}
                onError={(e) => {
                  e.target.src = '/placeholder-game.png';
                }}
              />
            ) : (
              <div className="placeholder-image-large">
                <span>Sem Imagem</span>
              </div>
            )}
          </div>
          <div className="game-info-main">
            <h1 className="game-title-large">{gameDetails.name}</h1>
            <div className="game-meta-large">
              {gameDetails.metacriticScore && (
                <div className="score-badge">
                  <span className="score-label">Metacritic</span>
                  <span className="score-value">{gameDetails.metacriticScore}/100</span>
                </div>
              )}
              <div className="score-badge">
                <span className="score-label">Avaliação dos Usuários</span>
                <span className="score-value">
                  {gameDetails.averageReviewRating ? `${gameDetails.averageReviewRating}/5 ⭐` : '-/5 ⭐'}
                </span>
              </div>
              {gameDetails.releaseDate && (
                <div className="release-date">
                  <span className="label">Lançamento:</span>
                  <span className="value">{formatDate(gameDetails.releaseDate)}</span>
                </div>
              )}
              {gameDetails.playtime && (
                <div className="playtime">
                  <span className="label">Tempo de jogo:</span>
                  <span className="value">{gameDetails.playtime}h</span>
                </div>
              )}
              {currentUser && (
              <div className="game-actions-section">
                <button 
                  onClick={handleToggleFavorite}
                  className={`btn ${isFavorite ? 'btn-favorite-active' : 'btn-favorite'}`}
                  disabled={favoriteLoading}
                >
                  {favoriteLoading ? (
                    'Carregando...'
                  ) : isFavorite ? (
                    <>🤍 Desfavoritar</>
                  ) : (
                    <>❤️ Favoritar</>
                  )}
                </button>
                
                <button 
                  onClick={() => setShowReviewForm(true)}
                  className="btn btn-primary review-button-standalone"
                >
                 Avaliar Jogo
                </button>
              </div>
            )}
            </div>
          </div>
        </div>

        <div className="game-details-grid">
          <div className="game-description">
            <h2>Descrição</h2>
            <p>{gameDetails.description || 'Descrição não disponível.'}</p>
          </div>

          <div className="game-sidebar">
            {gameDetails.genres && gameDetails.genres.length > 0 && (
              <div className="detail-section">
                <h3>Gêneros</h3>
                <div className="genre-tags">
                  {gameDetails.genres.map((genre, index) => (
                    <span key={index} className="genre-tag">
                      {genre}
                    </span>
                  ))}
                </div>
              </div>
            )}

            {gameDetails.platforms && gameDetails.platforms.length > 0 && (
              <div className="detail-section">
                <h3>Plataformas</h3>
                <div className="platform-list">
                  {gameDetails.platforms.map((platform, index) => (
                    <span key={index} className="platform-item">
                      {platform}
                    </span>
                  ))}
                </div>
              </div>
            )}

            {gameDetails.publishers && gameDetails.publishers.length > 0 && (
              <div className="detail-section">
                <h3>Editoras</h3>
                <div className="publisher-list">
                  {gameDetails.publishers.map((publisher, index) => (
                    <span key={index} className="publisher-item">
                      {publisher}
                    </span>
                  ))}
                </div>
              </div>
            )}
          </div>
        </div>

        {/* Screenshots */}
        {gameDetails.screenshots && gameDetails.screenshots.length > 0 && (
          <div className="screenshots-section">
            <h2>Screenshots</h2>
            <div className="screenshots-grid">
              {gameDetails.screenshots.slice(0, 6).map((screenshot, index) => (
                <div key={index} className="screenshot-item">
                  <img 
                    src={screenshot} 
                    alt={`Screenshot ${index + 1}`}
                    onError={(e) => {
                      e.target.style.display = 'none';
                    }}
                  />
                </div>
              ))}
            </div>
          </div>
        )}

        {/* Avaliação Geral por Aspectos - aparece sempre */}
        <div className="radar-chart-section">
          <GameRadarChart reviews={reviews} />
        </div>

        {/* Seção de Reviews */}
        <div className="reviews-section">
          <h2>Avaliações dos Usuários ({reviews.length})</h2>
          
          {reviewsLoading ? (
            <div className="loading">Carregando avaliações...</div>
          ) : reviews.length > 0 ? (
            <div className="reviews-list">
              {reviews.slice(0, reviews.length).map((review) => (
                <div key={review.id} className="review-item">
                  <div className="review-header">
                    <span className="reviewer-name">{review.user?.name || 'Usuário'}</span>
                    <div className="review-header-right">
                      <span className="review-rating">⭐ {review.ratings.average}/5</span>
                      <span className="review-date">Publicado em: {formatDate(review.createdAt)}</span>
                    </div>
                  </div>
                  {review.comment && (
                    <p className="review-comment">{review.comment}</p>
                  )}
                  <div className="review-aspects">
                    <div className="aspect-rating">
                      <span className="aspect-label">Gameplay:</span>
                      <span className="aspect-value">{review.ratings.gameplay || '-'}/5</span>
                    </div>
                    <div className="aspect-rating">
                      <span className="aspect-label">Visual:</span>
                      <span className="aspect-value">{review.ratings.visual || '-'}/5</span>
                    </div>
                    <div className="aspect-rating">
                      <span className="aspect-label">Áudio:</span>
                      <span className="aspect-value">{review.ratings.audio || '-'}/5</span>
                    </div>
                    <div className="aspect-rating">
                      <span className="aspect-label">Dificuldade:</span>
                      <span className="aspect-value">{review.ratings.difficulty || '-'}/5</span>
                    </div>
                    <div className="aspect-rating">
                      <span className="aspect-label">Imersão:</span>
                      <span className="aspect-value">{review.ratings.immersion || '-'}/5</span>
                    </div>
                    <div className="aspect-rating">
                      <span className="aspect-label">Hisrória:</span>
                      <span className="aspect-value">{review.ratings.history || '-'}/5</span>
                    </div>
                  </div>
                  
                  {/* Botões de editar/deletar visíveis apenas para o autor */}
                  {currentUser && review.user?.id === currentUser.id && (
                    <div className="review-actions">
                      <button 
                        className="btn btn-warning btn-sm" 
                        onClick={() => handleEditReview(review)}
                        disabled={deletingReview}
                      >
                        Editar
                      </button>
                      <button 
                        className="btn btn-danger btn-sm" 
                        onClick={() => confirmDeleteReview(review)}
                        disabled={deletingReview}
                      >
                        {deletingReview ? 'Deletando...' : 'Deletar'}
                      </button>
                    </div>
                  )}
                </div>
              ))}
            </div>
          ) : (
            <p className="no-reviews">Ainda não há avaliações para este jogo.</p>
          )}
        </div>
      </div>


      {/* Modal de Review */}
      {showReviewForm && (
        <ReviewForm
          gameId={gameDetails.id}
          currentUser={currentUser}
          review={editingReview}
          onSubmit={async (reviewData) => {
            if (editingReview) {
              // Editar review existente
              try {
                await reviewService.updateReview(editingReview.id, reviewData);
                setEditingReview(null);
                setShowReviewForm(false);
                await loadReviews(gameDetails.id);
                await loadGameDetails(gameDetails.id);
              } catch (error) {
                alert('Erro ao editar avaliação: ' + (error.response?.data?.error || error.message));
              }
            } else {
              // Criar nova review
              await handleCreateReview(reviewData);
            }
          }}
          onCancel={() => {
            setEditingReview(null);
            setShowReviewForm(false);
          }}
        />
      )}

      {/* Modal de confirmação de exclusão */}
      {deleteConfirm && (
        <div className="delete-modal-overlay">
          <div className="delete-modal">
            <div className="delete-modal-header">
              <h3>Confirmar Exclusão</h3>
            </div>
            <div className="delete-modal-content">
              <p>Tem certeza que deseja deletar sua avaliação:</p>
              <div className="review-to-delete">
                <div className="review-info">
                  <strong>Avaliação: ⭐ {deleteConfirm.ratings.average}/5</strong>
                  {deleteConfirm.comment && (
                    <div className="review-comment-preview">
                      <em>"{deleteConfirm.comment.length > 100 
                        ? deleteConfirm.comment.substring(0, 100) + '...' 
                        : deleteConfirm.comment}"</em>
                    </div>
                  )}
                </div>
              </div>
              <p className="warning-text">Esta ação não pode ser desfeita!</p>
            </div>
            <div className="delete-modal-actions">
              <button
                onClick={cancelDeleteReview}
                className="btn btn-secondary"
                disabled={deletingReview}
              >
                Cancelar
              </button>
              <button
                onClick={() => handleDeleteReview(deleteConfirm.id)}
                className="btn btn-danger"
                disabled={deletingReview}
              >
                {deletingReview ? 'Deletando...' : 'Confirmar Exclusão'}
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
};

export default GameDetail;
