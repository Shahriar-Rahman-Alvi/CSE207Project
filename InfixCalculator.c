#include<stdio.h>
#include<conio.h> // i **have to** use turbo c.
#define LEN 25

void push(int *stack  , int* top ,int item){
    printf(" pushing : %d ", item);
    stack[*top] = item;
    (*top)++;
}

int pop(int *stack , int* top){
    int temp;
    (*top)--;
    temp = stack[*top];
    printf(" popping : %d",temp); // this causing a dilemma while popping character operators.
    return temp;
}

void calc(int* numstack , int* numtop, int* opstack , int* optop){
    int num1,num2,ans;
    char sign;

    num1 = pop(numstack,numtop);
    num1 = pop(numstack,numtop);

    switch(pop(opstack,optop)){
        case '+' : ans = num1 + num2; sign = '+' ; break;
        case '-' : ans = num1 - num2; sign = '-' ; break;
        case '*' : ans = num1 * num2; sign = '*' ; break;
        case '/' : ans = num1 / num2; sign = '/' ; break;
    }
    printf("%d %c %d = %d \n",num1,sign,num2,ans);
    push(numstack,numtop,ans);
    while(getchar()!='\n'){} // cleanup stdin from any junk
}

int main(void){
    int optop = 0 , numtop = 0, i=0 , numstack[50] , opstack[30];
    char str[102], c;
    clrscr();

    // read and trim input evaluatioon string
    printf("enter string to be evaluated (100 chars max): ");
    fgets(str , 100 , stdin);
    while(str[i]!='\n'){ i++; }
    str[i] = '\0';
    printf("\nstring : %s \nLength : %d",str,i);

    i = 0;
    // evaluate
    while( (c=str[i]) !='\0'){
    printf("\n reading : %c ",str[i]);
    if(c=='('){ i++; continue; } // ignore open parens
    else if(c=='+'||c=='-'||c=='*'||c=='/') push(opstack,&optop,c);
    else if(c>=48 && c <=57) push(numstack,&numtop,(c-48));
    else if(c==')') calc(numstack , &numtop, opstack , &optop);
    else printf("\n%c is invalid..\n",c);
    i++;
    }
    printf("\nanswer is : %g",pop(numstack,&numtop));
    getch(); // again , *must use* turbo c
    return 0;
}