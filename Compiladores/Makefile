# Caminho raiz do projeto
ROOT := "$(shell pwd)"

# Ferramentas e opções
JAVAC := javac
JAVA := java

ANTLR_VERSION := 4.13.2
ANTLR_JAR := antlr-$(ANTLR_VERSION)-complete.jar
ANTLR_PATH := $(ROOT)/tools/$(ANTLR_JAR)
CLASS_PATH := .:$(ANTLR_PATH)
CLASS_PATH_OPTION := -cp $(CLASS_PATH)

# Jasmin
JASMIN_JAR := jasmin.jar

# ANTLR e TestRig
ANTLR4 := $(JAVA) -jar $(ANTLR_PATH)
TESTRIG := org.antlr.v4.gui.TestRig
GRUN := $(JAVA) $(CLASS_PATH_OPTION) ${TESTRIG}

# Projeto
GRAMMAR_NAME := Pascal
GEN_PATH := src/parser
PACKAGE_GEN := parser
BIN_PATH := bin

LEXER := $(GRAMMAR_NAME)Lexer.g
PARSER := $(GRAMMAR_NAME)Parser.g
GRAMMAR_FILES := $(LEXER) $(PARSER)

JAVA_SOURCES := $(wildcard src/**/*.java) src/Main.java

# Executa o ANTLR e o compilador Java
all: antlr javac
	@echo "Done."

# Executa o ANTLR para compilar a gramática
antlr: $(GRAMMAR_NAME)Lexer.g $(GRAMMAR_NAME)Parser.g
	$(ANTLR4) -no-listener -visitor -o $(GEN_PATH) -package $(PACKAGE_GEN) $(GRAMMAR_NAME)Lexer.g $(GRAMMAR_NAME)Parser.g

# Executa o javac para compilar os arquivos gerados
javac:
	rm -rf $(BIN_PATH)
	mkdir $(BIN_PATH)
	$(JAVAC) $(CLASS_PATH_OPTION) -d $(BIN_PATH) -sourcepath src $(JAVA_SOURCES)

# Testar o compilador
run:
	$(JAVA) -cp $(BIN_PATH):$(ANTLR_PATH) Main $(FILE)

# Testar o compilador gerando a arvore
run_tree:
	$(JAVA) -cp $(BIN_PATH):$(ANTLR_PATH) ${TESTRIG} $(PACKAGE_GEN).$(GRAMMAR_NAME) program $(FILE) -tree

# Compilar arquivo Pascal para Jasmin e executar na JVM
run_compiler:
	@echo "=== Compilando arquivo Pascal para Jasmin ==="
	$(JAVA) -cp $(BIN_PATH):$(ANTLR_PATH) Main $(FILE)
	@echo ""
	@echo "=== Compilando arquivo .j com Jasmin ==="
	$(JAVA) -jar $(JASMIN_JAR) $(FILE:.pas=.j)
	@echo ""
	@echo "=== Executando bytecode na JVM ==="
	$(JAVA) PascalProgram
	@echo ""
	@echo "=== Limpando arquivos temporários ==="
	@rm -f PascalProgram.class $(FILE:.pas=.j)

# Testar arquivo .j diretamente
test_jasmin:
	@echo "=== Compilando arquivo .j com Jasmin ==="
	$(JAVA) -jar $(JASMIN_JAR) $(FILE)
	@echo ""
	@echo "=== Executando bytecode na JVM ==="
	$(JAVA) PascalProgram
	@echo ""
	@echo "=== Limpando arquivos temporários ==="
	@rm -f PascalProgram.class

test:
	cd scripts && bash run_tests.sh

compare:
	cd scripts && bash compare.sh

# Remove os arquivos gerados pelo ANTLR
clean:
	@rm -rf $(GEN_PATH)/* $(BIN_PATH)
	clear

