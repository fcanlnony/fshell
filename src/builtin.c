#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 

#include "builtin.h"

short check_environment_command(char *string)
{
    if(!strncmp(string,"setenv",strlen("setenv")))
	return 1;
    else if(!strcmp(string,"cleanenv"))
	return 2;
    else if(!strncmp(string,"showenv",strlen("showenv")))
	return 3;
    else if(!strncmp(string,"removeenv",strlen("removeenv")))
	return 4;
    else if(!strncmp(string,"unalias",strlen("unalias")))
	return 5;
    else if(!strncmp(string,"cd",strlen("cd")))
	return 6;
    else if(!strncmp(string,"list",strlen("list")))
	return 7;
    else return -1;
}

short check_pipe(char *string)
{
    if(strchr(string,'|') != NULL)
	return 0;
    else return -1;
}

void cd_command(char *string,char *username)
{
    if(strchr(string,'~') != NULL) {
	char tmp[strlen(string)-strlen("~")];
	strcpy(tmp,string+strlen("~"));
	if(strcmp(username,"root")) {
	    char tmp2[strlen("/home/")+strlen(username)+strlen(tmp)];
	    memset(tmp2,0x00,strlen(tmp2));
	    sprintf(tmp2, "/home/%s%s", username,tmp);
	    chdir(tmp2);
	} else {
	    char tmp2[strlen("/root")+strlen(tmp)];
	    memset(tmp2,0x00,strlen(tmp2));
	    sprintf(tmp2, "/root%s", tmp);
	    chdir(tmp2);
	}
    } else {
	chdir(string);
    }
}

void help()
{
    printf("Options:\n  --version,-v print version\n  --help,-h get some help\n");
}
