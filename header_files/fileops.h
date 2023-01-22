/**
 * Reads the contents of a file.
 * See ../testing/FileOpsDriver.c for usecases.
*/

#include<stdio.h>
#include<stdlib.h>

/**
 * reads the conents of a given file.
 * 
 * Note: Adds a ')' at the end of file contents to help with postfix conversion.
 * @param path the filepath whose contents are to be read
 * @return NULL if filepath does not exist, character array containing file contents otherwise.
*/
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