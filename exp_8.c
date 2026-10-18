#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, ip = 0;

void printStep(char action[]) {
    stack[top + 1] = '\0';
    printf("%-15s %-15s %-15s\n", stack, input + ip, action);
}

int reduce() {
    /* E -> i */
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        return 1;
    }
    /* Handle length 3 productions: E -> E+E, E -> E*E, E -> (E) */
    if (top >= 2) {
        char op = stack[top - 1];
        if ((stack[top] == 'E' && stack[top - 2] == 'E' && (op == '+' || op == '*')) ||
            (stack[top] == ')' && stack[top - 2] == '(' && stack[top - 1] == 'E')) {
            stack[top - 2] = 'E';
            top -= 2;
            return 1;
        }
    }
    return 0;
}

int main() {
    printf("Enter input string (end with $): ");
    scanf("%49s", input);

    printf("\n%-15s %-15s %-15s\n---------------------------------------------\n", "Stack", "Input", "Action");

    while (1) {
        /* Accept */
        if (input[ip] == '$' && top == 0 && stack[0] == 'E') {
            printStep("Accept");
            break;
        }
        /* Reduce */
        if (reduce()) {
            printStep("Reduce");
        } 
        /* Shift */
        else if (input[ip] != '\0' && input[ip] != '$') {
            if (top >= 48) {
                printf("Error: Stack overflow\n");
                break;
            }
            stack[++top] = input[ip++];
            printStep("Shift");
        } 
        /* Error */
        else {
            printStep("Error");
            break;
        }
    }
    return 0;
}
