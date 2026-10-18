%{
#include <stdio.h>
#include <stdlib.h>
int line = 1;
int slno = 1;

void print_token(const char *token) {
    printf("%-8d %-15s %-20s %-8d\n", slno++, yytext, token, line);
}
%}

DIGIT   [0-9]
LETTER  [a-zA-Z]
ID      {LETTER}({LETTER}|{DIGIT})*
WS      [ \t]+

%%

"int"|"float"|"char"|"double"|"void"|"long"|"short" { print_token("KEYWORD"); }

{ID}       { print_token("IDENTIFIER"); }
{DIGIT}+   { print_token("NUMBER"); }

"="        { print_token("ASSIGNMENT_OP"); }
"+"        { print_token("PLUS_OP"); }
"-"        { print_token("MINUS_OP"); }
"*"        { print_token("MULTIPLY_OP"); }
"/"        { print_token("DIVIDE_OP"); }
","        { print_token("COMMA"); }
";"        { print_token("SEMICOLON"); }
"("        { print_token("LEFT_PAREN"); }
")"        { print_token("RIGHT_PAREN"); }
"{"        { print_token("LEFT_BRACE"); }
"}"        { print_token("RIGHT_BRACE"); }

{WS}       { /* Ignore spaces and tabs */ }
\n         { line++; }
.          { print_token("UNKNOWN"); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <C-file>\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }
    
    printf("%-8s %-15s %-20s %-8s\n--------------------------------------------------------------\n", 
           "Sl.No", "Lexeme", "Token", "Line No");
           
    yylex();
    fclose(yyin);
    return 0;
}
