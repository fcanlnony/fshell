#ifndef ALIAS_H_
#define ALIAS_H_

#define MAX_ALIAS_NUM 50

typedef struct {
    char *alias_name[MAX_ALIAS_NUM];
    char *alias_command[MAX_ALIAS_NUM];
    int alias_num;
} alias_t;

extern void init_alias(alias_t *point);
extern short check_alias(char *string);
extern short upload_alias(char *name,char *string,alias_t *point);
extern char *getalias_command(char *name,alias_t *point);
extern short check_alias_command(char *name,alias_t *point);
extern void cover_alias_command(char *string,alias_t *point,short num);

#endif /*ALIAS_H*/
