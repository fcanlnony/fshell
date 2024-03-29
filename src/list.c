#include <stdio.h>
#include <string.h>

#include "list.h"

static void list_alias(alias_t *point);
static void list_help();

void list_command(char **argv,universal_t *point)
{
    short num = sizeof(argv)/sizeof(argv[0]);
    if(num == 1) {
	if(!strcmp(argv[1],"alias"))
	    list_alias(point->alias);
	else if(!strcmp(argv[1],"help"))
	    list_help();
	else printf("'%s' unsupport to list\n",argv[1]);
    } else printf("'list option'\n");
}

void list_alias(alias_t *point)
{
    short i = 0;
    alias_t *current = point->next;
    while(current != NULL) {
	printf("%s => %s\n",current->alias_name,current->alias_command);
	current = current->next;
	i += 1;
    }
    printf("Total: %d\n",i);
}

void list_help()
{
    printf("You can use the list command to list the : alias,help\n");
}
