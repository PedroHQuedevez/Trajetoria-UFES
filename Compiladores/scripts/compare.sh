#!/bin/bash
# filepath: /home/labic/Área de Trabalho/trab-compiladores/tests/compare.sh

OUT_CORRETA="../tests/out"
OUT_TESTE="../tests/out_test"

cd "$(dirname "$0")"

passou=0
falhou=0

for ref in "$OUT_CORRETA"/*.out; do
    nome=$(basename "$ref")
    teste="$OUT_TESTE/$nome"
    if [ ! -f "$teste" ]; then
        echo "❌ Arquivo de teste ausente: $teste"
        falhou=$((falhou+1))
        continue
    fi
    if diff -q "$ref" "$teste" > /dev/null; then
        echo "✅ $nome: OK"
        passou=$((passou+1))
    else
        echo "❌ $nome: Diferente"
        falhou=$((falhou+1))
        diff "$ref" "$teste"
    fi
done

echo
echo "Total OK: $passou"
echo "Total com diferença/erro: $falhou"