CFLAGS="-march=native -O2 -pipe"
linklib=-lreadline
CC=gcc ${linklib}
headers=builtin.h exec.h parsing.h fshell.h
sources=builtin.c exec.c parsing.c fshell.c
name=fshell
DEFAULT_MAKE=${CC} ${headers} ${sources} -o ${name}

all:
	${DEFAULT_MAKE}

.PHONY: clean install uninstall debug

clean:
	rm fshell

install:
	cp fshell /bin/
	chmod 755 /bin/fshell

uninstall:
	rm /bin/fshell

debug:
	${DEFAULT_MAKE} -g
