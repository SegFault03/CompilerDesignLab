#include<stdio.h>
#include<math.h>
#include<string.h>
#include "../header_files/stack.h"
#include"../header_files/fileops.h"

int getSpecialChars(char ch)
{
  char specialChars[7] = {';',',',':','(',')','{','}'};
  int n = 0;
  while(n<7)
  {
    if(ch==specialChars[n])
    {
      // printf("\nSpecial Char = %c",ch);
      return 1;
    }
    n++;
  }
  return 0;
}


int getKeyword(char *word)
{
    int i;
    char *keywords[] = {"auto","break",	"case",	"char",	"const",	"continue",	"default",	"do",
"double",	"else",	"enum",	"extern",	"float",	"for",	"goto",	"if",
"int",	"long",	"register",	"return",	"short",	"signed",	"sizeof",	"static",
"struct",	"switch",	"typedef",	"union",	"unsigned",	"void",	"volatile",	"while", ""}, **n;
  n = keywords;
  while (*n != "") {
    if(strcmp(*n,word)==0)
    {
      printf("\nKeyword -> %s",word);
      return 1;
    }
    n++;
  }
  return 0;
}

int getOperators(char *word)
{
    char *delimeters[] =  {"+","/","-","*","%","++","--","=","+=","-=","/=","*=","%=","&=",
    "|=","^=",">>=","<<="}, **n;
  n = delimeters;
  while (*n != "") {
    if(strcmp(*n,word)==0)
    {
      printf("\nOperator -> %s",word);
      return 1;
    }
    n++;
  }
  return 0;
}

int main()
{
    char *path="../testing/input.txt";
    char *out = NULL;
    int i,c=0;
    out = read(path);
    //printf("%s",out);
    char tempwrd[10];
    for(i=0;i<strlen(out);i++)
    {
        if(out[i]=='\n'||out[i]=='\'')
        continue;
        if((out[i]>=48 && out[i]<=57 )|| (out[i]>=97 && out[i]<=122) ||out[i]=='.')
        {
            tempwrd[c] = out[i];
            c++;
        }
        
        else if(getSpecialChars(out[i])==1||out[i]=='\n'||out[i]==' ')
        {
            tempwrd[c] = '\0';
            if(tempwrd[0]=='\000')
            continue;
            if(getKeyword(tempwrd)!=1 && (out[i]!=' '||out[i]!=';'||out[i]!='\n'))
            {
              printf("\nOperand -> %s",tempwrd);
              if(out[i]!=' ')
              printf("\nSpecial Char -> %c",out[i]);
            }
            c = 0;
        }
        else
        {
            char str[2] = "\0"; /* gives {\0, \0} */
            str[0] = out[i];
            getOperators(str);
        }
    }
}
