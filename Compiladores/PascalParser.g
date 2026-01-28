parser grammar PascalParser;

options {
	tokenVocab = PascalLexer;
}

// Programa principal: estrutura básica de um programa Pascal
program:
	PROGRAM IDENTIFIER SEMICOLON 
	varsSect? 
	(functionDecl)* // Funções antes da seção de variáveis
	(procedureDecl)*
    stmtSect // bloco principal de código
	DOT // ponto final do programa
	EOF;

// Declaração de variáveis
varsSect:
	VAR varDecl*; // 'var' seguido de zero ou mais declarações

varDecl:
	identifierList COLON typeSpec SEMICOLON; // lista de identificadores ':' tipo ';'

identifierList:
	IDENTIFIER (COMMA IDENTIFIER)*; // um ou mais identificadores separados por ','

// Tipos básicos suportados
typeSpec: BOOLEAN | INTEGER | REAL | STRING | arrayType;

arrayType: ARRAY LBRACK range RBRACK OF typeSpec;

indexedVariable: IDENTIFIER LBRACK expr (expr)* RBRACK;

assignIndexed:  IDENTIFIER LBRACK expr (expr)* RBRACK ASSIGN expr;

range: INTEGER_VALUE DOTDOT INTEGER_VALUE; // intervalo de valores para arrays


// Statements
stmtSect:
	BEGIN stmtList END; // 'begin' lista de comandos 'end'

stmtList: (stmt SEMICOLON)*; // zero ou mais comandos, cada um seguido de ';'

// Comandos suportados
stmt
	: assignStmt // atribuição
	| ifStmt // if-then-else
	| readStmt // leitura
	| writeStmt // escrita
	| structureStmt // bloco 'begin...end'
	| forStmt // laço 'for'
  	| functionCall
	;

// Bloco composto (estrutura de comandos agrupados)
structureStmt: BEGIN stmtList END;

// Atribuição: var := expr
assignStmt: (IDENTIFIER | indexedVariable) ASSIGN expr ;

// Estrutura condicional: if-then-(else)
ifStmt: IF expr THEN (stmt | structureStmt) (ELSE (stmt | structureStmt))?;

// Comando de leitura: readln(var) Tem read sem ln?
readStmt
	: READ_LN (LPAREN IDENTIFIER? RPAREN)?
	| READ (LPAREN IDENTIFIER? RPAREN)?;

// Escrita: writeln(expr) Tem write sem ln?
writeStmt
	: WRITE_LN LPAREN expr (COMMA expr)* RPAREN
	| WRITE LPAREN expr (COMMA expr)* RPAREN;

forStmt:
	FOR IDENTIFIER ASSIGN exprFor (TO | DOWNTO) exprFor DO (
		BEGIN stmt SEMICOLON? END SEMICOLON
		| stmt 
		| structureStmt
	); //pode ser vazio;

// Expressões: aritméticas, relacionais, lógicas;
expr
	: expr AND expr # andExpr
	| expr OR expr # orExpr
	| expr relop expr # relExpr
	| expr addop expr # addExpr
	| expr mulop expr # mulExpr
  	| NOT expr # notExpr
	| LPAREN expr RPAREN # parenExpr
	| BOOLEAN_VALUE # booleanExpr
	| INTEGER_VALUE # integerExpr
	| REAL_VALUE # realExpr
	| STRING_VALUE # stringExpr
	| IDENTIFIER # identifierExpr
  	| functionCall # functionCallExpr
  	| indexedVariable # indexedVariableExpr
  	| assignIndexed # assignIndexedExpr
	;

// Expressões aceitas no laço for
exprFor: INTEGER_VALUE | IDENTIFIER;

// Operadores
mulop: STAR | SLASH | DIV | MOD;

addop: PLUS | MINUS;

relop: LESS | GREATER | LE | GE | NE | EQUAL;

// Declaração de função (para extensão futura) Estrutura: function IDENTIFIER
// Forma padrão: heading ; bloco
functionDecl
	: functionHeading SEMICOLON functionBlock
  	| FUNCTION IDENTIFIER COLON functionBlock
  	;

// (formalParameterList)? : resultType
functionHeading:
	FUNCTION IDENTIFIER (LPAREN formalParameterList RPAREN)? COLON typeSpec;

formalParameterList:
	identifierList COLON typeSpec (SEMICOLON identifierList COLON typeSpec)*;

functionBlock:
    varsSect? stmtSect SEMICOLON;

// Chamada de função
functionCall:
    IDENTIFIER LPAREN exprList? RPAREN;

exprList:
    expr (COMMA expr)*;

// Forma padrão: heading ; bloco
procedureDecl
  : procedureHeading SEMICOLON procedureBlock
  | PROCEDURE IDENTIFIER COLON procedureBlock
  ;

// (formalParameterList)? : resultType
procedureHeading:
	PROCEDURE IDENTIFIER (LPAREN formalParameterList RPAREN)?;

procedureBlock:
//Remover
    varsSect? stmtSect SEMICOLON;
