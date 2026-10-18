#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Input file not specified.\nUsage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error: Cannot open file '%s'.\n", argv[1]);
        return 1;
    }

    char line[500], *p;
    int found = 0, forno = 0;

    printf("I am Shino Jacob C X\nRoll No: 53\nHere is my for loop syntax checking output.\n\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        p = line;
        while ((p = strstr(p, "for")) != NULL) {
            /* Make sure it is actually the word "for" */
            if ((p == line || !isalnum(*(p - 1))) && !isalnum(*(p + 3)) && *(p + 3) != '_') {
                int semicolon = 0, open = 0, close = 0, error = 0;
                found = 1;
                printf("For loop %d:\n", ++forno);
                
                p += 3; /* Move after "for" */
                while (isspace(*p)) p++;

                /* Check '(' */
                if (*p != '(') {
                    printf(" Error: '(' is missing after 'for'.\n\n");
                    p++;
                    continue;
                }

                open = 1;
                p++;

                /* Scan the for header */
                for (int i = 0; p[i] != '\0'; i++) {
                    if (p[i] == ';') semicolon++;
                    if (p[i] == '(') open++;
                    if (p[i] == ')') {
                        if (--open == 0) { close = 1; break; }
                    }
                }

                /* Check closing ')' */
                if (!close) {
                    printf(" Error: ')' is missing.\n");
                    error = 1;
                }
                /* Check semicolons */
                if (semicolon != 2) {
                    printf(" Error: Expected 2 semicolons inside 'for' brackets, found %d.\n", semicolon);
                    error = 1;
                }
                
                printf(error ? "\n" : " For loop syntax is OK.\n\n");
            }
            p += 3;
        }
    }
    
    fclose(fp);
    if (!found) printf("Error: 'for' loop is not present.\n");
    return 0;
}
