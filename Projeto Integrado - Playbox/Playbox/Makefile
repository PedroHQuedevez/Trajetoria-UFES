.PHONY: help up down migrate install clean

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  docker         		- Sobe containers"
	@echo "  down       		- Para todos os containers"
	@echo "  migrate    		- Executa migrações do banco"
	@echo "  install      		- Executa script de setup inicial para configuração sem Docker"
	@echo "  start_server 		- Inicia o servidor sem Docker"
	@echo "  start_frontend 	- Inicia o frontend sem Docker"
	@echo "  clean      		- Remove containers, volumes, imagens e node_modules"
	@echo "  docs       		- Gera documentação de código para backend e frontend"
	@echo "  test       		- Executa testes automatizados da API"

# Up
docker:
	docker-compose up -d

# Down
down:
	docker-compose down

# Utilitários
migrate:
	@echo "Executando migrações..."
	docker-compose exec backend npx prisma migrate deploy

# Setup inicial (usar script de setup)
install:
	chmod +x ./scripts/setup.sh
	./scripts/setup.sh

# npm start sem Docker
start_server:
	@echo "Iniciando servidor sem Docker..."
	cd server && npm start

start_frontend:
	@echo "Iniciando frontend sem Docker..."
	cd client && npm start

test:
	@echo "Executando testes automatizados da API..."
	cd server && npm test

# Limpeza
clean:
	@echo "Limpando containers, volumes e imagens do projeto..."
	docker-compose down -v --rmi all --remove-orphans || true
	@echo "Limpando node_modules..."
	sudo rm -rf server/node_modules client/node_modules || true
	@echo "Limpando cache npm..."
	npm cache clean --force || true

docs:
	@echo "Gerando documentação de código..."
	cd server && npm run docs
	@echo "Documentação do backend gerada em server/docs"
	cd client && npm run docs
	@echo "Documentação do frontend gerada em client/docs"