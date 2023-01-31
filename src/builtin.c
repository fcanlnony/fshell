#include <string.h>

#include "builtin.h"

short check_builtin(char *string)
{
    if(!strncmp(string, "alias", strlen("alias")))
	return 1;
    else if(!strncmp(string, "unalias", strlen("unalias")))
	return 2;
    else if(!strncmp(string, "export", strlen("export")))
	return 3;
    else return -1;
}
