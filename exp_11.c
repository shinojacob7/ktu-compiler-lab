%{
#include <stdio.h>
int flag = 0;
%}

%%

"/*"    { flag = 1; }
"*/"    { flag = 0; }
"//"    { flag = 2; }

\n      { if (flag == 2) flag = 0; }
[ \t]+  { if (flag == 0) ; }
.       { if (flag == 0) fprintf(yyout, "%s", yytext); }

%%

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input.c output.c\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    if (!yyin || !yyout) {
        printf("File opening error\n");
        return 1;
    }
    
    yylex();
    fclose(yyin);
    fclose(yyout);
    return 0;
}

int yywrap() {
    return 1;
}
