################################################################
#
#
################################################################

CC=gcc
CFLAGS=-m32 -g
.PREFIXES= .c .o

ALL_TARGETS=main8

C_SOURCE=main8.c match_dyn.c 

C_OBJECTS=${C_SOURCE:.c=.o}

all: ${ALL_TARGETS}

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

main8: main8.o match_dyn.o
	${CC} ${CFLAGS} -o $@ main8.o match_dyn.o

clean:
	rm -f *.o ${ALL_TARGETS}

