#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

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

short exec_pipe(char **arrayA,char **arrayB)
{
    pid_t p = fork();
    if(p == 0) {
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if(pid == 0) {
	    close(fd[1]);
	    dup2(fd[0],0);
	    if(execvp(arrayB[0],arrayB) < 0)
		fprintf(stderr, "fshell : %s : command not found.\n", arrayB[0]);
	    wait(NULL);
	} else if(pid > 0) {
	    close(fd[0]);
	    dup2(fd[1],1);
	    if(execvp(arrayA[0],arrayA) < 0)
	    fprintf(stderr, "fshell : %s : command not found.\n", arrayA[0]);
	    wait(NULL);
	}
    } else if(p > 0)
	wait(NULL);
    fflush(stdin);
    return 0;
}
