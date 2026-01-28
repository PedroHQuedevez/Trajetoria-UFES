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

# Expor a porta que o React usa por padrão
EXPOSE 3000

# Comando para iniciar a aplicação em modo de desenvolvimento
CMD ["npm", "start"]
