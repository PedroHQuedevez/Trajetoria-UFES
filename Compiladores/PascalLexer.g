lexer grammar PascalLexer;

// '?' Significa opcionalidade
// '[]' Conjunto de caracteres 

// Fragmentos básicos
fragment DIGIT          : [0-9];
fragment LETTER         : [a-zA-Z];
fragment SIGN           : [+-];
fragment EXPONENT_PART  : [eE] SIGN? DIGIT+;


// Símbolos especiais (ISO 7185 Seção 6.1.2)
ASSIGN      : ':=';
EQUAL       : '=';
LESS        : '<';
GREATER     : '>';
LE          : '<=';
GE          : '>=';
NE          : '<>';
PLUS        : '+';
MINUS       : '-';
STAR        : '*';
SLASH       : '/';
LPAREN      : '(';
RPAREN      : ')';
LBRACK      : '[' | '(.';
RBRACK      : ']' | '.)';
COMMA       : ',';
COLON       : ':';
SEMICOLON   : ';';
DOT         : '.';
DOTDOT      : '..';
POINTER_REF : '^' | '@';


// Palavras reservadas (ISO 7185 Seção 6.1.2)
AND         : A N D;
ARRAY       : A R R A Y;
BEGIN       : B E G I N;
BOOLEAN     : B O O L E A N;
CASE        : C A S E;
CHAR        : C H A R;
CONST       : C O N S T;
DIV         : D I V;
DO          : D O;
DOWNTO      : D O W N T O;
ELSE        : E L S E;
END         : E N D;
FILE        : F I L E;
FOR         : F O R;
FUNCTION    : F U N C T I O N;
GOTO        : G O T O;
IF          : I F;
IN          : I N;
INTEGER     : I N T E G E R;
LABEL       : L A B E L;
MOD         : M O D;
NIL         : N I L;
NOT         : N O T;
OF          : O F;
OR          : O R;
PACKED      : P A C K E D;
PROCEDURE   : P R O C E D U R E;
PROGRAM     : P R O G R A M;
READ        : R E A D;
REAL        : R E A L;
RECORD      : R E C O R D;
REPEAT      : R E P E A T;
SET         : S E T;
STRING      : S T R I N G;
THEN        : T H E N;
TO          : T O;
TYPE        : T Y P E;
UNTIL       : U N T I L;
VAR         : V A R;
WHILE       : W H I L E;
WITH        : W I T H;
WRITE       : W R I T E;

//No padrão ISO 7185, readln e writeln não são palavras reservadas, mas procedimentos pré-definidos.
READ_LN    : R E A D L N;
WRITE_LN   : W R I T E L N;

// Números (ISO 7185 Seção 6.1.5)
fragment UNSIGNED_INTEGER : DIGIT+;
fragment UNSIGNED_REAL    : DIGIT+ '.' DIGIT+ (EXPONENT_PART)?
                          | DIGIT+ EXPONENT_PART;

fragment SIGNED_INTEGER : SIGN UNSIGNED_INTEGER;
fragment SIGNED_REAL    : SIGN UNSIGNED_REAL;

// NUMBER : UNSIGNED_INTEGER
//        | UNSIGNED_REAL
//        | SIGNED_INTEGER
//        | SIGNED_REAL;

INTEGER_VALUE : SIGNED_INTEGER
              | UNSIGNED_INTEGER;

REAL_VALUE    : SIGNED_REAL
              | UNSIGNED_REAL;

// Valores booleanos
BOOLEAN_VALUE : T R U E | F A L S E;


// Strings (ISO 7185 Seção 6.1.1) - apenas aspas simples
STRING_VALUE : '\'' ('\'\'' | ~'\'')* '\'';


// Identificadores (ISO 7185 Seção 6.1.4)
IDENTIFIER : LETTER (LETTER | DIGIT)*;


// Espaços em branco e comentários
WS : [ \t\r\n]+ -> skip ;
COMMENT : '(*' .*? '*)' -> skip ;
LINE_COMMENT : '{' .*? '}' -> skip ;


// Fragmentos para case insensitive
fragment A: [aA];
fragment B: [bB];
fragment C: [cC];
fragment D: [dD];
fragment E: [eE];
fragment F: [fF];
fragment G: [gG];
fragment H: [hH];
fragment I: [iI];
fragment J: [jJ];
fragment K: [kK];
fragment L: [lL];
fragment M: [mM];
fragment N: [nN];
fragment O: [oO];
fragment P: [pP];
fragment Q: [qQ];
fragment R: [rR];
fragment S: [sS];
fragment T: [tT];
fragment U: [uU];
fragment V: [vV];
fragment W: [wW];
fragment X: [xX];
fragment Y: [yY];
fragment Z: [zZ];
