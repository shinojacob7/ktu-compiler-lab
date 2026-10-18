#include <stdio.h>
#define MAX 500

char stack[MAX];
int lineNo[MAX];
int top = -1;

void push(char ch, int line) {
    stack[++top] = ch;
    lineNo[top] = line;
}

char pop(int *line) {
    *line = lineNo[top];
    return stack[top--];
}

int empty() {
    return top == -1;
}

char openBracket(char ch) {
    return (ch == ')') ? '(' : (ch == '}') ? '{' : (ch == ']') ? '[' : ' ';
}

char closeBracket(char ch) {
    return (ch == '(') ? ')' : (ch == '{') ? '}' : (ch == '[') ? ']' : ' ';
}

int main(int argc, char *argv[]) {
    printf("I am Shino Jacob C X. Here is my paranthesis balance output.\n");
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("File cannot be opened\n");
        return 0;
    }

    char ch, x;
    int line = 1, oldLine, error = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') line++;
        
        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch, line);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (empty()) {
                printf("Left %c missing : Identified at line number %d\n", openBracket(ch), line);
                error = 1;
            } else {
                x = pop(&oldLine);
                if (closeBracket(x) != ch) {
                    printf("Parentheses mismatch between %c and %c : Identified at line number %d\n", x, ch, line);
                    error = 1;
                }
            }
        }
    }
    fclose(fp);

    while (!empty()) {
        x = pop(&oldLine);
        printf("Right %c missing : Identified at line number %d\n", closeBracket(x), oldLine);
        error = 1;
    }

    if (!error) printf("Parentheses are balanced\n");
    return 0;
}
