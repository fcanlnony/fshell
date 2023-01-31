#include <string.h>

#include "parsing.h"

void parsing_normally(char *string,char **argv)
{
    int i = 0;
    for(*argv++ = strtok(string," ");i <= 20;i++) {
	*argv++ = strtok(NULL," ");
    }
}
