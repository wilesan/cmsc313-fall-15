################################################################
#
#
################################################################

CC=gcc
AS=nasm
CFLAGS=-m32 -g
ASFLAGS=-f elf -g -F dwarf

.PREFIXES= .c .o

ALL_TARGETS=add_test_nostdlib

C_SOURCE=sorter.c

ASM_SOURCE=adder.asm

ASM_OBJECTS={ASM_SOURCE:.asm=.o}

C_OBJECTS=${C_SOURCE:.c=.o}

all: ${ALL_TARGETS}

%.o: %.c
	${CC} -fno-stack-protector -c ${CFLAGS} $< -o $@

%.o: %.asm
	${AS} ${ASFLAGS} $< -o $@

add_test_nostdlib: add_test.o adder.o
	${CC} ${CFLAGS} -nostdlib -o $@ add_test.o adder.o
	
clean:
	rm -f *.o ${ALL_TARGETS}

