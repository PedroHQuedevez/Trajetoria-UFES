#!/bin/bash
# filepath: /home/labic/Área de Trabalho/trab-compiladores/run_tests.sh

IN_DIR="../tests/in"
OUT_DIR="../tests/out_test"
BIN_DIR="../bin"
ANTLR_JAR="../tools/antlr-4.13.2-complete.jar"

# Cria o diretório de saída se não existir
mkdir -p "$OUT_DIR"

# Executa para cada arquivo .pas em tests/in
for infile in "$IN_DIR"/*.pas; do
    fname=$(basename "$infile" .pas)
    outfile="$OUT_DIR/$fname.out"
    echo "Testando $infile -> $outfile"
    java -cp ".:$BIN_DIR:$ANTLR_JAR" Main "$infile" > "$outfile" 2>&1
done

echo "Todos os testes foram executados. Saídas em $OUT_DIR/"