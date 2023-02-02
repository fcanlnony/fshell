#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alias.h"

void init_alias(alias_t *point)
{
    short i = 0;
    while(i < MAX_ALIAS_NUM) {
	point->alias_name[i] = NULL;
	point->alias_command[i] = NULL;
	i++;
    }
    point->alias_num = 0;
}

short check_alias(char *string)
{
    if(!strncmp(string,"alias",strlen("alias")))
	return 0;
    else return -1;
}

short upload_alias(char *name,char *string,alias_t *point)
{
    if(point->alias_num == MAX_ALIAS_NUM)
	return -1;
    point->alias_num += 1;
    point->alias_name[point->alias_num-1] = name;
    point->alias_command[point->alias_num-1] = string;
    return 0;
}

char *getalias_command(char *name,alias_t *point)
{
    short i = 0;
    while(point->alias_name[i] != NULL) {
	if(!strcmp(point->alias_name[i],name)) {
	    return point->alias_command[i];
	}
	i++;
    }
    return (char *)NULL;
}

short check_alias_command(char *name,alias_t *point)
{
    short i = 0,t = -1;
    while(point->alias_name[i] != NULL) {
	if(!strcmp(point->alias_name[i],name)) {
	    t = i;
	    return t;
	}
	i++;
    }
    return t;
}

void cover_alias_command(char *string,alias_t *point,short num)
{
    point->alias_command[num] = string;
}

