#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    int top;
    double items[MAX];
} Stack;

void push(Stack* stack, double value) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

double pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 's' || ch == 'c' || ch == 't' || ch == 'l';
}

double applyOperation(char operator, double a, double b) {
    switch (operator) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default:
            printf("Unknown operator: %c\n", operator);
            exit(1);
    }
}

void evaluate(Stack* stack, char operator) {
    double b = pop(stack);
    double a = pop(stack);
    push(stack, applyOperation(operator, a, b));
}

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

double evaluatePostfix(char* postfix) {
    Stack stack;
    stack.top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            double num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            i--;
            push(&stack, num);
        } else if (isOperator(postfix[i])) {
            evaluate(&stack, postfix[i]);
        }
    }
    return pop(&stack);
}

char** infixToPostfix(char *input) {
    static char postfix[MAX][20];
    Stack stack;
    stack.top = -1;
    int k = 0;

    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];
        char buffer[20];

        if (isdigit(c)) {
            int j = 0;
            while (isdigit(input[i]) || input[i] == '.') {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';
            strcpy(postfix[k++], buffer);
            i--;
        } else if (c == '(') {
            push(&stack, "(");
        } else if (c == ')') {
            while (strcmp(stack.items[stack.top], "(") != 0) {
                strcpy(postfix[k++], pop(&stack));
            }
            pop(&stack);
        } else if (isOperator(c)) {
            while (!isEmpty(&stack) && strcmp(stack.items[stack.top], "(") != 0 && precedence(c) <= precedence(stack.items[stack.top][0])) {
                strcpy(postfix[k++], pop(&stack));
            }
            sprintf(buffer, "%c", c);
            push(&stack, buffer);
        }
    }

    while (!isEmpty(&stack)) {
        strcpy(postfix[k++], pop(&stack));
    }

    return postfix;
}

double evaluation(char *infix) {
    char **postfix = infixToPostfix(infix);
    return evaluatePostfix(*postfix);
}

int main() {
    char infix[MAX];
    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    double result = evaluation(infix);
    printf("Result: %lf\n", result);
    return 0;
}
