#include<stdio.h>
#include<math.h>
#include<string.h>
#include "../header_files/stack.h"
#include"../header_files/fileops.h"

void getKeyword(char *word)
{
    int i;
    char *keywords[] = {"auto","break",	"case",	"char",	"const",	"continue",	"default",	"do",
"double",	"else",	"enum",	"extern",	"float",	"for",	"goto",	"if",
"int",	"long",	"register",	"return",	"short",	"signed",	"sizeof",	"static",
"struct",	"switch",	"typedef",	"union",	"unsigned",	"void",	"volatile",	"while", ""}, **n;
  n = keywords;
  while (*n != "") {
    if(strcmp(*n,word)==0)
    printf("\n%s",word);
    n++;
  }
}

void getOperators(char *word)
{
    char *delimeters[] =  {"+","/","-","*","%","++","--","=","+=","-=","/=","*=","%=","&=",
    "|=","^=",">>=","<<="}, **n;
  n = delimeters;
  while (*n != "") {
    if(strcmp(*n,word)==0)
    printf("\n%s",word);
    n++;
  }
}

int main()
{
    char *path="../testing/input.txt";
    char *out = NULL;
    int i,c=0;
    out = read(path);
    printf("%s",out);
    char tempwrd[10];
    for(i=0;i<strlen(out);i++)
    {
        if((out[i]>=48 && out[i]<=57 )|| (out[i]>=97 && out[i]<=122))
        {
            tempwrd[c] = out[i];
            c++;
        }
        
        else if(out[i]==' '||out[i]==';'||out[i]=='\n')
        {
            tempwrd[c] = '\0';
            getKeyword(tempwrd);
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
