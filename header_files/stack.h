#include<stdio.h>
#include<stdlib.h>

typedef struct Stack{
    char arr[5];
    struct Stack* next;
}Stack;

Stack* createNode(char *arr)
{
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    int i=-1;
    while(arr[++i]!='$' && i<5)
    temp->arr[i] = arr[i];
    temp->arr[i]='$';
    temp->next = NULL;
    return temp;
}

Stack* push(Stack* top, char *arr)
{
    Stack* temp = createNode(arr);
    temp->next = top;
    top = temp;
    return top;
}

Stack* pop(Stack* top)
{
    Stack* temp = top;
    top = top->next;
    free(temp);
    return top;
}


int isEmpty(Stack *top)
{
    return top==NULL?1:0;
}

void printStack(Stack *top)
{
    while(isEmpty(top)!=1)
    {
        printf("%s\n",top->arr);
        top = top->next;
    }
}