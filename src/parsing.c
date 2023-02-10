#include <string.h>
#include <stdlib.h>

#include "parsing.h"

void parsing_nomally(char *string,char **array)
{
    array[0] = strtok(string," ");
    short i = 0;
    while(array[i] != NULL)
        array[++i] = strtok(NULL," ");
}

void parsing_pipe(char *string,char **arrayA,char **arrayB)
{
    char *tmp1 = strtok(string,"|");
    char *tmp2 = strtok(NULL,"");
    //memmove(tmp2,tmp2+strlen(" "),strlen(tmp2));
    short i = 1,k = 1;
    for(arrayA[0] = strtok(tmp1," ");i < 20;i++) {
	arrayA[i] = strtok(NULL," ");
    }
    for(arrayB[0] = strtok(tmp2," ");k < 20;k++) {
	arrayB[k] = strtok(NULL," ");
    }
}
