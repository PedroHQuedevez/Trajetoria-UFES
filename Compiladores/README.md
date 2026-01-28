# trab-compiladores
Desenvolvimento de um compilador para linguagem Pascal

# Requisitos
[Antlr4](https://www.antlr.org/download/antlr-4.13.2-complete.jar)
java
javac

# Estrutura do Projeto
- [src](src) - Contém os arquivos fonte do compilador.
    - [parser](src/parser) - Contém os arquivos gerados pelo ANTLR.
    - [checker](src/checker) - Contém o verificador semântico.
    - [typing](src/typing) - Contém a enumeração dos tipos de dados utilizados no compilador.
    - [Main.java](src/Main.java) - Ponto de entrada do compilador.
- [tools](tools) - Contém antlr4;
- [tests](tests) - Contém os testes automatizados.
    - [in](tests/in) - Contém os arquivos de entrada para os testes.
    - [out](tests/out) - Contém os arquivos de saída esperados para os testes.
- [run_tests.sh](run_tests.sh) - Script para executar os testes automatizados.
- [compare.sh](compare.sh) - Script para comparar a saída dos testes com os resultados esper
- [Makefile](Makefile) - Arquivo de construção do projeto.
- [PascalLexer.g](PascalLexer.g) - Arquivo de gramática do ANTLR para o lexer.
- [PascalParser.g](PascalParser.g) - Arquivo de gramática do ANTLR para o parser.

# Utilização
1. Clone o repositório na sua máquina:
```bash
git clone https://github.com/RenanCampista/trab-compiladores.git
```
2. Execute o comando make
```bash
make
```
3. Para realizar tests automatizados, utilize o comando abaixo:
```bash
make test
```
4. Você pode comparar a saída dos testes com os resultados esperados utilizando o comando:
```bash
make compare
```