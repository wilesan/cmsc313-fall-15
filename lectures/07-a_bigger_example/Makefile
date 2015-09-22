################################################################
#
# Makefile for toupper.asm
# Last Edited 9/4/2015
#
################################################################

AS=nasm
LD=ld
ASFLAGS=-f elf -g -F dwarf
LDFLAGS=-melf_i386
.PREFIXES= .o .asm

ASM_SOURCE=escape.asm escape-complete.asm

ALL_TARGETS=escape escape-complete

ASM_OBJECTS=${ASM_SOURCE:.asm=.o}

all: ${ALL_TARGETS}

%.o: %.asm
	${AS} ${ASFLAGS} $< -o $@

escape: escape.o
	${LD} ${LDFLAGS} -o $@ $<

escape-complete: escape-complete.o
	${LD} ${LDFLAGS} -o $@ $<

clean:
	rm -f *.o ${ALL_TARGETS}

