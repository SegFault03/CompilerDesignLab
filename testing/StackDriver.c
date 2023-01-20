#include<stdio.h>
#include "../header_files/stack.h"

int main()
{
    char arr[] = {'a','b','$'};
    char arr2[] = {'a','b','c','$'};
    char arr3[] = {'2','1','$'};
    char arr4[] = {'1','b','#','$'};
    Stack *top = NULL;
    int i=-1;
    top = push(top,arr);
    top = push(top,arr2);
    top = push(top,arr3);
    top = push(top,arr4);
    while(top->arr[++i]!='$' && i<5)
    printf("%c",arr[i]);
}