#include <unistd.h>
#include <wait.h>
#include <stdio.h>

short run_cmd(char **argv)
{
    pid_t pid = fork();
    switch(pid) {
    case -1:
	return -1;

    case 0:
	if(execvp(argv[0],argv) == -1)
	    printf("fshell : %s : command not found.\n",argv[0]);

    case 1:
	wait(NULL);
    }
    return 0;
}
