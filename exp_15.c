#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[50];
int top = -1;

void push(char ch) {
    stack[++top] = ch;
}

char pop() {
    return stack[top--];
}

int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return (ch == '^') ? 3 : 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char ch;
    
    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];
        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') postfix[j++] = pop();
            if (top != -1) pop();
        } else {
            while (top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }
    while (top != -1) postfix[j++] = pop();
    postfix[j] = '\0';
}

void generateTAC(char postfix[]) {
    char stack[50][20];
    int top = -1, temp = 1;
    char arg1[20], arg2[20], result[20];
    
    printf("\n===== THREE ADDRESS CODE =====\n");
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            stack[++top][0] = postfix[i];
            stack[top][1] = '\0';
        } else {
            strcpy(arg2, stack[top--]);
            strcpy(arg1, stack[top--]);
            sprintf(result, "t%d", temp++);
            printf("%s = %s %c %s\n", result, arg1, postfix[i], arg2);
            strcpy(stack[++top], result);
        }
    }
}

void generateQuadruple(char postfix[]) {
    char stack[50][20];
    int top = -1, temp = 1;
    char arg1[20], arg2[20], result[20];
    
    printf("\n===== QUADRUPLE =====\n%-5s %-10s %-10s %-10s %-10s\n--------------------------------------------------\n", 
           "No.", "Operator", "Arg1", "Arg2", "Result");
           
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            stack[++top][0] = postfix[i];
            stack[top][1] = '\0';
        } else {
            strcpy(arg2, stack[top--]);
            strcpy(arg1, stack[top--]);
            sprintf(result, "t%d", temp++);
            printf("%-5d %-10c %-10s %-10s %-10s\n", temp - 1, postfix[i], arg1, arg2, result);
            strcpy(stack[++top], result);
        }
    }
}

void generateTriple(char postfix[]) {
    char stack[50][20];
    int top = -1, count = 0;
    char arg1[20], arg2[20];
    
    printf("\n===== TRIPLE =====\n%-5s %-10s %-10s %-10s\n----------------------------------------\n", 
           "No.", "Operator", "Arg1", "Arg2");
           
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            stack[++top][0] = postfix[i];
            stack[top][1] = '\0';
        } else {
            strcpy(arg2, stack[top--]);
            strcpy(arg1, stack[top--]);
            printf("%-5d %-10c %-10s %-10s\n", count, postfix[i], arg1, arg2);
            sprintf(stack[++top], "(%d)", count++);
        }
    }
}

int main() {
    char infix[50], postfix[50];
    printf("Enter infix expression: ");
    scanf("%49s", infix);
    
    infixToPostfix(infix, postfix);
    printf("\nPostfix: %s\n", postfix);
    
    generateTAC(postfix);
    generateQuadruple(postfix);
    generateTriple(postfix);
    return 0;
}
