# Usar uma imagem base do Node.js
FROM node:18-alpine

# Definir o diretório de trabalho
WORKDIR /app

# Copiar package.json e package-lock.json (se existir)
COPY package*.json ./

# Instalar dependências
RUN npm install

# Copiar o código fonte
COPY . .

# Gerar o cliente Prisma
RUN npx prisma generate

# Expor a porta que o servidor usa
EXPOSE 5000

# Comando para iniciar a aplicação
CMD ["npm", "start"]