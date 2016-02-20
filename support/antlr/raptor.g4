grammar raptor;

anything
    : .*?
    ;

//
// Identifiers
//
NAME
    : [a-zA-Z_][a-zA-Z0-9_]*
    ;

//
// Literals (integral, floating-point, and strings)
//
LITERAL
    : INTEGER | FLOAT | BOOLEAN | STRING
    ;
INTEGER
    : [0-9]+
    ;
FLOAT
    : [0-9]+ '.' [0-9]* | '.' [0-9]+
    ;
BOOLEAN
    : TRUE | FALSE
    ;
STRING
    :  '"' (ESC_CHAR | ~('\\' | '"' | '\r' | '\n'))* '"'
    ;
CHARACTER
    :  '\'' (ESC_CHAR | ~('\\' | '\'' | '\r' | '\n')) '\''
    ;
ESC_CHAR
    :  '\\' ('\\' | '\'' | 't' | 'n' | 'r')
    ;

//
// Non-code elements
//
COMMENT
    : '#[' .*? '#]'
    | '#' ~[\r\n]*
    ;
WHITESPACE
    : [ \t\r\n\u000C]+ -> skip
    ;

//
// Reserved keywords
//
TRUE        : 'true'    ;
FALSE       : 'false'   ;
MAIN        : 'main'    ;
IMPORT      : 'import'  ;
PACKAGE     : 'package' ;
STRUCT      : 'struct'  ;
LENGTH      : 'len'     ;
AND         : 'and'     ;
OR          : 'or'      ;

//
// Punctuation
//
EXCLAIM     : '!'       ;
SEMI        : ';'       ;
COLON       : ':'       ;
COMMA       : ','       ;
PERIOD      : '.'       ;
QUESTION    : '?'       ;

//
// Operators
//
PLUS        : '+'       ;
MINUS       : '-'       ;
STAR        : '*'       ;
SLASH       : '/'       ;

EQUAL       : '='       ;
EQUAL2      : '=='      ;
NOT_EQUAL   : '!='      ;

PERCENT     : '%'       ;
CARET       : '^'       ;
AMP         : '&'       ;
PIPE        : '|'       ;
TILDE       : '~'       ;
HASH        : '#'       ;

LESS        : '<'       ;
LESS2       : '<<'      ;
LESS_EQ     : '<='      ;

GREATER     : '>'       ;
GREATER2    : '>>'      ;
GREATER_EQ  : '>='      ;

//
// Braces/brackets/parens
//
L_PAREN     : '('       ;
R_PAREN     : ')'       ;
L_BRACE     : '{'       ;
R_BRACE     : '}'       ;
L_SQUARE    : '['       ;
R_SQUARE    : ']'       ;


//block
//    : expression*
//    | EOF
//    ;
//
//expression
//    : packagedef
//    | namedef
//    | call
//    | NAME | LITERAL
//    //| 'import' NAME       <-- reserved function calls (handled the same as calls)
//    //| 'main'              <-- reserved function calls (handled the same as calls)
//    ;
//
//packagedef
//    : 'package' NAME ('{' (NAME ':' STRING)+ '}' | ';')
//    ;
//
//namedef
//    : NAME+ '=' expression+ ';'
//    ;
//
//call
//    : NAME expression+ ';'
//    ;
