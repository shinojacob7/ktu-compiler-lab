%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(char *s);
%}

%token NUMBER
%left '+'
%left '*'

%%

S : E           { printf("Result = %d\n", $1); }
  ;

E : E '+' T     { $$ = $1 + $3; }
  | T           { $$ = $1; }
  ;

T : T '*' F     { $$ = $1 * $3; }
  | F           { $$ = $1; }
  ;

F : NUMBER      { $$ = $1; }
  ;

%%

int yylex() {
    char ch;
    while ((ch = getchar()) == ' ' || ch == '\t');
    
    if (ch >= '0' && ch <= '9') {
        yylval = ch - '0';
        while ((ch = getchar()) >= '0' && ch <= '9') {
            yylval = yylval * 10 + ch - '0';
        }
        ungetc(ch, stdin);
        return NUMBER;
    }
    
    return (ch == '\n') ? 0 : ch;
}

int yyerror(char *s) {
    printf("Invalid expression\n");
    return 0;
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}
