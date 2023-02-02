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
