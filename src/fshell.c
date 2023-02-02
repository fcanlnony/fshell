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

char *array[] = {NULL},*arrayA[] = {NULL},*arrayB[] = {NULL};
static jmp_buf env;

static void siginthandler()
{
    longjmp(env, 1);
}

int main()
{
    struct passwd *pwd = getpwuid(getuid());
    char display_readline[13];
    sprintf(display_readline,"%s","fshell >>> ");
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
	char *input = readline(display_readline);
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
	    parsing_nomally(input,array);
	    exec_cmd_nomally(array);
	}
	write_history(history_file_path);
	free(input);
    }
}
