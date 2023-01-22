#include<stdio.h>
#include "../header_files/stack.h"

int main()
{
    float num1=2, num2=3, num3=4, num4=5;
    Stack *top = NULL;
    int i=-1;
    top = push(top,num1);
    top = push(top,num2);
    top = push(top,num3);
    top = push(top,num4);
    printStack(top);
    top = pop(top);
    top = pop(top);
    top = pop(top);
    printf("%d",isEmpty(top));
    top = pop(top);
    printf("%d",isEmpty(top));
}