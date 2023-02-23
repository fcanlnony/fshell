#ifndef LIST_H_
#define LIST_H_

#include "alias.h"

typedef struct {
    alias_t *alias;
} universal_t;

extern void list_command(char **argv,universal_t *point);

#endif /*LIST_H*/
