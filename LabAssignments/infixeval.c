#include<stdio.h>
#include "../header_files/stack.h"
#include"../header_files/fileops.h"

int prec(char ch)                        //returns the precedence of the given operator
{
	int c=0;
    char pr[8]="|&-+%/*^";              //array storing operators in ascending orders of precedence
    if(ch=='('||ch==')')                //() have the highest precedence, but we need to push an operator if they are present, hence in this particular
                                        //program they have the lowest precedence
    return 0;
    else
    {
        for(int i=0;i<8;i++)
        {
            if(ch==pr[i])
            return i+1;                 //return the index of the character, which is their precedence value
        }
    }
}

void convertToPostfix(char *inexp, char *outexp)
{
    int i=0,tempCount=0,outCount=0;
    char temp[4], open[]={'(','\0'};
    Stack *top = NULL;
    while(inexp[i]!='\0')
    {
        if(inexp[i]>=48 && inexp[i]<=57)
        {
            //Make the number
            temp[tempCount] = inexp[i];
            tempCount++;
        }
        else
        {
            //Push any existing number into the output expression
            if(tempCount!=0)
            {
                temp[tempCount] = '\0';
                int j = 0;
                while(temp[j]!='\0')
                {
                    outexp[outCount] = temp[j];
                    j++; outCount++;
                }
                outexp[outCount] = '$';
                outCount++;
                tempCount = 0;
            }

            //Finally, check the type of the operator
            if(inexp[i]=='(')
            {
                //Push '(' onto the stack
                top = push(top,open);
            }
            else if(inexp[i]==')')
            {
                //Pop until '(' is encountered
                while(isEmpty(top)!=1 && top->arr[0]!='(')
                {
                    outexp[outCount] = top->arr[0];
                    outCount++;
                    top = pop(top);
                }
                top = pop(top);
            }
            else
            {
                char pushChar[]={inexp[i],'\0'};

                //Pop until the operator at top of the stack has a lower precedence than the current character
                while(isEmpty(top)!=-1 && prec(top->arr[0])>=prec(inexp[i]))
                {
                    outexp[outCount] = top->arr[0];
                    outCount++;
                    top = pop(top);
                }
                top = push(top,pushChar);
            }
        }
        i++;
    }
    outexp[outCount] = '\0';
}

int main()
{
    char inexp[] = {'(','5','+',')','\0'}, outexp[100];
    convertToPostfix(inexp, outexp);
    int i = 0;
    while(outexp[i]!='\0')
    {
        printf("%c",outexp[i]);
        i++;
    }
}