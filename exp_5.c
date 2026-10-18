#include <stdio.h>
#include <string.h>

char terminal[10];
char prec[10][10];
char stack[50], input[50];
int top = -1, n;

/* Find index of a terminal */
int getindex(char c) {
    for (int i = 0; i < n; i++) {
        if (terminal[i] == c) return i;
    }
    return -1;
}

/* Push into stack */
void push(char c) {
    stack[++top] = c;
}

/* Get topmost terminal from stack */
char gettop() {
    for (int i = top; i >= 0; i--) {
        if (stack[i] != 'E') return stack[i];
    }
    return '$';
}

/* Display stack */
void printstack() {
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
}

/* Check whether handle is valid */
int validhandle(char *handle) {
    int len = strlen(handle);
    if (strcmp(handle, "i") == 0) return 1;
    if (len == 3 && handle[0] == 'E' && handle[2] == 'E') return 1;
    return 0;
}

int main() {
    int i, j, ip = 0, row, col, boundary, prevterm, k, len;
    char a, b, handle[20];

    printf("Enter no of terminals : ");
    scanf("%d", &n);
    printf("Enter the terminals : ");
    for (i = 0; i < n; i++) scanf(" %c", &terminal[i]);

    printf("\nEnter precedence relation\n\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%c and %c : ", terminal[i], terminal[j]);
            scanf(" %c", &prec[i][j]);
        }
    }

    printf("\nPrecedence Table\n\n    ");
    for (i = 0; i < n; i++) printf("%4c", terminal[i]);
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%4c", terminal[i]);
        for (j = 0; j < n; j++) printf("%4c", prec[i][j]);
        printf("\n");
    }

    printf("\nEnter input string (use i and end with $): ");
    scanf("%s", input);
    if (input[strlen(input) - 1] != '$') strcat(input, "$");

    top = -1;
    ip = 0;
    push('$');

    printf("\n%-15s %-15s %s\n", "Stack", "Input", "Action");
    printf("---------------------------------------------\n");

    while (1) {
        a = gettop();
        b = input[ip];

        /* Accept condition */
        if (top == 1 && stack[0] == '$' && stack[1] == 'E' && b == '$') {
            printstack();
            printf("\t\t%s\t\tAccept\n", input + ip);
            break;
        }

        row = getindex(a);
        col = getindex(b);

        /* Invalid symbols or relation error */
        if (row == -1 || col == -1 || prec[row][col] == '-') {
            printstack();
            printf("\t\t%s\t\tError\n\nInput string rejected.\n", input + ip);
            break;
        }

        /* SHIFT */
        if (prec[row][col] == '<' || prec[row][col] == '=') {
            printstack();
            printf("\t\t%s\t\tShift %c\n", input + ip, b);
            push(b);
            ip++;
        }
        /* REDUCE */
        else if (prec[row][col] == '>') {
            prevterm = boundary = -1;

            /* Find the nearest '<' precedence relation */
            for (j = top; j >= 0; j--) {
                if (stack[j] != 'E') {
                    if (prevterm != -1) {
                        row = getindex(stack[j]);
                        col = getindex(stack[prevterm]);
                        if (prec[row][col] == '<') {
                            boundary = j;
                            break;
                        }
                    }
                    prevterm = j;
                }
            }

            if (boundary == -1) {
                printf("Error: Invalid handle\n");
                break;
            }

            /* Copy handle */
            len = 0;
            for (k = boundary + 1; k <= top; k++) handle[len++] = stack[k];
            handle[len] = '\0';

            printstack();
            printf("\t\t%s\t\t", input + ip);

            if (!validhandle(handle)) {
                printf("Invalid handle %s\n\nInput string rejected.\n", handle);
                break;
            }
            printf("Reduce E -> %s\n", handle);

            /* Replace handle with E */
            top = boundary;
            push('E');
        } else {
            printf("Invalid precedence relation.\n");
            break;
        }
    }
    return 0;
}
