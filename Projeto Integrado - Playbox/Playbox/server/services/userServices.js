/**
 * Remove o próprio usuário do sistema
 * @param {number} userId - ID do usuário
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se usuário não encontrado
 */
const deleteOwnUser = async (userId) => {
    try {
        const user = await prisma.user.findUnique({ where: { id: userId } });
        if (!user) {
            throw new Error("Usuário não encontrado.");
        }

        // Usar transação para garantir atomicidade
        await prisma.$transaction(async (prisma) => {
            // Deletar todas as reviews do usuário primeiro
            await prisma.review.deleteMany({
                where: { userId: userId }
            });

            // Deletar todos os catálogos do usuário
            await prisma.catalog.deleteMany({
                where: { userId: userId }
            });

            // Agora deletar o usuário
            await prisma.user.delete({
                where: { id: userId }
            });
        });

        return { status: 200, message: "Sua conta foi excluída com sucesso." };
    } catch (error) {
        if (error.code === 'P2025') {
            throw new Error("Usuário não encontrado.");
        }
        console.error('Erro ao excluir a própria conta:', error);
        throw new Error("Erro ao excluir a própria conta: " + error.message);
    }
}
/**
 * @fileoverview Serviços de usuário
 * @description Contém todas as funções relacionadas ao gerenciamento de usuários
 */

const prisma = require("./prisma.js")
const bcrypt = require("bcryptjs")
const jwt = require("jsonwebtoken")


// Chave secreta para JWT
const JWT_SECRET = process.env.JWT_SECRET || 'chave-secreta';

/**
 * Cria um novo usuário no sistema
 * @param {Object} userData - Dados do usuário
 * @param {string} userData.name - Nome do usuário
 * @param {string} userData.email - Email do usuário
 * @param {string} userData.password - Senha do usuário
 * @returns {Promise<Object>} Resultado da operação com status e dados do usuário
 * @throws {Error} Erro se dados obrigatórios não fornecidos ou email/nome já em uso
 */
const createUser = async (userData) => {
    try {
        const { name, email, password } = userData;

        if (!name || !email || !password) {
            throw new Error("Todos os campos são obrigatórios.");
        }

        // O número 10 significa o custo de hashing, quanto maior, mais seguro, mas mais lento.
        const hashedPassword = await bcrypt.hash(password, 10);

        const user = await prisma.user.create({
            data: {
                name,
                email,
                password: hashedPassword,
                isAdmin: false, // Setado para false por padrão
                catalogs: {
                    create: {
                        name: `Favoritos de ${name}`
                    }
                }
            },
            select: {
                id: true,
                name: true,
                email: true,
                isAdmin: true,
                createdAt: true,
                catalogs: {
                    select: {
                        id: true,
                        name: true,
                    }
                }
            }
        });
        
        return { status: 201, message: "Usuário criado com sucesso.", user };
    } catch (error) {
        if (error.code === 'P2002') {
            const field = error.meta?.target?.[0];
            if (field === 'name') {
                throw new Error("Nome de usuário já está em uso.");
            } else if (field === 'email') {
                throw new Error("Email já está em uso.");
            } else {
                throw new Error("Erro ao criar usuário: " + error.message);
            }
        } else {
            console.error('Erro ao criar usuário:', error);
            throw new Error("Erro ao criar usuário: " + error.message);
        }
    }
}

/**
 * Busca todos os usuários do sistema
 * @returns {Promise<Object>} Lista de usuários com status 200
 * @throws {Error} Erro se falha na busca
 */
const getAllUsers = async () => {
    try {
        const users = await prisma.user.findMany({
            select: {
                id: true,
                name: true,
                email: true,
                isAdmin: true,
                createdAt: true
            }
        });
        return { status: 200, users };
    } catch (error) {
        console.error('Erro ao buscar usuários:', error);
        throw new Error("Erro ao buscar usuários: " + error.message);
    }
}

/**
 * Busca usuário por ID
 * @param {number} userId - ID do usuário
 * @returns {Promise<Object>} Dados do usuário com status 200
 * @throws {Error} Erro se usuário não encontrado
 */
const getUserById = async (userId) => {
    try {
        const user = await prisma.user.findUnique({
            where: { id: userId },
            select: {
                id: true,
                name: true,
                email: true,
                isAdmin: true,
                createdAt: true
            }
        });

        if (!user) {
            throw new Error("Usuário não encontrado.");
        }

        return { status: 200, user };
    } catch (error) {
        console.error('Erro ao buscar usuário:', error);
        throw new Error("Erro ao buscar usuário: " + error.message);
    }
}

/**
 * Busca usuário por email
 * @param {string} email - Email do usuário
 * @returns {Promise<Object>} Dados do usuário ou mensagem de não encontrado
 */
const getUserByEmail = async (email) => {
    try {
        const user = await prisma.user.findUnique({
            where: { email },
            select: {
                id: true,
                name: true,
                email: true,
                isAdmin: true,
                createdAt: true
            }
        });

        if (!user) {
            return { status: 404, message: "Usuário não encontrado." };
        }

        return { status: 200, user };
    } catch (error) {
        console.error('Erro ao buscar usuário por email:', error);
        throw new Error("Erro ao buscar usuário por email: " + error.message);
    }
}

/**
 * Atualiza dados de um usuário
 * @param {number} userId - ID do usuário
 * @param {Object} userData - Novos dados do usuário
 * @param {string} userData.name - Nome do usuário
 * @param {string} userData.email - Email do usuário
 * @param {string} [userData.password] - Nova senha (opcional)
 * @param {boolean} [userData.isAdmin] - Status de admin (opcional)
 * @returns {Promise<Object>} Dados do usuário atualizado
 * @throws {Error} Erro se usuário não encontrado ou dados inválidos
 */
const updateUser = async (userId, userData) => {
    try {
        const { name, email, password, isAdmin } = userData;

        if (!name || !email) {
            throw new Error("Nome e email são obrigatórios.");
        }

        const user = await prisma.user.findUnique({
            where: { id: userId }
        });

        if (!user) {
            throw new Error("Usuário não encontrado.");
        }

        const updatedData = {
            name,
            email,
            isAdmin: isAdmin !== undefined ? isAdmin : user.isAdmin // Mantém o valor atual se não for fornecido
        };

        if (password) {
            updatedData.password = await bcrypt.hash(password, 10);
        }

        const updatedUser = await prisma.user.update({
            where: { id: userId },
            data: updatedData,
            select: {
                id: true,
                name: true,
                email: true,
                isAdmin: true,
                createdAt: true
            }
        });

        return { status: 200, message: "Usuário atualizado com sucesso.", user: updatedUser };
    } catch (error) {
        if (error.code === 'P2002') {
            const field = error.meta?.target?.[0];
            if (field === 'name') {
                throw new Error("Nome de usuário já está em uso.");
            } else if (field === 'email') {
                throw new Error("Email já está em uso.");
            } else {
                throw new Error("Erro ao atualizar usuário: " + error.message);
            }
        }
        console.error('Erro ao atualizar usuário:', error);
        throw new Error("Erro ao atualizar usuário: " + error.message);
    }
}

/**
 * Remove um usuário do sistema
 * @param {number} userId - ID do usuário
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se usuário não encontrado
 */
const deleteUser = async (userId) => {
    try {
        const user = await prisma.user.findUnique({
            where: { id: userId }
        });

        if (!user) {
            throw new Error("Usuário não encontrado.");
        }

        // Usar transação para garantir atomicidade
        await prisma.$transaction(async (prisma) => {
            // Deletar todas as reviews do usuário primeiro
            await prisma.review.deleteMany({
                where: { userId: userId }
            });

            // Deletar todos os catálogos do usuário
            await prisma.catalog.deleteMany({
                where: { userId: userId }
            });

            // Agora deletar o usuário
            await prisma.user.delete({
                where: { id: userId }
            });
        });

        return { status: 200, message: "Usuário deletado com sucesso." };
    } catch (error) {
        if (error.code === 'P2025') {
            throw new Error("Usuário não encontrado.");
        }
        console.error('Erro ao deletar usuário:', error);
        throw new Error("Erro ao deletar usuário: " + error.message);
    }
}

/**
 * Autentica um usuário no sistema
 * @param {string} email - Email do usuário
 * @param {string} password - Senha do usuário
 * @returns {Promise<Object>} Token JWT e dados do usuário
 * @throws {Error} Erro se credenciais inválidas
 */
const authenticateUser = async (email, password) => {
    try {
        const user = await prisma.user.findUnique({
            where: { email }
        });

        if (!user) {
            throw new Error("Usuário não encontrado.");
        }

        const isPasswordValid = await bcrypt.compare(password, user.password);
        if (!isPasswordValid) {
            throw new Error("Senha incorreta.");
        }

        const token = jwt.sign({ id: user.id, isAdmin: user.isAdmin }, process.env.JWT_SECRET, { expiresIn: '1h' });

        return { status: 200, message: "Autenticação bem-sucedida.", token, user };
    } catch (error) {
        console.error('Erro ao autenticar usuário:', error);
        throw new Error("Erro ao autenticar usuário: " + error.message);
    }
}

/**
 * Verifica se um token JWT é válido
 * @param {string} token - Token JWT
 * @returns {Object} Status e dados do usuário decodificados
 * @throws {Error} Erro se token inválido ou expirado
 */
const verifyToken = (token) => {
    try {
        const decoded = jwt.verify(token, process.env.JWT_SECRET);
        return { status: 200, userId: decoded.id, isAdmin: decoded.isAdmin };
    } catch (error) {
        console.error('Erro ao verificar token:', error);
        throw new Error("Token inválido ou expirado.");
    }
}

/**
 * Middleware para autenticação de rotas
 * @param {Object} req - Objeto de requisição Express
 * @param {Object} res - Objeto de resposta Express
 * @param {Function} next - Função next do Express
 * @returns {void} Chama next() se autenticado ou retorna erro
 */
const authenticateToken = (req, res, next) => {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];

    if (!token) {
        return res.status(401).json({ error: "Acesso negado. Token não fornecido." });
    }

    jwt.verify(token, process.env.JWT_SECRET, (err, decoded) => {
        if (err) {
            return res.status(403).json({ error: "Token inválido." });
        }
        // decoded contém id, isAdmin, etc
        req.user = {
            id: decoded.id,
            name: decoded.name,
            email: decoded.email,
            isAdmin: decoded.isAdmin
        };
        next();
    });
}

/**
 * Altera a senha de um usuário
 * @param {number} userId - ID do usuário
 * @param {string} currentPassword - Senha atual
 * @param {string} newPassword - Nova senha
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se senha atual incorreta ou usuário não encontrado
 */
const changePassword = async (userId, currentPassword, newPassword) => {
    try {
        const user = await prisma.user.findUnique({ where: { id: userId } });

        if (!user) {
            throw new Error("Usuário não encontrado.");
        }

        const isCurrentPasswordValid = await bcrypt.compare(currentPassword, user.password);
        if (!isCurrentPasswordValid) {
            throw new Error("Senha atual incorreta.");
        }

        const hashedNewPassword = await bcrypt.hash(newPassword, 10);

        await prisma.user.update({
            where: { id: userId },
            data: { password: hashedNewPassword }
        });

        return { status: 200, message: "Senha alterada com sucesso!" };
    } catch (error) {
        console.error('Erro ao alterar senha:', error);
        throw new Error(error.message);
    }
};

/**
 * Solicita recuperação de senha
 * @param {string} email - Email do usuário
 * @param {string} jwtSecret - Chave secreta JWT
 * @returns {Promise<Object>} Token de recuperação (em desenvolvimento)
 * @throws {Error} Erro na geração do token
 */
const requestPasswordReset = async (email, jwtSecret) => {
    try {
        const user = await prisma.user.findUnique({ where: { email } });

        if (!user) {
            return { status: 200, message: "Se o email existir no sistema, você receberá instruções para redefinir sua senha." };
        }

        const resetToken = jwt.sign(
            { userId: user.id, email: user.email, type: 'password-reset' },
            jwtSecret,
            { expiresIn: '1h' }
        );

        return {
            status: 200,
            message: "Token de recuperação gerado com sucesso!",
            resetToken // ⚠️ Em produção, remova esta linha e envie o token por email
        };
    } catch (error) {
        console.error('Erro ao solicitar recuperação de senha:', error);
        throw new Error("Erro ao solicitar recuperação de senha.");
    }
};

/**
 * Redefine senha usando token de recuperação
 * @param {string} token - Token de recuperação
 * @param {string} newPassword - Nova senha
 * @param {string} jwtSecret - Chave secreta JWT
 * @returns {Promise<Object>} Mensagem de sucesso
 * @throws {Error} Erro se token inválido ou usuário não encontrado
 */
const resetPassword = async (token, newPassword, jwtSecret) => {
    try {
        const decoded = jwt.verify(token, jwtSecret);

        if (decoded.type !== 'password-reset') {
            throw new Error("Tipo de token inválido.");
        }

        const user = await prisma.user.findUnique({ where: { id: decoded.userId } });

        if (!user) {
            throw new Error("Usuário não encontrado.");
        }

        const hashedPassword = await bcrypt.hash(newPassword, 10);

        await prisma.user.update({
            where: { id: decoded.userId },
            data: { password: hashedPassword }
        });

        return { status: 200, message: "Senha redefinida com sucesso!" };
    } catch (error) {
        console.error('Erro ao redefinir senha:', error);
        throw new Error(error.message);
    }
};

/**
 * Cria um usuário administrador
 * @param {Object} adminData - Dados do administrador
 * @param {string} adminData.name - Nome do administrador
 * @param {string} adminData.email - Email do administrador
 * @param {string} adminData.password - Senha do administrador
 * @returns {Promise<Object>} Dados do administrador criado
 * @throws {Error} Erro se dados obrigatórios não fornecidos
 */
const createAdmin = async (adminData) => {
    try {
        const { name, email, password } = adminData;

        if (!name || !email || !password) {
            throw new Error("Nome, email e senha são obrigatórios.");
        }

        const hashedPassword = await bcrypt.hash(password, 10);

        const admin = await prisma.user.create({
            data: {
                name,
                email,
                password: hashedPassword,
                isAdmin: true,
                catalogs: {
                    create: {
                        name: `Favoritos de ${name}`
                    }
                }
            },
            select: {
                id: true,
                name: true,
                email: true,
                isAdmin: true,
                createdAt: true,
                catalogs: {
                    select: {
                        id: true,
                        name: true,
                    }
                }
            }
        });

        return { status: 201, message: "Administrador criado com sucesso!", user: admin };
    } catch (error) {
        console.error('Erro ao criar administrador:', error);
        throw new Error(error.message);
    }
};

/**
 * Middleware para verificar permissões de administrador
 * @param {Object} req - Objeto de requisição Express
 * @param {Object} res - Objeto de resposta Express
 * @param {Function} next - Função next do Express
 * @returns {void} Chama next() se for admin ou retorna erro 403
 */
const requireAdmin = (req, res, next) => {
    if (!req.user.isAdmin) {
        return res.status(403).json({ error: 'Acesso negado. Apenas administradores podem acessar.' });
    }
    next();
};

// Exportando os serviços. Isso faz com que esses métodos possam ser usados em outros arquivos.
module.exports = {
    createUser,
    getAllUsers,
    getUserById,
    getUserByEmail,
    updateUser,
    deleteUser,
    deleteOwnUser,
    authenticateUser,
    verifyToken,
    authenticateToken,
    changePassword,
    requestPasswordReset,
    resetPassword,
    createAdmin,
    requireAdmin
};