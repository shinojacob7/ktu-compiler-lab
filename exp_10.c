%{
#include <stdio.h>
#include <stdlib.h>
float num1, num2, result;
int flag = 0;
%}

%%

[0-9]+ {
    if (flag == 0) {
        num1 = atoi(yytext);
    } else {
        num2 = atoi(yytext);
        switch (flag) {
            case 1: result = num1 + num2; break;
            case 2: result = num1 - num2; break;
            case 3: result = num1 * num2; break;
            case 4: result = num1 / num2; break;
        }
        num1 = result;
    }
}

"+"     { flag = 1; }
"-"     { flag = 2; }
"*"     { flag = 3; }
"/"     { flag = 4; }
[ \t]   ;
\n      { printf("Result = %.2f\n", result); }
.       { printf("Invalid character\n"); }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter expression: ");
    yylex();
    return 0;
}
