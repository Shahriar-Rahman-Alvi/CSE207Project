#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Define a stack structure
typedef struct Stack {
    char data[100][20]; // Assuming each element of the stack can hold a string of up to 20 characters
    int top;
} Stack;

// Function to initialize the stack
void initialize(Stack *stack) {
    stack->top = -1;
}

// Function to push an element onto the stack
void push(Stack *stack, char *element) {
    strcpy(stack->data[++stack->top], element);
}

// Function to pop an element from the stack
char* pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '×' || c == '÷' || c == '^' || c == 's' || c == 'c' || c == 't' || c == 'l';
}

// Function to return the priority of an operator
int priority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 0;
        case '×':
        case '÷':
            return 1;
        case '^':
            return 2;
        case 's':
        case 'c':
        case 't':
        case 'l':
            return 3;
        default:
            return -1;
    }
}

// Function to convert infix expression to postfix
char** infixToPostfix(char *input) {
    static char postfix[100][20]; // Assuming the postfix expression can have a maximum of 100 elements
    Stack stack;
    initialize(&stack);
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
            while (strcmp(stack.data[stack.top], "(") != 0) {
                strcpy(postfix[k++], pop(&stack));
            }
            pop(&stack); // Pop "("
        } else if (isOperator(c)) {
            while (!isEmpty(&stack) && strcmp(stack.data[stack.top], "(") != 0 && priority(c) <= priority(stack.data[stack.top][0])) {
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

// Function to evaluate postfix expression
double evaluatePostfix(char **postfix, int length, int isDegree) {
    Stack stack;
    initialize(&stack);

    for (int i = 0; i < length; i++) {
        char *token = postfix[i];
        char buffer[20];

        if (isOperator(token[0])) {
            double op2 = atof(pop(&stack));
            double op1 = atof(pop(&stack));
            double result = 0;

            switch (token[0]) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '×':
                    result = op1 * op2;
                    break;
                case '÷':
                    if (op2 != 0) {
                        result = op1 / op2;
                    } else {
                        printf("Division by zero\n");
                        exit(1);
                    }
                    break;
                case '^':
                    result = pow(op1, op2);
                    break;
                case 's':
                case 'c':
                case 't':
                case 'l':
                    result = (token[0] == 's' || token[0] == 'c' || token[0] == 't') ? (isDegree ? tan(op1 * M_PI / 180.0) : tan(op1)) : (token[0] == 'l' ? log(op1) : log10(op1));
                    break;
            }

            sprintf(buffer, "%f", result);
            push(&stack, buffer);
        } else {
            push(&stack, token);
        }
    }

    return atof(pop(&stack));
}

// Function to convert infix expression to postfix and evaluate
double evaluation(char *infix, int isDegree) {
    char **postfix = infixToPostfix(infix);
    int length = 0;
    while (strcmp(postfix[length], "") != 0) {
        length++;
    }
    return evaluatePostfix(postfix, length, isDegree);
}

int main() {
    char infix[100];
    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    printf("Result: %f\n", evaluation(infix, 0)); // Change the second argument to 1 if trigonometric functions should be evaluated in degrees
    return 0;
}
