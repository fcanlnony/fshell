#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <wait.h>
#include <sys/types.h>
#include <signal.h>
#include <setjmp.h>
#include <pwd.h>

#include "parsing.h"
#include "exec.h"
#include "alias.h"
#include "builtin.h"

char *array[] = {NULL};
static jmp_buf env;

static void siginthandler()
{
    longjmp(env, 1);
}

int main()
{
    struct passwd *pwd = getpwuid(getuid());
    char history_file_path[154];
    if(!strcmp(pwd->pw_name,"root"))
	sprintf(history_file_path,"/home/%s/.fshell_history",pwd->pw_name);
    else strncpy(history_file_path,"/root/.fshell_history",strlen("/root/.fshell_history"));
    read_history(history_file_path);
    alias_t aVariable;
    init_alias(&aVariable);
    char *tmp4=malloc(sizeof(char)*1024),*tmp5=malloc(sizeof(char)*1024);
    int len = 0;
    setjmp(env);
    while (1) {
	signal(SIGINT,siginthandler);
	char *input = readline("fshell >>> ");
	if(strcmp(input,"exit") == 0)
	    exit(0);
	add_history(input);
	len = strlen(input);
	if(check_alias(input) == 0) {
	    char tmp1[len];
	    memset(tmp1,0x00,len);
	    memmove(tmp1, input+strlen("alias "), len);
	    char *tmp2 = strtok(tmp1,"=");
	    char *tmp3 = strtok(NULL,"");
	    strcpy(tmp4,tmp2);
	    strcpy(tmp5,tmp3);
	    if(check_alias_command(tmp4, &aVariable) != -1)
	    cover_alias_command(tmp5, &aVariable,check_alias_command(tmp4, &aVariable));
	    else upload_alias(tmp4, tmp5, &aVariable);
	} else if(check_environment_command(input) != -1) {
	    short num = check_environment_command(input);
	    if(num == 1) {
		char *tmp[2];
		tmp[0] = strtok(input, " ");
		tmp[1] = strtok(NULL,"");
		char *tmp2 = malloc(sizeof(char)*strlen(tmp[1]));
		strcpy(tmp2,tmp[1]);
		putenv(tmp2);
	    } else if(num == 2) {
		clearenv();
	    } else if(num == 3) {
		char tmp[len-strlen("showenv ")];
		memset(tmp,0x00,strlen(tmp));
		strcpy(tmp,input+strlen("showenv "));
		if(getenv(tmp) != NULL)
		    puts(getenv(tmp));
		else printf("fshell : %s : Invalid environment variables\n",tmp);
	    } else if(num == 4) {
		char *tmp = malloc(sizeof(char)*(len-strlen("removeenv ")));
		memset(tmp,0x00,strlen(tmp));
		strcpy(tmp,input+strlen("removeenv "));
		unsetenv(tmp);
	    }
	} else {
	    char tmp1[len];
	    memset(tmp1,0x00,len);
	    strcpy(tmp1,input);
	    char *tmp2 = strtok(tmp1," ");
	    if(check_alias_command(tmp2, &aVariable) != -1) {
		char *alias_char = getalias_command(tmp2, &aVariable);
		char tmp[len];
		memset(tmp,0x00,len);
		strcpy(tmp,input+strlen(tmp2));
		char tmp3[len-strlen(tmp2)+strlen(alias_char)];
		memset(tmp3,0x00,strlen(tmp3));
		strcpy(tmp3,alias_char);
		strcat(tmp3,tmp);
		strcpy(input,tmp3);
	    }
	    if (check_pipe(input) == 0) {
		char *arrayA[20] = {NULL},*arrayB[20] = {NULL};
		parsing_pipe(input, arrayA, arrayB);
		exec_pipe(arrayA, arrayB);
	    } else {
		parsing_nomally(input,array);
		exec_cmd_nomally(array);
	    }
	}
	write_history(history_file_path);
	free(input);
    }
}
