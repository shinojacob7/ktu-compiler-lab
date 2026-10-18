#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;

void push(char ch) {
    stack[++top] = ch;
}

char pop() {
    return stack[top--];
}

int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    return (ch == '*' || ch == '/') ? 2 : 0;
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

void generateAssembly(char postfix[], int start) {
    int address = start;
    char ch;
    
    printf("\nAddress\tInstruction\n----------------------\n");
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];
        if (isalnum(ch)) {
            printf("%d\tMOV A,%c\n", address++, ch);
            printf("%d\tPUSH A\n", address++);
        } else {
            printf("%d\tPOP B\n", address++);
            printf("%d\tPOP A\n", address++);
            
            if (ch == '+')      printf("%d\tADD B\n", address++);
            else if (ch == '-') printf("%d\tSUB B\n", address++);
            else if (ch == '*') printf("%d\tMUL B\n", address++);
            else if (ch == '/') printf("%d\tDIV B\n", address++);
            
            printf("%d\tPUSH A\n", address++);
        }
    }
    printf("%d\tPOP A\n", address++);
    printf("%d\tHLT\n", address++);
}

int main() {
    char infix[100], postfix[100];
    int start;
    
    printf("Enter infix expression: ");
    scanf("%99s", infix);
    printf("Enter starting address: ");
    scanf("%d", &start);
    
    infixToPostfix(infix, postfix);
    printf("\nPostfix expression: %s\n", postfix);
    
    generateAssembly(postfix, start);
    return 0;
}
