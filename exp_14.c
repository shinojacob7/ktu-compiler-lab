%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int yylex();
int yyerror(char *s);
%}

%token LETTER DIGIT

%%

L : S '\n'      { printf("Valid Identifier\n"); return 0; }
  ;

S : LETTER A
  | LETTER
  ;

A : LETTER A
  | DIGIT A
  | LETTER
  | DIGIT
  ;

%%

int yylex() {
    char c = getchar();
    if (isalpha(c)) return LETTER;
    if (isdigit(c)) return DIGIT;
    return c;
}

int yyerror(char *s) {
    printf("Invalid Identifier\n");
    return 0;
}

int main() {
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}
