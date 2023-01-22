/**
 * Standard Stack implementation via linked list.
 * Stores a floating point number as data.
 * See ../testing/StackDriver for usecases.
*/

#include<stdio.h>
#include<stdlib.h>

/**
 * Stack node implemented via linked list.
*/
typedef struct Stack{
    float ch;
    struct Stack* next;
}Stack;

Stack* createNode(float ch)
{
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    int i=-1;
    temp->ch = ch;
    temp->next = NULL;
    return temp;
}

/**
 * Pushes a node onto the stack.
 * @param top A Stack* pointer pointing to the top of the stack
 * @param ch number to be stored as data
 * @return new Stack* top pointer
*/
Stack* push(Stack* top, float ch)
{
    Stack* temp = createNode(ch);
    temp->next = top;
    top = temp;
    return top;
}

/**
 * Pops a node from the top of the stack.
 * 
 * Note: Data from the top of the stack, if required, should be accessed via top->ch before popping.
 * @param top A Stack* pointer pointing to the top of the stack
 * @return new Stack* top pointer after popping a node
*/
Stack* pop(Stack* top)
{
    Stack* temp = top;
    top = top->next;
    free(temp);
    return top;
}

/**
 * Checks if stack is empty or not.
 * @param top A Stack* pointer pointing to the top of the stack
 * @return 1 if empty, 0 otherwise.
*/
int isEmpty(Stack *top)
{
    return top==NULL?1:0;
}

/**
 * Prints the stack.
 * @param top A Stack* pointer pointing to the top of the stack
 * 
*/
void printStack(Stack *top)
{
    while(isEmpty(top)!=1)
    {
        printf("%f\n",top->ch);
        top = top->next;
    }
}