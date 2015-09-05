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

ASM_SOURCE=toupper.asm

ALL_TARGETS=toupper

ASM_OBJECTS=${ASM_SOURCE:.asm=.o}

all: ${ALL_TARGETS}

%.o: %.asm
	${AS} ${ASFLAGS} $< -o $@

${ALL_TARGETS}: ${ASM_OBJECTS}
	${LD} ${LDFLAGS} -o $@ $<

clean:
	rm -f *.o ${ALL_TARGETS}

