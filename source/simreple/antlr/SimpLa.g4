grammar SimpLa;

// $antlr-format columnLimit 100, minEmptyLines 1, maxEmptyLinesToKeep 1, useTab false
// $antlr-format reflowComments false, breakBeforeBraces false
// $antlr-format keepEmptyLinesAtTheStartOfBlocks false, allowShortRulesOnASingleLine false
// $antlr-format alignSemicolons hanging, alignColons hanging, alignTrailingComments true

statement
    : assignment
    ;

assignment
    : LET ID EQUAL expression
    ;

expression
    : sum
    | atom
    ;

sum
    : atom (PLUS atom)*
    ;

atom
    : literal
    | variableRef
    ;

literal
    : INTEGER
    ;

variableRef
    : ID
    ;

LET
    : 'let'
    ;

PLUS
    : '+'
    ;

EQUAL
    : '='
    ;

INTEGER
    : [0-9]+
    ;

ID
    : [a-zA-Z]+
    ;

WS
    : [ \n\r\t] -> skip
    ;
