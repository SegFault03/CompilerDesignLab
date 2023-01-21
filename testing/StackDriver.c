#include<stdio.h>
#include "../header_files/stack.h"

int main()
{
    char arr[] = {'a','b','\0'};
    char arr2[] = {'a','b','c','\0'};
    char arr3[] = {'2','1','\0'};
    char arr4[] = {'1','b','#','\0'};
    Stack *top = NULL;
    int i=-1;
    top = push(top,arr);
    top = push(top,arr2);
    top = push(top,arr3);
    top = push(top,arr4);
    printStack(top);
    top = pop(top);
    top = pop(top);
    top = pop(top);
    printf("%d",isEmpty(top));
    top = pop(top);
    printf("%d",isEmpty(top));
}