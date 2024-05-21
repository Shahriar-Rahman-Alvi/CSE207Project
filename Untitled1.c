#include<stdio.h>
#include<stdlib.h>
typedef struct node {
    int data;char str;
    struct node* next;
}node;
node* enter(node *h, int num){
    if(num==2){
        printf("enter operator");}
    else if(num==1){
        printf("Enter Number");
    }

    char input[20];
    fgets(input, 20, stdin);
    node *tmp = malloc(100);

    if(atoi(input)!=0){
        tmp->data = atoi(input);
        tmp->next = NULL;
    }
    else{
        tmp->str = (char)input[0];
        node *nodeNode = enter(tmp, num-1);
        tmp->next = nodeNode;
    }
}
int main(){
    node *head = malloc(100);
    char input[20];
    printf("Enter first num");
    fgets(input, 20, stdin);
    head->data = atoi(input);
    node *nextNode  = enter(head, 2);
    head->next = nextNode;

    int first = head->data;
    int second = head->next->next->data;
    char op =head->next->str;

    if(op == '+'){
        printf("%i + %i = %i", first, second, first+second);

    }
    else if(op == '-'){
        printf("%i - %i = %i", first, second, first-second);
    }
    else if(op == '*'){
        printf("%i * %i = %i", first, second, first*second);
    }
    else if(op == '/'){
        printf("%i / %i = %i", first, second, first/second);
    }
    else{
        printf("Invalid operator or number");
    }
}
