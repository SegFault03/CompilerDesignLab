#include<stdio.h>
#include<stdlib.h>

char* read(const char path[100])
{
    FILE *fp;
    fp=fopen(path,"r");
    if(fp==NULL)
	{
		printf("File NOT FOUND!");
		return NULL;
	}
    fseek(fp, 0L, SEEK_END);
    long numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);  
 
    char *outexp = (char*)calloc(numbytes, sizeof(char));   
    if(outexp == NULL)
        return NULL;
 
    fread(outexp, sizeof(char), numbytes, fp);
    outexp[numbytes] = ')';
    outexp[numbytes+1] = '\0';
    fclose(fp);
    return outexp;
}