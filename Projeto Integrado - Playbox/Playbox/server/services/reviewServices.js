/**
 * @fileoverview Serviços de avaliações (reviews)
 * @description Contém todas as funções relacionadas ao gerenciamento de avaliações de jogos
 */

const prisma = require("./prisma.js")

/**
 * Cria uma nova avaliação para um jogo
 * @param {Object} reviewData - Dados da avaliação
 * @param {number} reviewData.gameId - ID do jogo
 * @param {number} reviewData.userId - ID do usuário
 * @param {number} reviewData.gameplayRating - Avaliação do gameplay (0-5)
 * @param {number} reviewData.visualRating - Avaliação visual (0-5)
 * @param {number} reviewData.audioRating - Avaliação do áudio (0-5)
 * @param {number} reviewData.difficultyRating - Avaliação da dificuldade (0-5)
 * @param {number} reviewData.immersionRating - Avaliação da imersão (0-5)
 * @param {number} reviewData.historyRating - Avaliação da história (0-5)
 * @param {string} reviewData.comment - Comentário da avaliação
 * @returns {Promise<Object>} Resultado da operação com dados da avaliação
 * @throws {Error} Erro se dados inválidos ou jogo não encontrado
 */
const createReview = async (reviewData) => {
    try {
        const { 
            gameId, 
            userId, 
            gameplayRating, 
            visualRating, 
            audioRating, 
            difficultyRating, 
            immersionRating, 
            historyRating, 
            comment 
        } = reviewData;

        // Validar que todos os ratings estão entre 0 e 5
        const ratings = [gameplayRating, visualRating, audioRating, difficultyRating, immersionRating, historyRating];
        
        for (const rating of ratings) {
            if (rating < 0 || rating > 5 || !Number.isInteger(rating)) {
                return { status: 400, message: 'Todos os ratings devem ser números inteiros entre 0 e 5 estrelas.' };
            }
        }

        // Calcular a média dos ratings (manter como float para precisão)
        const averageRating = (
            gameplayRating + 
            visualRating + 
            audioRating + 
            difficultyRating + 
            immersionRating + 
            historyRating
        ) / 6;

        // Verificar se o jogo existe
        const game = await prisma.game.findUnique({
            where: { id: gameId }
        });
        if (!game) {
            return { status: 404, message: 'Jogo não encontrado.' };
        }

        // Criar nova avaliação
        const review = await prisma.review.create({
            data: {
                gameId,
                userId,
                gameplayRating,
                visualRating,
                audioRating,
                difficultyRating,
                immersionRating,
                historyRating,
                averageRating: parseFloat(averageRating.toFixed(2)),
                comment
            }
        });

        // Atualizar a média de avaliação do jogo
        await updateGameAverageRating(gameId);

        return { status: 201, review };
    } catch (error) {
        console.error('Erro ao criar avaliação:', error);
        throw new Error('Erro ao criar avaliação');
    }
}

/**
 * Busca avaliação por ID
 * @param {number} id - ID da avaliação
 * @returns {Promise<Object>} Dados da avaliação com informações do jogo e usuário
 */
const getReviewById = async (id) => {
    try {
        if (!id || isNaN(Number(id))) {
            throw new Error('ID da avaliação inválido ou não fornecido');
        }
        
        const review = await prisma.review.findUnique({
            where: { id: Number(id) },
            select: {
                gameId: true,
                userId: true,
                gameplayRating: true,
                visualRating: true,
                audioRating: true,
                difficultyRating: true,
                immersionRating: true,
                historyRating: true,
                averageRating: true,
                comment: true,
                createdAt: true,
                updatedAt: true,
            }
        });
        
        if (!review) {
            return { status: 404, message: 'Avaliação não encontrada.' };
        }
        
        return { status: 200, review };
    } catch (error) {
        console.error('Erro ao buscar avaliação:', error);
        throw new Error('Erro ao buscar avaliação');
    }
}

/**
 * Busca todas as avaliações de um jogo específico
 * @param {number} gameId - ID do jogo
 * @returns {Promise<Object>} Lista de avaliações formatadas do jogo
 * @description Retorna avaliações ordenadas por data de criação (mais recentes primeiro)
 */
const getReviewsByGameId = async (gameId) => {
    try {
        const reviews = await prisma.review.findMany({
            where: { gameId },
            select: {
                id: true,
                gameplayRating: true,
                visualRating: true,
                audioRating: true,
                difficultyRating: true,
                immersionRating: true,
                historyRating: true,
                averageRating: true,
                comment: true,
                createdAt: true,
                updatedAt: true,
                user: {
                    select: {
                        id: true,
                        name: true,
                        email: true
                    }
                }
            },
            orderBy: {
                createdAt: 'desc'
            }
        });

        if (reviews.length === 0) {
            return { status: 404, message: 'Nenhuma avaliação encontrada para este jogo.' };
        }

        // Formatando os dados para melhor apresentação
        const formattedReviews = reviews.map(review => ({
            id: review.id,
            ratings: {
                gameplay: review.gameplayRating,
                visual: review.visualRating,
                audio: review.audioRating,
                difficulty: review.difficultyRating,
                immersion: review.immersionRating,
                history: review.historyRating,
                average: review.averageRating
            },
            comment: review.comment,
            user: {
                id: review.user.id,
                name: review.user.name
            },
            createdAt: review.createdAt,
            updatedAt: review.updatedAt
        }));

        return { status: 200, reviews: formattedReviews };
    } catch (error) {
        console.error('Erro ao buscar avaliações:', error);
        throw new Error('Erro ao buscar avaliações');
    }
}

/**
 * Atualiza uma avaliação existente
 * @param {number} reviewId - ID da avaliação
 * @param {Object} reviewData - Novos dados da avaliação
 * @param {number} reviewData.gameplayRating - Nova avaliação do gameplay (0-5)
 * @param {number} reviewData.visualRating - Nova avaliação visual (0-5)
 * @param {number} reviewData.audioRating - Nova avaliação do áudio (0-5)
 * @param {number} reviewData.difficultyRating - Nova avaliação da dificuldade (0-5)
 * @param {number} reviewData.immersionRating - Nova avaliação da imersão (0-5)
 * @param {number} reviewData.historyRating - Nova avaliação da história (0-5)
 * @param {string} reviewData.comment - Novo comentário da avaliação
 * @returns {Promise<Object>} Dados da avaliação atualizada
 * @throws {Error} Erro se avaliação não encontrada ou dados inválidos
 */
const updateReview = async (reviewId, reviewData) => {
    try {
        const { 
            gameplayRating, 
            visualRating, 
            audioRating, 
            difficultyRating, 
            immersionRating, 
            historyRating, 
            comment,
            gameId,
            userId
        } = reviewData;

        // Validar que todos os ratings estão entre 0 e 5
        const ratings = [gameplayRating, visualRating, audioRating, difficultyRating, immersionRating, historyRating];
        
        for (const rating of ratings) {
            if (rating < 0 || rating > 5 || !Number.isInteger(rating)) {
                return { status: 400, message: 'Todos os ratings devem ser números inteiros entre 0 e 5 estrelas.' };
            }
        }

        // Calcular a nova média dos ratings (manter como float para precisão)
        const averageRating = (
            gameplayRating + 
            visualRating + 
            audioRating + 
            difficultyRating + 
            immersionRating + 
            historyRating
        ) / 6;

        // Verificar se a avaliação existe
        const existingReview = await prisma.review.findUnique({
            where: { id: reviewId }
        });
        if (!existingReview) {
            return { status: 404, message: 'Avaliação não encontrada.' };
        }

        // Atualizar avaliação
        const updatedReview = await prisma.review.update({
            where: { id: reviewId },
            data: {
                gameplayRating,
                visualRating,
                audioRating,
                difficultyRating,
                immersionRating,
                historyRating,
                averageRating: parseFloat(averageRating.toFixed(2)),
                comment
            }
        });

        // Atualizar a média de avaliação do jogo
        await updateGameAverageRating(existingReview.gameId);

        return { status: 200, updatedReview };
    } catch (error) {
        console.error('Erro ao atualizar avaliação:', error);
        throw new Error('Erro ao atualizar avaliação');
    }
}

/**
 * Remove uma avaliação do sistema
 * @param {number} reviewId - ID da avaliação
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se avaliação não encontrada
 * @description Também atualiza a média de avaliação do jogo relacionado
 */
const deleteReview = async (reviewId, reviewData) => {
    try {
        console.log('deleteReview called with:', { reviewId, reviewData });
        
        const {
            userId
        } = reviewData;
        
        // Vamos usar uma transação para garantir atomicidade
        const result = await prisma.$transaction(async (prisma) => {
            // Primeiro, buscar a review para obter o gameId
            const existingReview = await prisma.review.findUnique({
                where: { id: reviewId },
                select: { gameId: true, userId: true }
            });
            
            if (!existingReview) {
                throw new Error('Review não encontrada');
            }
            
            if (existingReview.userId !== userId) {
                throw new Error('Permissão negada');
            }
            
            // Deletar a review
            await prisma.review.delete({
                where: { id: reviewId }
            });
            
            return existingReview.gameId;
        });
        console.log(result)

        // Atualizar a média de avaliação do jogo
        await updateGameAverageRating(result);

        return { status: 200, message: 'Avaliação deletada com sucesso.' };
    } catch (error) {
        console.error('Erro ao deletar avaliação:', error);
        
        // Verificar se é um erro de record não encontrado
        if (error.code === 'P2025') {
            return { status: 404, message: 'Avaliação não encontrada ou já foi deletada.' };
        }
        
        throw new Error('Erro ao deletar avaliação');
    }
}

/**
 * Busca todas as avaliações de um usuário específico
 * @param {number} userId - ID do usuário
 * @returns {Promise<Object>} Lista de avaliações do usuário com informações dos jogos
 */
const getReviewsByUserId = async (userId) => {
    try {
        const reviews = await prisma.review.findMany({
            where: { userId },
            include: {
                game: true
            }
        });

        if (reviews.length === 0) {
            return { status: 404, message: 'Nenhuma avaliação encontrada para este usuário.' };
        }

        return { status: 200, reviews };
    } catch (error) {
        console.error('Erro ao buscar avaliações do usuário:', error);
        throw new Error('Erro ao buscar avaliações do usuário');
    }
}

/**
 * Atualiza a média de avaliação do jogo
 * @param {number} gameId - ID do jogo
 * @returns {Promise<void>}
 * @throws {Error} Erro se falha na atualização
 * @description Recalcula e atualiza a média baseada em todas as avaliações do jogo
 */
const updateGameAverageRating = async (gameId) => {
    try {
        const reviews = await prisma.review.findMany({
            where: { gameId }
        });

        if (reviews.length === 0) {
            // Se não há reviews, definir como null
            await prisma.game.update({
                where: { id: gameId },
                data: { averageReviewRating: null }
            });
            return;
        }

        // Calcular a média dos averageRating de todas as reviews do jogo
        const totalRating = reviews.reduce((sum, review) => sum + review.averageRating, 0);
        const averageReviewRating = totalRating / reviews.length;

        // Atualizar o jogo com a nova média
        await prisma.game.update({
            where: { id: gameId },
            data: { averageReviewRating: parseFloat(averageReviewRating.toFixed(2)) }
        });
    } catch (error) {
        console.error('Erro ao atualizar média de avaliação do jogo:', error);
        throw new Error('Erro ao atualizar média de avaliação do jogo');
    }
}

module.exports = {
    createReview,
    getReviewById,
    getReviewsByGameId,
    updateReview,
    deleteReview,
    getReviewsByUserId,
    updateGameAverageRating
};