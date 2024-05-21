#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    double items[MAX];
} Stack;

// Function prototypes
void push(Stack* stack, double value);
double pop(Stack* stack);
double peek(Stack* stack);
int isEmpty(Stack* stack);
void evaluate(Stack* stack, char operator);
double applyOperation(char operator, double a, double b);
int precedence(char operator);
int isOperator(char ch);
double evaluatePostfix(char* postfix);

int main() {
    char postfix[MAX];
    printf("Enter postfix expression: ");
    fgets(postfix, MAX, stdin);
    postfix[strcspn(postfix, "\n")] = 0;  // Remove newline character

    double result = evaluatePostfix(postfix);
    printf("Result: %lf\n", result);

    return 0;
}

void push(Stack* stack, double value) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

double pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

double peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->items[stack->top];
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void evaluate(Stack* stack, char operator) {
    double b = pop(stack);
    double a = pop(stack);
    push(stack, applyOperation(operator, a, b));
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

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
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
