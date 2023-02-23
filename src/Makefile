CFLAGS="-march=native -O2 -pipe"
LINKLIB=-lreadline
CC=gcc -std=c17 ${LINKLIB}
HEADERS= builtin.c alias.h list.h exec.h parsing.h fshell.h
SOURCES= builtin.h alias.c list.c exec.c parsing.c fshell.c
NAME= fshell

all:
	${CC} ${HEADERS} ${SOURCES} -o ${NAME}

.PHONY: clean install uninstall debug

clean:
	rm fshell

install:
	cp fshell /bin/
	chmod 755 /bin/fshell

uninstall:
	rm /bin/fshell

debug:
	${CC} ${HEADERS} ${SOURCES} -o ${NAME} -g
