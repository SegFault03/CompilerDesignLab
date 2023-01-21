#include<stdio.h>
#include "../header_files/fileops.h"

int main()
{
    char *path="input.txt";
    char *out = NULL;
    out = read(path);
    int i = -1;
    printf("%s",out);
}