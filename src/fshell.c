#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <setjmp.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "fshell.h"
#include "parsing.h"
#include "exec.h"

int main()
{
    struct passwd *pwd = getpwuid(getuid());
    
    char READLINE_OUTPUT[ARRAY_SIZE+100+32];
    
    char username[32];
    strcpy(username,pwd->pw_name);
    
    char history_file_path[54];
    sprintf(history_file_path,"/home/%s/.fshell_history",username);
    
    while(1) {
	char *input = malloc(sizeof(char)*ARRAY_SIZE);
	read_history(history_file_path);
	char path[100];
	getcwd(path,sizeof(path));

	if(strcmp(username,"root"))
	    sprintf(READLINE_OUTPUT, "\033[;32;1m%s\033[0m \033[;32;1m[\033[0m %s \033[;32;1m]\033[0m\n%s", pwd->pw_name,path,">>> ");
	else sprintf(READLINE_OUTPUT, "\033[;31;1m%s\033[0m \033[;31;1m[\033[0m %s \033[;31;1m]\033[0m\n%s", pwd->pw_name,path,">>> ");
	input = readline(READLINE_OUTPUT);

	parsing_normally(input, array);
	run_cmd(array);
	add_history(input);
	write_history(history_file_path);
	free(input);
    }
}
