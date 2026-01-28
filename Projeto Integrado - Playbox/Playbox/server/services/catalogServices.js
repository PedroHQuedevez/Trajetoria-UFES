/**
 * @fileoverview Serviços de catálogos
 * @description Contém todas as funções relacionadas ao gerenciamento de catálogos de jogos
 */

const prisma = require("./prisma.js")

/**
 * Formatar strings separadas por vírgula em arrays (facilitar o carregamento do jogo)
 * @param {string} str - String separada por vírgulas
 * @returns {Array} Array de strings
 */
const stringToArray = (str) => {
    return str ? str.split(',').map(item => item.trim()).filter(item => item.length > 0) : [];
};

/**
 * Formata o jogo para retorno convertendo strings em arrays
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
 * Cria um novo catálogo
 * @param {Object} catalogData - Dados do catálogo
 * @param {string} catalogData.name - Nome do catálogo
 * @param {number} catalogData.userId - ID do usuário proprietário
 * @returns {Promise<Object>} Resultado da operação com dados do catálogo
 * @throws {Error} Erro se catálogo já existe ou falha na criação
 */
const createCatalog = async (catalogData) => {
    try {
        const { name, userId } = catalogData;

        // Verificar se o catálogo já existe
        const existingCatalog = await prisma.catalog.findFirst({
            where: { name, userId }
        });
        if (existingCatalog) {
            return { status: 400, message: 'Catálogo já existe.' };
        }

        // Criar novo catálogo
        const catalog = await prisma.catalog.create({
            data: {
                name,
                userId
            }
        });

        return { status: 201, catalog };
    } catch (error) {
        console.error('Erro ao criar catálogo:', error);
        throw new Error('Erro ao criar catálogo');
    }
}

/**
 * Busca catálogo por ID
 * @param {number} id - ID do catálogo
 * @returns {Promise<Object>} Dados do catálogo com jogos e informações do usuário
 */
const getCatalogById = async (id) => {
    try {
        const catalog = await prisma.catalog.findUnique({
            where: { id },
            include: {
                games: true,
                user: true
            }
        });

        if (!catalog) {
            return { status: 404, message: 'Catálogo não encontrado.' };
        }

        // Formatar os jogos para retorno
        const formattedCatalog = {
            ...catalog,
            games: catalog.games.map(formatGameForResponse)
        };

        return { status: 200, catalog: formattedCatalog };
    } catch (error) {
        console.error('Erro ao buscar catálogo:', error);
        throw new Error('Erro ao buscar catálogo');
    }
}

/**
 * Busca todos os catálogos de um usuário específico
 * @param {number} userId - ID do usuário
 * @returns {Promise<Object>} Lista de catálogos do usuário com jogos formatados
 */
const getCatalogsByUserId = async (userId) => {
    try {
        const catalogs = await prisma.catalog.findMany({
            where: { userId },
            include: {
                games: true
            }
        });

        // Formatar os jogos para retorno
        const formattedCatalogs = catalogs.map(catalog => ({
            ...catalog,
            games: catalog.games.map(formatGameForResponse)
        }));

        return { status: 200, catalogs: formattedCatalogs };
    } catch (error) {
        console.error('Erro ao buscar catálogos do usuário:', error);
        throw new Error('Erro ao buscar catálogos do usuário');
    }
}

/**
 * Adiciona um jogo a um catálogo
 * @param {number} catalogId - ID do catálogo
 * @param {number} gameId - ID do jogo
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se catálogo não encontrado ou jogo já está no catálogo
 */
const addGameToCatalog = async (catalogId, gameId) => {
    try {
        // Verificar se o catálogo existe
        const catalog = await prisma.catalog.findUnique({
            where: { id: catalogId }
        });
        if (!catalog) {
            return { status: 404, message: 'Catálogo não encontrado.' };
        }

        // Verificar se o jogo já está no catálogo
        const existingGame = await prisma.catalog.findFirst({
            where: {
                id: catalogId,
                games: {
                    some: { id: gameId }
                }
            }
        });
        if (existingGame) {
            return { status: 400, message: 'Jogo já está no catálogo.' };
        }

        // Adicionar jogo ao catálogo
        await prisma.catalog.update({
            where: { id: catalogId },
            data: {
                games: {
                    connect: { id: gameId }
                }
            }
        });

        return { status: 200, message: 'Jogo adicionado ao catálogo com sucesso.' };
    } catch (error) {
        console.error('Erro ao adicionar jogo ao catálogo:', error);
        throw new Error('Erro ao adicionar jogo ao catálogo');
    }
}

/**
 * Remove um jogo de um catálogo
 * @param {number} catalogId - ID do catálogo
 * @param {number} gameId - ID do jogo
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se catálogo não encontrado ou jogo não está no catálogo
 */
const removeGameFromCatalog = async (catalogId, gameId) => {
    try {
        // Verificar se o catálogo existe
        const catalog = await prisma.catalog.findUnique({
            where: { id: catalogId }
        });
        if (!catalog) {
            return { status: 404, message: 'Catálogo não encontrado.' };
        }

        // Verificar se o jogo está no catálogo
        const existingGame = await prisma.catalog.findFirst({
            where: {
                id: catalogId,
                games: {
                    some: { id: gameId }
                }
            }
        });
        if (!existingGame) {
            return { status: 400, message: 'Jogo não encontrado no catálogo.' };
        }

        // Remover jogo do catálogo
        await prisma.catalog.update({
            where: { id: catalogId },
            data: {
                games: {
                    disconnect: { id: gameId }
                }
            }
        });

        return { status: 200, message: 'Jogo removido do catálogo com sucesso.' };
    } catch (error) {
        console.error('Erro ao remover jogo do catálogo:', error);
        throw new Error('Erro ao remover jogo do catálogo');
    }
}

/**
 * Remove um catálogo do sistema
 * @param {number} id - ID do catálogo
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se catálogo não encontrado
 */
const deleteCatalog = async (id) => {
    try {
        const deletedCatalog = await prisma.catalog.delete({
            where: { id }
        });
        return { status: 200, message: 'Catálogo deletado com sucesso', deletedCatalog };
    } catch (error) {
        console.error('Erro ao deletar catálogo:', error);
        throw new Error('Erro ao deletar catálogo');
    }
}

/**
 * Atualiza dados de um catálogo
 * @param {number} id - ID do catálogo
 * @param {Object} catalogData - Novos dados do catálogo
 * @param {string} catalogData.name - Novo nome do catálogo
 * @param {number} catalogData.userId - Novo ID do usuário proprietário
 * @returns {Promise<Object>} Dados do catálogo atualizado
 * @throws {Error} Erro se catálogo não encontrado
 */
const updateCatalog = async (id, catalogData) => {
    try {
        const { name, userId } = catalogData;

        // Verificar se o catálogo existe
        const existingCatalog = await prisma.catalog.findUnique({
            where: { id }
        });
        if (!existingCatalog) {
            return { status: 404, message: 'Catálogo não encontrado.' };
        }

        // Atualizar catálogo
        const updatedCatalog = await prisma.catalog.update({
            where: { id },
            data: {
                name,
                userId
            }
        });

        return { status: 200, updatedCatalog };
    } catch (error) {
        console.error('Erro ao atualizar catálogo:', error);
        throw new Error('Erro ao atualizar catálogo');
    }
}

/**
 * Busca todos os catálogos do sistema
 * @returns {Promise<Object>} Lista de todos os catálogos com jogos e usuários
 * @throws {Error} Erro se falha na busca
 */
const getAllCatalogs = async () => {
    try {
        const catalogs = await prisma.catalog.findMany({
            include: {
                games: true,
                user: true
            }
        });

        // Formatar os jogos para retorno
        const formattedCatalogs = catalogs.map(catalog => ({
            ...catalog,
            games: catalog.games.map(formatGameForResponse)
        }));

        return { status: 200, catalogs: formattedCatalogs };
    } catch (error) {
        console.error('Erro ao listar catálogos:', error);
        throw new Error('Erro ao listar catálogos');
    }
}

module.exports = {
    createCatalog,
    getCatalogById,
    getCatalogsByUserId,
    addGameToCatalog,
    removeGameFromCatalog,
    deleteCatalog,
    updateCatalog,
    getAllCatalogs
};