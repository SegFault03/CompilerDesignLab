#include<stdio.h>
#include "../header_files/stack.h"
#include"../header_files/fileops.h"

int prec(char ch)                        //returns the precedence of the given operator
{
	int c=0;
    char symboltable[5] = "-+*/^";
    int precedenceTable[] = {1,1,2,2,3};     //array storing operators in ascending orders of precedence
    if(ch=='('||ch==')')                    //() have the highest precedence, but we need to push an operator if they are present, hence in this particular
                                        //program they have the lowest precedence
    return 0;
    else
    {
        for(int i=0;i<5;i++)
        {
            if(ch==symboltable[i])
            return precedenceTable[i];                 //return the index of the character, which is their precedence value
        }
    }
}

void convertToPostfix(char *inexp, char *outexp)
{
    int i=0,tempCount=0,outCount=0;
    char temp[4], open[]={'(','\0'};
    Stack *top = NULL;
    top = push(top, open);
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

int getNum(char *numchar)
{
    int j = -1, num = 0;
    while(numchar[++j]!='$')
    num = num*10 + (numchar[j]-'0');
    return num;
}

int evaluatePostfix(char *inexp)
{
    int i=0, num=0, tempCount=0;
    char temp[5];
    Stack *top = NULL;
    while(inexp[i]!='\0')
    {
        if(inexp[i]>=48 && inexp[i]<=57)
        {
            //Make the number
            temp[tempCount] = inexp[i];
            tempCount++;
        }
        else if(inexp[i]=='$')
        {
            temp[tempCount] = '$';
            top = push(top,temp);
            tempCount = 0;
        }
        else
        {
            int num1 = getNum(top->arr);
            top = pop(top);
            int num2 = getNum(top->arr);
            top = pop(top);
            int result = 0;
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
                result = num1 ^ num2;
                break;
            }
            
            int fact = 10, count=1;
            while(result/fact>0)
            {
                fact*=10; 
                count++;
            }

            tempCount = count;
            temp[tempCount--] ='$';
            while(result>0)
            {
                temp[tempCount] = (result%10)+'0';
                tempCount--;
                result/=10;
            }

            top = push(top, temp);
            tempCount = 0;
        }
        i++;
    }
    
    return getNum(top->arr);
}

int main()
{
    char *path="..\\testing\\input.txt";
    char *inexp = read(path), outexp[100];
    convertToPostfix(inexp, outexp);
    int i = 0;
    // while(outexp[i]!='\0')
    // {
    //     printf("%c",outexp[i]);
    //     i++;
    // }
    printf("\nThe result is: %d",evaluatePostfix(outexp));
}