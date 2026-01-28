/**
 * @fileoverview Cliente Prisma
 * @description Configuração e exportação do cliente Prisma para acesso ao banco de dados
 */

const { PrismaClient } = require('@prisma/client')

/**
 * Cliente Prisma para conexão com o banco de dados
 * @type {PrismaClient}
 */
const prisma = new PrismaClient();

module.exports = prisma;