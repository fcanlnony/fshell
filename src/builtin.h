#ifndef BUILTIN_H_
#define BUILTIN_H_

extern short check_environment_command(char *string);
extern short check_pipe(char *string);
extern void cd_command(char *string,char *username);

#endif /*BUILTIN_H_*/
