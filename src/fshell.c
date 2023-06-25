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
#include "list.h"
#include "fshell.h"

char *array[] = {NULL},*arrayA[20] = {NULL},*arrayB[20] = {NULL};
static jmp_buf env;

static void siginthandler()
{
    longjmp(env, 1);
}

int main(int argc,char **argv)
{
    if(argc > 1) {
	if(argc == 2) {
	    if(!strcmp(argv[1],"--version") || !strcmp(argv[1],"-v"))
		printf("fshell %s\n",FSHELL_VERSION);
	    else if(!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h"))
		list();
	    else if(!strcmp(argv[1],"--compile-time") || !strcmp(argv[1],"-ct"))
		printf("Time:%s Date:%s\n",__TIME__,__DATE__);
	    else printf("Unknow option :%s \n",argv[1]);
	} else help();
	exit(0);
    }
    struct passwd *pwd = getpwuid(getuid());
    char history_file_path[154];
    if(!strcmp(pwd->pw_name,"root"))
	strncpy(history_file_path,"/root/.fshell_history",strlen("/root/.fshell_history"));
    else sprintf(history_file_path,"/home/%s/.fshell_history",pwd->pw_name);
    read_history(history_file_path);
    char path_display[100];
    alias_t aVariable;
    init_alias(&aVariable);
    universal_t uVariable;
    uVariable.alias = &aVariable;
    int len = 0;
    char display_readline[256];
    setjmp(env);
    while (1) {
	signal(SIGINT,siginthandler);
	getcwd(path_display,100);
	if(strcmp(pwd->pw_name,"root"))
	    sprintf(display_readline, "\033[1;32m%s\033[0m \033[1;32m[\033[0m %s \033[1;32m]\033[0m\n%s", pwd->pw_name,path_display,">>> ");
	else sprintf(display_readline, "\033[1;31m%s\033[0m \033[1;31m[\033[0m %s \033[1;31m]\033[0m\n%s", pwd->pw_name,path_display,">>> ");			 
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
	    if(tmp3 != NULL) {
		char *tmp4=malloc(sizeof(char)*strlen(tmp2)),*tmp5=malloc(sizeof(char)*strlen(tmp3));
		memset(tmp4,0x00,strlen(tmp4));
		memset(tmp5,0x00,strlen(tmp5));
		strcpy(tmp4,tmp2);
		strcpy(tmp5,tmp3);
		if(check_alias_command(tmp4, &aVariable) != -1)
		    cover_alias_command(tmp5, &aVariable,check_alias_command(tmp4, &aVariable));
		else upload_alias(tmp4, tmp5, &aVariable);
	    }
	} else if(check_environment_command(input) != -1) {
	    short num = check_environment_command(input);
	    if(num == 1) {
		char *tmp[2];
		tmp[0] = strtok(input, " ");
		tmp[1] = strtok(NULL,"");
		if(tmp[1] != NULL) {
		    char *tmp1 = malloc(sizeof(char)*strlen(tmp[1]));
		    strcpy(tmp1,tmp[1]);
		    putenv(tmp1);
		}
	    } else if(num == 2) {
		clearenv();
	    } else if(num == 3) {
		char tmp[len-strlen("showenv ")];
		strcpy(tmp,input+strlen("showenv "));
		if(getenv(tmp) != NULL)
		    puts(getenv(tmp));
		else printf("fshell : %s : Invalid environment variables\n",tmp);
	    } else if(num == 4) {
		char *tmp = malloc(sizeof(char)*(len-strlen("removeenv ")));
		memset(tmp,0x00,strlen(tmp));
		strcpy(tmp,input+strlen("removeenv "));
		unsetenv(tmp);
		free(tmp);
	    } else if(num == 5) {
		char *tmp = malloc(sizeof(char)*(len-strlen("unalias ")));
		memset(tmp,0x00,strlen(tmp));
		strcpy(tmp,input+strlen("unalias "));
		short num_unalias = check_alias_command(tmp, &aVariable);
		if(num_unalias != -1) {
		    unalias_command(&aVariable, num_unalias);
		}
		free(tmp);
	    } else if(num == 6) {
		char tmp[len-strlen("cd ")];
		strcpy(tmp,input+strlen("cd "));
		cd_command(tmp,pwd->pw_name);
	    } else if(num == 7) {
		parsing_nomally(input, array);
		if(array[1] != NULL)
		    list_command(array, &uVariable);
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
		parsing_pipe(input, arrayA, arrayB);
		exec_pipe(arrayA, arrayB);
		fflush(stdout);
	    } else {
		parsing_nomally(input,array);
		exec_cmd_nomally(array);
	    }
	}
	write_history(history_file_path);
	free(input);
    }
}
