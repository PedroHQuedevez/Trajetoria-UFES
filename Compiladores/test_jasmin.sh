#!/bin/bash

# Script para testar arquivos .j diretamente
# Uso: ./test_jasmin.sh arquivo.j

if [ $# -eq 0 ]; then
    echo "Uso: $0 <arquivo.j>"
    exit 1
fi

JASMIN_FILE=$1

echo "=== Testando arquivo Jasmin: $JASMIN_FILE ==="

# Verifica se o arquivo existe
if [ ! -f "$JASMIN_FILE" ]; then
    echo "Erro: Arquivo '$JASMIN_FILE' não encontrado!"
    exit 1
fi

# Compila com Jasmin
echo "Compilando com Jasmin..."
java -jar jasmin.jar "$JASMIN_FILE"

if [ $? -ne 0 ]; then
    echo "Erro na compilação com Jasmin!"
    exit 1
fi

echo "Compilação bem-sucedida!"

# Executa o bytecode
echo "Executando o programa..."
java PascalProgram

echo ""
echo "=== Teste concluído ==="

# Limpa arquivos temporários
rm -f PascalProgram.class