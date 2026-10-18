#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");
    if (!fp1 || !fp2) return 1;

    int ch, ch1, line = 1, si = 0, i, flag = 0;
    char lexeme[50];
    char keyword[18][50] = {
        "void", "int", "char", "float", "double", "if", "else", "for", 
        "while", "return", "break", "continue", "printf", "scanf", 
        "fopen", "fclose", "fgetc", "ungetc"
    };

    fprintf(fp2, "SLNO\tLEXEME\tLINE NO\n");

    while ((ch = fgetc(fp1)) != EOF) {
        if (ch == ' ' || ch == '\t') continue;
        if (ch == '\n') { line++; continue; }

        // 1. Single Character Tokens Optimization
        if (ch == ';') {
            fprintf(fp2, "\n%d\t%c\tsemi_colon\t%d", ++si, ch, line);
        } else if (ch == '(' || ch == '{' || ch == '[') {
            fprintf(fp2, "\n%d\t%c\topen_bracket\t%d", ++si, ch, line);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            fprintf(fp2, "\n%d\t%c\tclose_bracket\t%d", ++si, ch, line);
        } else if (strchr("+-*/%", ch)) {
            fprintf(fp2, "\n%d\t%c\tarithmetic_operator\t%d", ++si, ch, line);
        } else if (strchr("&,.#", ch)) {
            fprintf(fp2, "\n%d\t%c\tspecial_operator\t%d", ++si, ch, line);
        } 
        // 2. Relational Operators (<, >, !)
        else if (strchr("<>!", ch)) {
            lexeme[0] = ch;
            ch1 = fgetc(fp1);
            if (ch1 == '=') {
                lexeme[1] = ch1; lexeme[2] = '\0';
            } else {
                lexeme[1] = '\0'; ungetc(ch1, fp1);
            }
            fprintf(fp2, "\n%d\t%s\trelational_operator\t%d", ++si, lexeme, line);
        } 
        // 3. Assignment and Equality Operator (=, ==)
        else if (ch == '=') {
            ch1 = fgetc(fp1);
            if (ch1 == '=') {
                fprintf(fp2, "\n%d\t==\trelational_operator\t%d", ++si, line);
            } else {
                ungetc(ch1, fp1);
                fprintf(fp2, "\n%d\t=\tassignment_operator\t%d", ++si, line);
            }
        } 
        // 4. Numerical Constants
        else if (isdigit(ch)) {
            flag = i = 0;
            ch1 = ch;
            do {
                lexeme[i++] = ch1;
                if (ch1 == '.') flag = 1;
                ch1 = fgetc(fp1);
            } while (isdigit(ch1) || ch1 == '.');
            lexeme[i] = '\0';
            ungetc(ch1, fp1);
            fprintf(fp2, "\n%d\t%s\t%s\t%d", ++si, lexeme, flag ? "float_number" : "number", line);
        } 
        // 5. Identifiers and Keywords
        else if (isalpha(ch)) {
            i = 0; ch1 = ch;
            do {
                lexeme[i++] = ch1;
                ch1 = fgetc(fp1);
            } while (isalnum(ch1));
            lexeme[i] = '\0';
            ungetc(ch1, fp1);

            flag = 0;
            for (int j = 0; j < 18; j++) {
                if (strcmp(lexeme, keyword[j]) == 0) { flag = 1; break; }
            }
            fprintf(fp2, "\n%d\t%s\t%s\t%d", ++si, lexeme, flag ? "keyword" : "identifier", line);
        } else {
            fprintf(fp2, "error");
        }
    }

    fclose(fp1);
    fclose(fp2);
    printf("\nOutput file '%s' created successfully.\n", argv[2]);
    return 0;
}
