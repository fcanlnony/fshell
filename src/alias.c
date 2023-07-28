#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "alias.h"

alias_t* init_alias(char *name,char *command)
{
    alias_t* new = (struct alias*)malloc(sizeof(struct alias));
    new->alias_name = name;
    new->alias_command = command;
    new->next = NULL;
    return new;
}

inline bool check_alias(char *command)
{
    if(!strncmp(command,"alias ",strlen("alias ")))
	return true;
    else return false;
}

char *getalias_command(char *name,alias_t *point)
{
    alias_t *current = point->next;
    for(;current != NULL;current = current->next) {
	if(!strcmp(name,current->alias_name)) {
	    return current->alias_command;
	}
    }
    return (char*)NULL;
}

short upload_alias(char *name, char *command, alias_t *point)
{
    alias_t *current = point;
    alias_t *prev = NULL;
    for(;current != NULL;prev = current,current = current->next) {
	if(!strcmp(name,current->alias_name)) {
	    current->alias_command = command;
	    return 0;
	}
    }
    alias_t *new = init_alias(name, command);
    prev->next = new;
    current = prev->next;
    return 0;
}

short unalias_command(alias_t *point,char *name)
{
    alias_t *current = point->next;
    alias_t *prev = current;
    for(;current != NULL;prev = current,current = current->next) {
	if(!strcmp(name,current->alias_name)) {
	    prev = current->next;
	    current = prev;
	    return 0;
	}
    }
    return -1;
}
