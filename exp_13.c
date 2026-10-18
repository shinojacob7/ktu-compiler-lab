%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int yylex();
int yyerror(char *);
%}

%union {
    double value;
}

%token <value> NUMBER
%left '+' '-'
%left '*' '/'
%right '^'
%right UMINUS
%type <value> E

%%

S : E '\n'          { printf("Result = %.2lf\n", $1); }
  ;

E : E '+' E         { $$ = $1 + $3; }
  | E '-' E         { $$ = $1 - $3; }
  | E '*' E         { $$ = $1 * $3; }
  | E '/' E         { 
                        if ($3 == 0) {
                            printf("Error: Division by zero\n");
                            YYABORT;
                        }
                        $$ = $1 / $3; 
                    }
  | E '^' E         { $$ = pow($1, $3); }
  | '(' E ')'       { $$ = $2; }
  | '-' E %prec UMINUS { $$ = -$2; }
  | NUMBER          { $$ = $1; }
  ;

%%

int yylex() {
    char ch;
    while ((ch = getchar()) == ' ' || ch == '\t');
    
    if ((ch >= '0' && ch <= '9') || ch == '.') {
        ungetc(ch, stdin);
        scanf("%lf", &yylval.value);
        return NUMBER;
    }
    return ch;
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
