#ifndef FSHELL_H_
#define FSHELL_H_

#define FSHELL_VERSION  "0.1.1-dev"
#include <stdio.h>

void list() {
    fprintf(stdout,"  --compile-time,-ct get compile time\n \
 --vesion,-v get version\n");   
}

#endif /*FSHELL_H_*/
