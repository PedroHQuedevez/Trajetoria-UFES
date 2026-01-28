import React, { useState, useEffect } from 'react';
import { gameService } from '../services/api';
import '../styles/Home.css';

const Home = ({ onGameSelect, searchTerm = '' }) => {
  const [showGenreDropdown, setShowGenreDropdown] = useState(false);
  /**
   * Alterna seleção de um gênero no filtro.
   * @param {string} genre Nome do gênero
   */
  const handleGenreCheckbox = (genre) => {
    if (genreFilter.includes(genre)) {
      setGenreFilter(genreFilter.filter(g => g !== genre));
    } else {
      setGenreFilter([...genreFilter, genre]);
    }
  };
  /**
   * Fecha o dropdown de gêneros ao perder o foco.
   * @param {Object} e Evento do elemento
   */
  const handleDropdownBlur = (e) => {
    if (!e.currentTarget.contains(e.relatedTarget)) {
      setShowGenreDropdown(false);
    }
  };
  const [games, setGames] = useState([]);
  const [filteredGames, setFilteredGames] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [genreFilter, setGenreFilter] = useState([]);
  // Extrair gêneros únicos dos jogos
  const allGenres = Array.from(new Set(games.flatMap(game => game.genres || []))).sort();
  const [sortOption, setSortOption] = useState('nameAsc');
  // Função para ordenar os jogos
  /**
   * Ordena a lista de jogos conforme a opção selecionada.
   * @param {Array} games Lista de jogos
   * @returns {Array} Lista ordenada
   */
  const sortGames = (games) => {
    const sorted = [...games];
    switch (sortOption) {
      case 'nameAsc':
        sorted.sort((a, b) => a.name.localeCompare(b.name));
        break;
      case 'nameDesc':
        sorted.sort((a, b) => b.name.localeCompare(a.name));
        break;
      case 'metacriticDesc':
        sorted.sort((a, b) => (b.metacriticScore || 0) - (a.metacriticScore || 0));
        break;
      case 'metacriticAsc':
        sorted.sort((a, b) => (a.metacriticScore || 0) - (b.metacriticScore || 0));
        break;
      case 'userRatingDesc':
        sorted.sort((a, b) => (b.averageReviewRating || 0) - (a.averageReviewRating || 0));
        break;
      case 'userRatingAsc':
        sorted.sort((a, b) => (a.averageReviewRating || 0) - (b.averageReviewRating || 0));
        break;
      default:
        break;
    }
    return sorted;
  };


  useEffect(() => {
    loadGames();
  }, []);

  useEffect(() => {
    if (searchTerm) {
      const filtered = games.filter(game => 
        game.name.toLowerCase().includes(searchTerm.toLowerCase()) ||
        (game.genres && game.genres.some(genre => 
          genre.toLowerCase().includes(searchTerm.toLowerCase())
        ))
      );
      setFilteredGames(filtered);
    } else {
      setFilteredGames(games);
    }
  }, [searchTerm, games]);

  /**
   * Carrega a lista de jogos da API.
   * @async
   * @returns {Promise<void>}
   */
  const loadGames = async () => {
    try {
      setLoading(true);
      setError(null);
      const response = await gameService.getGames();
      setGames(response.games || []);
    } catch (err) {
      setError('Erro ao carregar jogos: ' + (err.response?.data?.error || err.message));
      console.error('Erro ao carregar jogos:', err);
    } finally {
      setLoading(false);
    }
  };

  /**
   * Chama o callback ao selecionar um jogo.
   * @param {Object} game Objeto do jogo selecionado
   */
  const handleGameClick = (game) => {
    if (onGameSelect) {
      onGameSelect(game);
    }
  };

  if (loading) {
    return (
      <div className="home-container">
        <div className="loading">Carregando jogos...</div>
      </div>
    );
  }

  if (error) {
    return (
      <div className="home-container">
        <div className="error-message">{error}</div>
        <button onClick={loadGames} className="btn btn-primary">
          Tentar Novamente
        </button>
      </div>
    );
  }

  let genreFilteredGames = searchTerm ? filteredGames : games;
  if (genreFilter.length > 0) {
    genreFilteredGames = genreFilteredGames.filter(game =>
      game.genres && genreFilter.every(selected => game.genres.includes(selected))
    );
  }
  const displayGames = sortGames(genreFilteredGames);
      <div className="sort-bar">
        <label htmlFor="sort-select">Ordenar por:</label>
        <select
          id="sort-select"
          value={sortOption}
          onChange={e => setSortOption(e.target.value)}
          className="sort-select"
        >
          <option value="name">Nome (A-Z)</option>
          <option value="metacritic">Nota Metacritic</option>
          <option value="userRating">Nota Média dos Usuários</option>
        </select>
      </div>

  return (
    <div className="home-container">
      <div className="home-header">
        <h1>Biblioteca de Jogos</h1>
        <p>Descubra e explore nossa coleção de jogos</p>
        {searchTerm && (
          <p className="search-results">
            Resultados para: "{searchTerm}" ({displayGames.length} jogos encontrados)
          </p>
        )}
        <div className="filter-controls">
          <div className="filter-left">
            <label style={{ marginRight: 8, color: '#29B6F6', fontWeight: 500 }}>Filtrar por gênero:</label>
            <div className="genre-dropdown" tabIndex={0} onBlur={handleDropdownBlur} style={{ position: 'relative', minWidth: 160 }}>
              <button type="button" className="filter-button" onClick={() => setShowGenreDropdown(s => !s)}>
                {genreFilter.length > 0 ? `${genreFilter.length} selecionado(s)` : 'Selecionar gêneros'}
              </button>
              {showGenreDropdown && (
                <div className="genre-dropdown-menu" style={{ position: 'absolute', top: '110%', left: 0, background: '#222', borderRadius: 12, boxShadow: '0 2px 8px rgba(0,0,0,0.2)', zIndex: 10, padding: 12, minWidth: 180 }}>
                  {allGenres.map(genre => (
                    <label key={genre} style={{ display: 'flex', alignItems: 'center', marginBottom: 6, cursor: 'pointer' }}>
                      <input
                        type="checkbox"
                        checked={genreFilter.includes(genre)}
                        onChange={() => handleGenreCheckbox(genre)}
                        style={{ marginRight: 8 }}
                      />
                      {genre}
                    </label>
                  ))}
                </div>
              )}
            </div>
          </div>
          <div className="filter-right">
            <label htmlFor="sort-select" style={{ marginRight: 8, color: '#29B6F6', fontWeight: 500 }}>Ordenar por:</label>
            <select
              id="sort-select"
              value={sortOption}
              onChange={e => setSortOption(e.target.value)}
              className="sort-button"
            >
              <option value="nameAsc">Nome (A-Z)</option>
              <option value="nameDesc">Nome (Z-A)</option>
              <option value="metacriticDesc">Metacritic ↓</option>
              <option value="metacriticAsc">Metacritic ↑</option>
              <option value="userRatingDesc">Usuários ↓</option>
              <option value="userRatingAsc">Usuários ↑</option>
            </select>
          </div>
        </div>
      </div>

      {displayGames.length === 0 ? (
        <div className="no-games">
          <p>{searchTerm ? 'Nenhum jogo encontrado para sua busca.' : 'Nenhum jogo encontrado.'}</p>
        </div>
      ) : (
        <div className="games-grid">
          {displayGames.map((game) => (
            <div 
              key={game.id} 
              className="game-card" 
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
                <h3 className="game-title">{game.name}</h3>
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
            </div>
          ))}
        </div>
      )}
    </div>
  );
};

export default Home;
