#ifndef ALIAS_H_
#define ALIAS_H_

typedef struct alias {
    char *alias_name;
    char *alias_command;
    struct alias *next;
} alias_t;

extern void init_alias(alias_t *point);
extern short check_alias(char *string);
extern char *getalias_command(char *name,alias_t *point);
extern short upload_alias(char *name,char *string,alias_t *point);
extern short unalias_command(alias_t *point,char *name);

#endif /*ALIAS_H*/
