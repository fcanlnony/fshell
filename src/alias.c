#include <string.h>
#include <stdlib.h>

#include "alias.h"

void init_alias(alias_t *point)
{
    point->alias_name = (char*)malloc(sizeof(char));
    point->alias_command = (char*)malloc(sizeof(char));
    point->next = NULL;
}

inline short check_alias(char *string)
{
    if(!strncmp(string,"alias ",strlen("alias ")))
	return 0;
    else return -1;
}

char *getalias_command(char *name,alias_t *point)
{
    alias_t *current = point->next;
    while(current != NULL) {
	if(!strcmp(name,current->alias_name)) {
	    return current->alias_command;
	}
	current = current->next;
    }
    if(current == NULL) {
	return (char*)NULL;
    }
}

short upload_alias(char *name, char *string, alias_t *point)
{
    alias_t *current = point;
    alias_t *current2 = NULL;
    while(current != NULL) {
	if(!strcmp(name,current->alias_name)) {
	    current->alias_command = string;
	    return 0;
	}
	current2 = current;
	current = current->next;
    }
    alias_t *new = (struct alias*)malloc(sizeof(struct alias));
    init_alias(new);
    new->alias_name = name;
    new->alias_command = string;
    current2->next = new;
    current = current2->next;
    return 0;
}

short unalias_command(alias_t *point,char *name)
{
    alias_t *current = point->next;
    alias_t *current2 = current;
    while(current != NULL) {
	if(!strcmp(name,current->alias_name)) {
	    current2 = current->next;
	    current = current2;
	    return 0;
	}
	current2 = current;
	current = current->next;
    }
    return -1;
}
