#ifndef ALIAS_H_
#define ALIAS_H_

#include <stdbool.h>
typedef struct alias {
    char *alias_name;
    char *alias_command;
    struct alias *next;
} alias_t;

extern alias_t* init_alias(char *name,char *command);
extern bool check_alias(char *command);
extern char *getalias_command(char *name,alias_t *point);
extern short upload_alias(char *name,char *command,alias_t *point);
extern short unalias_command(alias_t *point,char *name);

#endif /*ALIAS_H*/
