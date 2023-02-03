#include <string.h>
#include <stdlib.h>

#include "builtin.h"

short check_environment_command(char *string)
{
    if(!strncmp(string,"export",strlen("export")))
	return 1;
    else if(!strcmp(string,"cleanenv"))
	return 2;
    else if(!strncmp(string,"showenv",strlen("showenv")))
	return 3;
    else if(!strncmp(string,"removeenv",strlen("removeenv")))
	return 4;
    else return -1;
}

short check_pipe(char *string)
{
    if(strchr(string,'|') != NULL)
	return 0;
    else return -1;
}
