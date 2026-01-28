/**
 * @fileoverview Serviços de jogos
 * @description Contém todas as funções relacionadas ao gerenciamento de jogos
 */

const prisma = require("./prisma.js")
const fs = require('fs');

/**
 * Converte gêneros do JSON para o formato do enum
 * @param {string[]} genres - Array de gêneros
 * @returns {string|null} Gêneros convertidos separados por vírgula, ou null se algum gênero for inválido
 */
const convertGenresToEnum = (genres) => {
    const genreMap = {
        'Action': 'ACTION',
        'Adventure': 'ADVENTURE', 
        'Indie': 'INDIE',
        'Massively Multiplayer': 'MASSIVELY_MULTIPLAYER',
        'Platformer': 'PLATFORMER',
        'Puzzle': 'PUZZLE',
        'RPG': 'RPG',
        'Racing': 'RACING',
        'Shooter': 'SHOOTER',
        'Sports': 'SPORTS'
    };
    
    const convertedGenres = [];
    for (const genre of genres) {
        const mappedGenre = genreMap[genre];
        if (!mappedGenre) {
            // Se algum gênero não é reconhecido, retorna null para rejeitar o jogo
            return null;
        }
        convertedGenres.push(mappedGenre);
    }
    
    return convertedGenres.join(',');
};

/**
 * Converte arrays em strings separadas por vírgula
 * @param {Array} array - Array para converter
 * @returns {string} String separada por vírgulas
 */
const arrayToString = (array) => {
    return Array.isArray(array) ? array.join(',') : '';
};

/**
 * Converte strings em arrays
 * @param {string} str - String separada por vírgulas
 * @returns {Array} Array de strings
 */
const stringToArray = (str) => {
    return str ? str.split(',').map(item => item.trim()).filter(item => item.length > 0) : [];
};

/**
 * Formata o jogo para retorno (converter strings em arrays)
 * @param {Object} game - Objeto do jogo
 * @returns {Object|null} Jogo formatado ou null
 */
const formatGameForResponse = (game) => {
    if (!game) return null;
    
    return {
        ...game,
        platforms: stringToArray(game.platforms),
        genres: stringToArray(game.genres),
        publishers: stringToArray(game.publishers),
        screenshots: stringToArray(game.screenshots)
    };
};

/**
 * Cria um novo jogo no sistema
 * @param {Object} gameData - Dados do jogo
 * @param {string} gameData.name - Nome do jogo
 * @param {string} gameData.description - Descrição do jogo
 * @param {string} gameData.backgroundImage - URL da imagem de fundo
 * @param {string} gameData.releaseDate - Data de lançamento
 * @param {number} gameData.playtime - Tempo de jogo em horas
 * @param {string[]} gameData.platforms - Plataformas disponíveis
 * @param {string[]} gameData.genres - Gêneros do jogo
 * @param {string[]} gameData.publishers - Editoras do jogo
 * @param {number} gameData.metacriticScore - Pontuação no Metacritic
 * @param {string[]} gameData.screenshots - URLs das capturas de tela
 * @returns {Promise<Object>} Resultado da operação com dados do jogo
 * @throws {Error} Erro se jogo já existe ou falha na criação
 */
const createGame = async (gameData) => {
    const { name, description, backgroundImage, releaseDate, playtime, platforms, genres, publishers, metacriticScore, screenshots } = gameData;

    try {
        // Validar campos obrigatórios
        if (!name) {
            throw new Error('Nome do jogo é obrigatório');
        }
        
        if (!releaseDate) {
            throw new Error('Data de lançamento é obrigatória');
        }
        
        // Converter e validar releaseDate
        const parsedReleaseDate = new Date(releaseDate);
        if (isNaN(parsedReleaseDate.getTime())) {
            throw new Error('Data de lançamento inválida');
        }

        // Converter arrays para strings separadas por vírgula
        const convertedGenres = convertGenresToEnum(genres);
        if (!convertedGenres) {
            throw new Error('Jogo contém gêneros não suportados');
        }
        
        const platformsString = arrayToString(platforms);
        const publishersString = arrayToString(publishers);
        const screenshotsString = arrayToString(screenshots);
        
        // verificar se ja possui um jogo com esse nome
        try {
            const verifyGame = await getGameByName(name);
            if (verifyGame.status === 200) {
                return { status: 409, message: 'Este jogo já se encontra no banco de dados'};
            }
        } catch (error) {
            // Se der erro na verificação, continua com a criação
            console.log('Aviso: Erro ao verificar jogo existente, continuando com criação:', error.message);
        }

        const game = await prisma.game.create({
            data: {
                name,
                description,
                backgroundImage,
                releaseDate: parsedReleaseDate,
                playtime,
                platforms: platformsString,
                genres: convertedGenres,
                publishers: publishersString,
                metacriticScore,
                screenshots: screenshotsString
            }
        });
        
        // Formatar o jogo para retorno (converter strings em arrays)
        const formattedGame = formatGameForResponse(game);
        
        return { status: 200, game: formattedGame}
    } catch (error) {
        console.error('Erro ao criar jogo:', error);
        throw new Error('Erro ao criar jogo');
    }
}

/**
 * Busca jogo por ID
 * @param {number} id - ID do jogo
 * @returns {Promise<Object>} Dados do jogo ou mensagem de erro
 */
const getGameById = async (id) => {
    try {
        const game = await prisma.game.findUnique({
            where: { id },
            select: {
                id: true,
                name: true,
                description: true,
                backgroundImage: true,
                releaseDate: true,
                playtime: true,
                platforms: true,
                genres: true,
                publishers: true,
                metacriticScore: true,
                averageReviewRating: true,
                screenshots: true,
                createdAt: true,
            }
        });
        if (!game) {
            return { status: 404, message: 'Jogo não encontrado' };
        }
        
        // Formatar o jogo para retorno (converter strings em arrays)
        const formattedGame = formatGameForResponse(game);
        
        return { status: 200, game: formattedGame };
    } catch (error) {
        console.error('Erro ao buscar jogo:', error);
        throw new Error('Erro ao buscar jogo');
    }
}

/**
 * Busca jogo por nome
 * @param {string} name - Nome do jogo
 * @returns {Promise<Object>} Dados do jogo ou mensagem de erro
 */
const getGameByName = async (name) => {
    try {
        const game = await prisma.game.findFirst({
            where: { name },
            select: {
                id: true,
                name: true,
                description: true,
                backgroundImage: true,
                releaseDate: true,
                playtime: true,
                platforms: true,
                genres: true,
                publishers: true,
                metacriticScore: true,
                screenshots: true,
                createdAt: true,
            }
        });
        if (!game) {
            return { status: 404, message: 'Jogo não encontrado' };
        }
        
        // Formatar o jogo para retorno (converter strings em arrays)
        const formattedGame = formatGameForResponse(game);
        
        return { status: 200, game: formattedGame };
    } catch (error) {
        console.error('Erro ao buscar jogo:', error);
        throw new Error('Erro ao buscar jogo');
    }
}

/**
 * Atualiza dados de um jogo
 * @param {number} id - ID do jogo
 * @param {Object} gameData - Novos dados do jogo
 * @returns {Promise<Object>} Dados do jogo atualizado
 * @throws {Error} Erro se falha na atualização
 */
const updateGame = async (id, gameData) => {
    const { name, description, backgroundImage, releaseDate, playtime, platforms, genres, publishers, metacriticScore, screenshots } = gameData;

    try {
        // Validar e converter releaseDate se fornecida
        let parsedReleaseDate = undefined;
        if (releaseDate) {
            parsedReleaseDate = new Date(releaseDate);
            if (isNaN(parsedReleaseDate.getTime())) {
                throw new Error('Data de lançamento inválida');
            }
        }

        // Converter arrays para strings separadas por vírgula se fornecidos
        let convertedGenres = undefined;
        if (genres) {
            convertedGenres = convertGenresToEnum(genres);
            if (convertedGenres === null) {
                throw new Error('Jogo contém gêneros não suportados');
            }
        }
        
        const platformsString = platforms ? arrayToString(platforms) : undefined;
        const publishersString = publishers ? arrayToString(publishers) : undefined;
        const screenshotsString = screenshots ? arrayToString(screenshots) : undefined;
        
        const updatedGame = await prisma.game.update({
            where: { id },
            data: {
                name,
                description,
                backgroundImage,
                releaseDate: parsedReleaseDate,
                playtime,
                platforms: platformsString,
                genres: convertedGenres,
                publishers: publishersString,
                metacriticScore,
                screenshots: screenshotsString
            }
        });
        
        // Formatar o jogo para retorno (converter strings em arrays)
        const formattedGame = formatGameForResponse(updatedGame);
        
        return { status: 200, updatedGame: formattedGame };
    } catch (error) {
        console.error('Erro ao atualizar jogo:', error);
        throw new Error('Erro ao atualizar jogo');
    }
}

/**
 * Remove um jogo do sistema
 * @param {number} id - ID do jogo
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se jogo não encontrado
 */
const deleteGame = async (id) => {
    try {
        const deletedGame = await prisma.game.delete({
            where: { id }
        });
        return { status: 200, message: 'Jogo deletado com sucesso', deletedGame };
    } catch (error) {
        console.error('Erro ao deletar jogo:', error);
        throw new Error('Erro ao deletar jogo');
    }
}

/**
 * Busca jogos por gênero
 * @param {string} genre - Gênero para filtrar
 * @returns {Promise<Object>} Lista de jogos do gênero especificado
 * @throws {Error} Erro se falha na busca
 */
const getGamesByGenre = async (genre) => {
    try {
        const games = await prisma.game.findMany({
            where: {
                genres: {
                    contains: genre
                }
            },
            select: {
                id: true,
                name: true,
                description: true,
                backgroundImage: true,
                releaseDate: true,
                playtime: true,
                platforms: true,
                genres: true,
                publishers: true,
                metacriticScore: true,
                screenshots: true,
                createdAt: true,
            },
            orderBy: {
                name: 'asc' // Ordenar por nome, do A ao Z
            }
        });
        
        // Formatar os jogos para retorno (converter strings em arrays)
        const formattedGames = games.map(formatGameForResponse);
        
        return { status: 200, games: formattedGames };
    } catch (error) {
        console.error('Erro ao buscar jogos por gênero:', error);
        throw new Error('Erro ao buscar jogos por gênero');
    }
}

/**
 * Busca todos os jogos do sistema
 * @returns {Promise<Object>} Lista de todos os jogos
 * @throws {Error} Erro se falha na busca
 */
const getAllGames = async () => {
    try {
        const games = await prisma.game.findMany({
            select: {
                id: true,
                name: true,
                description: true,
                backgroundImage: true,
                releaseDate: true,
                playtime: true,
                platforms: true,
                genres: true,
                publishers: true,
                metacriticScore: true,
                averageReviewRating: true,
                screenshots: true,
                createdAt: true,
            }, 
            orderBy: {
                name: 'asc' // Ordenar por data de criação, do mais recente para o mais antigo
            }
        });
        
        // Formatar os jogos para retorno (converter strings em arrays)
        const formattedGames = games.map(formatGameForResponse);
        
        return { status: 200, games: formattedGames };
    } catch (error) {
        console.error('Erro ao buscar jogos:', error);
        throw new Error('Erro ao buscar jogos');
    }
}

/**
 * Recalcula todas as médias de avaliação dos jogos
 * @returns {Promise<Object>} Resultado da operação com contagem de jogos atualizados
 * @throws {Error} Erro se falha no recálculo
 * @description Percorre todos os jogos e recalcula a média baseada nas reviews
 */
const recalculateAllGameAverages = async () => {
    try {
        const games = await prisma.game.findMany({
            include: {
                reviews: true
            }
        });

        let updatedCount = 0;

        for (const game of games) {
            if (game.reviews.length === 0) {
                // Se não há reviews, definir como null
                await prisma.game.update({
                    where: { id: game.id },
                    data: { averageReviewRating: null }
                });
            } else {
                // Verificar se todas as reviews têm averageRating válido
                const validReviews = game.reviews.filter(review => 
                    review.averageRating !== null && review.averageRating !== undefined
                );
                
                if (validReviews.length === 0) {
                    // Se não há reviews válidas, definir como null
                    await prisma.game.update({
                        where: { id: game.id },
                        data: { averageReviewRating: null }
                    });
                } else {
                    // Calcular a média dos averageRating de todas as reviews válidas do jogo
                    const totalRating = validReviews.reduce((sum, review) => sum + review.averageRating, 0);
                    const averageReviewRating = totalRating / validReviews.length;

                    // Atualizar o jogo com a nova média
                    await prisma.game.update({
                        where: { id: game.id },
                        data: { averageReviewRating: parseFloat(averageReviewRating.toFixed(2)) }
                    });
                }
            }
            updatedCount++;
        }

        console.log(`✅ Médias de avaliação recalculadas para ${updatedCount} jogos`);
        return { success: true, updatedCount };
    } catch (error) {
        console.error('Erro ao recalcular médias de avaliação:', error);
        throw new Error('Erro ao recalcular médias de avaliação: ' + error.message);
    }
};

module.exports = {
    createGame,
    getGameById,
    getGameByName,
    updateGame,
    deleteGame,
    getGamesByGenre,
    getAllGames,
    recalculateAllGameAverages
};