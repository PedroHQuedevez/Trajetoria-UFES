/**
 * @fileoverview Servidor principal da API Playbox
 * @description Configura e inicia o servidor Express com conexão ao banco de dados
 */

require('dotenv').config({ path: '../.env' });
const express = require('express'); // Framework para construir APIs
const cors = require('cors'); // Middleware para habilitar CORS
const { getUserByEmail, createAdmin } = require('./services/userServices.js');
const app = express();
const routes = require('./routes/index.js'); // Importa as rotas organizadas

const prisma = require('./services/prisma.js'); // Importa o cliente Prisma

app.use(cors()); // Habilita CORS para todas as rotas. CORS é necessário para permitir que o frontend acesse a API
app.use(express.json()); // Middleware para interpretar JSON no corpo das requisições
app.use(routes);

const PORT = process.env.PORT || process.env.SERVER_PORT || 5000; // Render usa PORT, local usa SERVER_PORT

/**
 * Inicia o servidor e configura conexões iniciais
 * @description Conecta ao banco de dados e cria usuário admin se necessário
 */
app.listen(PORT, async () => {

    // Verificar se a conexão com o banco de dados foi bem-sucedida
    try {
        await prisma.$connect();
        console.log(`✅ Conexão com o banco de dados estabelecida`);
    } catch (error) {
        console.error(`❌ Erro ao conectar com o banco de dados: ${error.message}`);
        process.exit(1);
    }

    // Verificar se o banco de dados já possui um user admin
    try {
        const email = process.env.ADMIN_EMAIL || 'admin@email.com';

        const admin = await getUserByEmail(email);
        if (!admin.user) {
            const name = 'admin';
            const password = process.env.ADMIN_PASSWORD || 'admin123';
            const data = { name, email, password };
            await createAdmin(data);
            console.log(`✅ Usuário admin criado com sucesso.`);
        } else {
            console.log(`✅ Usuário admin já existe.`);
        }
    } catch (error) {
        console.error(`❌ Erro ao verificar usuário admin: ${error.message}`);
        process.exit(1);
    }

    console.log(`🚀 Servidor rodando na porta ${PORT}`);
    console.log(`📡 API disponível em http://localhost:${PORT}`);
});

/**
 * Encerramento gracioso do servidor
 * @description Desconecta do banco de dados antes de encerrar o processo
 */
process.on('SIGINT', async () => {
    console.log('🔄 Encerrando servidor graciosamente...');
    await prisma.$disconnect();
    console.log('✅ Conexão com banco de dados encerrada');
    process.exit(0);
});

/**
 * Encerramento gracioso do servidor
 * @description Desconecta do banco de dados antes de encerrar o processo
 */
process.on('SIGTERM', async () => {
    console.log('🔄 Encerrando servidor graciosamente...');
    await prisma.$disconnect();
    console.log('✅ Conexão com banco de dados encerrada');
    process.exit(0);
});
