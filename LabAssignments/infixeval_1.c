#include<stdio.h>
#include<math.h>
#include "../header_files/stack.h"
#include"../header_files/fileops.h"

/**
Returns precedence of an operator
@param ch operator whose precedence is to be found
@return precedence of the character
**/
int prec(char ch)                                    //returns the precedence of the given operator
{
	int c=0;
    char symboltable[5] = "-+*/^";
    int precedenceTable[] = {1,1,2,2,3};            //array storing operators in ascending orders of precedence
    if(ch=='('||ch==')')                            //lowest precedence as no operator needs to be pushed in case of brackets
    return 0;
    else
    {
        for(int i=0;i<5;i++)
        {
            if(ch==symboltable[i])
            return precedenceTable[i];             //return the index of the character, which is their precedence value
        }
    }
}

/**
 * Convert a legal infix expression into its postfix equivalent.
 * 
 * Notes: The resulting postfix expression may contain symbols such as '$' and '!', where
 * '$' indicates end of a number and '!' indicates the negative sign before a number.
 * @param inexp the infix expression as a character array
 * @param outexp an empty character array in which the resulting postfix expression is to be returned
 * 
*/
void convertToPostfix(char *inexp, char *outexp)
{
    int i=0,tempCount=0,outCount=0;
    char temp[4], open='(';
    Stack *top = NULL;
    top = push(top, (float)open);
    while(inexp[i]!='\0')
    {
        if((inexp[i]>=48 && inexp[i]<=57) || inexp[i]=='.' || (inexp[i]=='-' && tempCount==0 && inexp[i-1]!=')'))
        {
            //Make the number
            temp[tempCount] = inexp[i]=='-'?'!':inexp[i];
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
                top = push(top,(float)open);
            }
            else if(inexp[i]==')')
            {
                //Pop until '(' is encountered
                while(isEmpty(top)!=1 && (char)top->ch!='(')
                {
                    outexp[outCount] = (char)top->ch;
                    outCount++;
                    top = pop(top);
                }
                top = pop(top);
            }
            else
            {
                float pushChar = inexp[i];

                //Pop until the operator at top of the stack has a lower precedence than the current character
                while(isEmpty(top)!=-1 && prec((char)top->ch)>=prec(inexp[i]))
                {
                    outexp[outCount] = (char)top->ch;
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

/**
 * Makes a number from a character array. 
 * 
 * Array may have symbols such as '$' and '!'. See convertToPostfix() for meaning.
 * @param numchar the character array containing the number
 * @return floating point number
*/
float getNum(char *numchar)
{
    int j = numchar[0]=='!'?0:-1;
    float fact = 10, left = 0, isDec = 0, num=0;
    while(numchar[++j]!='$')
    {
        //Check for decimal point
        if(numchar[j]=='.')             
        {
            isDec = 1;
            left = num;
            num = 0;
            fact = 10;
            continue;
        }
        num = num*fact + (numchar[j]-'0');
        fact*=10;
    }

    //Add the right and left hand side of a decimal number.
    if(isDec==1)
    num = left+(num/fact);

    //Check if its a negative number
    return numchar[0]=='!'?num*(-1):num;
}

/**
 * Evaluates a given postfix expression.
 * @param inexp the character containing the postfix expression to be evaluated
 * @return floating point result of the postfix expression after evaluation
*/
float evaluatePostfix(char *inexp)
{
    int i=0, num=0, tempCount=0;
    char temp[5];
    Stack *top = NULL;
    while(inexp[i]!='\0')
    {
        if((inexp[i]>=48 && inexp[i]<=57) || inexp[i]=='!' || inexp[i]=='.')
        {
            //Make the number
            temp[tempCount] = inexp[i];
            tempCount++;
        }
        else if(inexp[i]=='$')
        {
            temp[tempCount] = '$';
            top = push(top,getNum(temp));
            tempCount = 0;
        }
        else
        {
            float num1 = top->ch;
            top = pop(top);
            float num2 = top->ch;
            top = pop(top);
            float result = 0;
            switch(inexp[i])
            {
                case '+':
                result = num1 + num2;
                break;

                case '-':
                result = num2 - num1;
                break;

                case '*':
                result = num1 * num2;
                break;

                case '/':
                result = num2 / num1;
                break;

                case '^':
                result = (float)pow(num1,num2);
                break;
            }

            top = push(top, result);
            tempCount = 0;
        }
        i++;
    }
    
    return top->ch;
}

/**
 * driver module
 * 
 * 'path' is the only variable that can/should be changed. 
 * 'path' should contain the filepath from which the expression is to be read.
*/
int main()
{
    char *path="..\\testing\\input.txt";
    char *inexp = read(path), outexp[100];
    convertToPostfix(inexp, outexp);
    int i = 0;
    printf("\nThe result is: %f",evaluatePostfix(outexp));
}