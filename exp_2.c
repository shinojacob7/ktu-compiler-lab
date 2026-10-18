#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) return 1; // Basic safety check for arguments
    
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");
    int ch, ch1, ch2;

    if (!fp1 || !fp2) return 1; // Ensure files opened successfully

    while ((ch = fgetc(fp1)) != EOF) {
        switch (ch) {
            case ' ':
            case '\t':
            case '\n':
                break; // Skip whitespaces
                
            case '/':
                ch1 = fgetc(fp1);
                if (ch1 == '/') {
                    while ((ch = fgetc(fp1)) != '\n' && ch != EOF); // Skip single-line comment
                } else if (ch1 == '*') {
                    while ((ch1 = fgetc(fp1)) != EOF) { // Skip multi-line comment
                        if (ch1 == '*' && (ch2 = fgetc(fp1)) == '/') break;
                        if (ch1 == '*') ungetc(ch2, fp1);
                    }
                } else {
                    fputc('/', fp2);
                    if (ch1 != EOF) ungetc(ch1, fp1);
                }
                break;
                
            default:
                fputc(ch, fp2);
        }
    }

    fclose(fp1);
    fclose(fp2);
    printf("\nOutput file '%s' created successfully.\n", argv[2]);
    return 0;
}
