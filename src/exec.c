#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

#include "exec.h"

short exec_cmd_nomally(char **array)
{
    pid_t pid = fork();
    if(pid < 0) {
	return -1;
    } else if(pid == 0) {
	if(execvp(array[0],array) < 0)
	    fprintf(stderr, "fshell : %s : command not found.\n", array[0]);
	exit(0);
    } else wait(NULL);
    return 0;
}
