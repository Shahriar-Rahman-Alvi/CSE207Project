#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long intResult = 0;
double k = 0, result = 0;

// Stack node structure
struct StackNode {
    double data;
    struct StackNode* next;
};

// Stack structure
struct Stack {
    struct StackNode* top;
};

// Function to create a new node
struct StackNode* createNode(double data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// Function to push data onto the stack
void push(struct Stack* stack, double data) {
    struct StackNode* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop data from the stack
double pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    struct StackNode* temp = stack->top;
    double data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Function to clear the stack
void clearStack(struct Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

// Function to free the memory allocated for the stack
void freeStack(struct Stack* stack) {
    clearStack(stack);
    free(stack);
}

//double result = 0;
struct Stack* history;

int menu() {
    int input;
    printf("\n  1. Addition");
    printf("\n  2. Subtraction");
    printf("\n  3. Multiplication");
    printf("\n  4. Division");
    printf("\n  5. Undo");
    printf("\n  6. Exit");
    printf("\n  Enter your choice: ");
    scanf("%d", &input);
    return input;
}

void addition() {
     double a, b;
    if(k)
    {
        printf("\nEnter your 1st number : ");
        scanf("%lf", &a);
        result += a;
        printf("\nResult = %lf", result);
    }
    else
    {
        printf("\nEnter your numbers : ");
        scanf("%lf%lf", &a, &b);
        result = a + b;
        printf("\nResult = %lf", result);
    }
}

void subtraction()
{
     double a, b;
    if(k)
    {
        printf("\nEnter your 1st number : ");
        scanf("%lf", &a);
        result -= a;
        printf("\nResult = %lf", result);
    }
    else
    {
        printf("\nEnter your numbers : ");
        scanf("%lf%lf", &a, &b);
        result = a - b;
        printf("\nResult = %lf", result);
    }

}

void multiplication()
{
    double a, b;
    if(k)
    {
        printf("\nEnter your 1st number : ");
        scanf("%lf", &a);
        result *= a;
        printf("\nResult = %lf", result);
    }
    else
    {
        printf("\nEnter your numbers : ");
        scanf("%lf%lf", &a, &b);
        result = a * b;
        printf("\nResult = %lf",result);
    }

}

void division()
{
    double a, b;
    if(k)
    {
        printf("\nEnter a number: ");
        scanf("%lf", &a);
        if(a!=0)
        {
        result /= a;
        printf("\nResult = %lf", result);
        }
        else
        {
        printf("Math Error\n");
        }
    }
    else
    {
        printf("\nEnter two numbers: ");
        scanf("%lf%lf", &a, &b);
        if (b!=0)
        {
        result = a / b;
        printf("\nResult = %lf", result);
        }
        else
        {
        printf("Math Error\n");
        }
    }

}

void undo()
{
    if (!isEmpty(history)) {
        result = pop(history);
        printf("\nUndo operation performed. Result = %lf", result);
    } else {
        printf("\nNo more undo operations available");
    }
}

void main() {
    history = createStack();

    while (1) {
        switch (menu()) {
            case 1:
                addition();
                break;

            case 2:
                subtraction();
                break;

            case 3:
                multiplication();
                break;

            case 4:
                division();
                break;

            case 5:
                undo();
                break;

            case 6:
                printf("\nExiting...");
                freeStack(history);
                exit(0);
                break;

            default:
                printf("\nInvalid Choice !");
        }

        printf("\nPress any key to continue...");
        getchar(); // To clear the input buffer
        getchar(); // Wait for user input
    }
}
