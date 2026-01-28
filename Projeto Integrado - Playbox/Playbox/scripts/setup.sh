#!/bin/bash

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Função para imprimir mensagens coloridas
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Função para verificar se um comando existe
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Função para verificar se um diretório existe
dir_exists() {
    [ -d "$1" ]
}

# Função para limpar cache npm se necessário
clean_npm_cache() {
    print_info "Verificando cache npm..."
    if npm cache verify 2>/dev/null | grep -q "issues"; then
        print_warning "Cache npm com problemas. Limpando..."
        npm cache clean --force
    fi
}

# Header
echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}         SETUP SCRIPT           ${NC}"
echo -e "${BLUE}================================${NC}"
echo ""

# Verificar se Node.js está instalado
print_info "Verificando Node.js..."
if command_exists node; then
    NODE_VERSION=$(node --version)
    print_success "Node.js encontrado: $NODE_VERSION"
else
    print_error "Node.js não encontrado. Por favor, instale Node.js primeiro."
    echo "Visite: https://nodejs.org/"
    exit 1
fi

# Verificar se npm está instalado
print_info "Verificando npm..."
if command_exists npm; then
    NPM_VERSION=$(npm --version)
    print_success "npm encontrado: $NPM_VERSION"
else
    print_error "npm não encontrado. Por favor, instale npm primeiro."
    exit 1
fi

# Obter o diretório do script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SCRIPT_DIR="$SCRIPT_DIR/.."
print_info "Diretório do projeto: $SCRIPT_DIR"

# Verificar estrutura do projeto
print_info "Verificando estrutura do projeto..."

if ! dir_exists "$SCRIPT_DIR/server"; then
    print_error "Diretório 'server' não encontrado!"
    exit 1
fi

if ! dir_exists "$SCRIPT_DIR/client"; then
    print_error "Diretório 'client' não encontrado!"
    exit 1
fi

print_success "Estrutura do projeto verificada"

# Limpar cache npm se necessário
clean_npm_cache

# Configurar Backend
echo ""
print_info "Configurando Backend..."
cd "$SCRIPT_DIR/server"

if [ ! -f "package.json" ]; then
    print_error "package.json não encontrado no server!"
    exit 1
fi

# Limpar node_modules se existir com permissões incorretas
if [ -d "node_modules" ]; then
    if [ ! -w "node_modules" ]; then
        print_warning "node_modules com permissões inadequadas. Removendo..."
        sudo rm -rf node_modules
    fi
fi

print_info "Instalando dependências do server..."
npm install

if [ $? -eq 0 ]; then
    print_success "Dependências do server instaladas com sucesso"
else
    print_error "Falha ao instalar dependências do server"
    exit 1
fi

# Verificar se o Prisma está configurado
print_info "Configurando Prisma..."
if [ -f "prisma/schema.prisma" ]; then
    print_info "Gerando cliente Prisma..."
    npx prisma generate
    
    if [ $? -eq 0 ]; then
        print_success "Cliente Prisma gerado com sucesso"
    else
        print_error "Falha ao gerar cliente Prisma"
        exit 1
    fi
else
    print_warning "Schema do Prisma não encontrado. Pule se não for necessário."
fi

# Configurar Frontend
echo ""
print_info "Configurando Frontend..."
cd "$SCRIPT_DIR/client"

if [ ! -f "package.json" ]; then
    print_error "package.json não encontrado no client!"
    exit 1
fi

# Limpar node_modules se existir com permissões incorretas
if [ -d "node_modules" ]; then
    if [ ! -w "node_modules" ]; then
        print_warning "node_modules com permissões inadequadas. Removendo..."
        sudo rm -rf node_modules
    fi
fi

print_info "Instalando dependências do client..."
npm install

if [ $? -eq 0 ]; then
    print_success "Dependências do client instaladas com sucesso"
else
    print_error "Falha ao instalar dependências do client"
    exit 1
fi

# Voltar para a raiz do projeto
cd "$SCRIPT_DIR"

# Criar arquivo .env centralizado na raiz se não existir
if [ ! -f ".env" ]; then
    print_info "Criando arquivo .env centralizado na raiz do projeto..."
    if [ -f ".env.example" ]; then
        cp .env.example .env
        print_success "Arquivo .env criado a partir do .env.example"
        print_warning "IMPORTANTE: Configure a DATABASE_URL com suas credenciais do Neon.tech"
    else
        print_warning "Arquivo .env.example não encontrado. Criando .env básico..."
        cat > .env << 'EOF'
# Database
DATABASE_URL="postgresql://user:password@localhost:5432/playbox?schema=public"

# JWT
JWT_SECRET="your-super-secret-jwt-key-change-this-in-production"

# Server
SERVER_PORT=5000
NODE_ENV=development

# Client
REACT_APP_API_URL=http://localhost:5000
EOF
        print_success "Arquivo .env básico criado"
        print_warning "IMPORTANTE: Configure o arquivo .env com suas credenciais reais!"
    fi
else
    print_info "Arquivo .env já existe na raiz do projeto"
fi

# Criar link simbólico no client para usar o .env da raiz
print_info "Configurando client para usar .env centralizado..."
cd "$SCRIPT_DIR/client"
if [ -f ".env" ] && [ ! -L ".env" ]; then
    rm .env
fi
if [ ! -L ".env" ]; then
    ln -sf ../.env .env
    print_success "Link simbólico criado para o client"
fi

# Verificar configuração do server
print_info "Verificando configuração do server..."
cd "$SCRIPT_DIR/server"

# Resumo final
echo ""
echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}     SETUP CONCLUÍDO COM SUCESSO${NC}"
echo -e "${GREEN}================================${NC}"
echo ""

print_info "Próximos passos:"
echo ""
echo "   1. Configure o arquivo .env na raiz do projeto com suas credenciais do Neon.tech"
echo "   2. Terminal 1: make start_server"
echo "   3. Terminal 2: make start_frontend"
echo ""

print_info "Configuração centralizada:"
echo "   Arquivo .env na raiz controla todas as configurações"
echo "   Tanto desenvolvimento local quanto Docker usam o mesmo arquivo"
echo ""

print_success "Setup concluído!"
