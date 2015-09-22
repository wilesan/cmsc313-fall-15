; File: toupper.asm last updated 09/26/2001
; Minor updates to comments 02/05/2015
;
; Convert user input to upper case.
;
; Assemble using NASM:  nasm -f elf -g -F stabs toupper.asm
; Link with ld:  ld -o toupper toupper.o -melf_i386
;

%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4
%define BUFLEN 256


        SECTION .data                   ; initialized data section

msg1:   db "Enter string: "             ; user prompt
len1:   equ $-msg1                      ; length of first message

msg2:   db "Original: "                 ; original string label
len2:   equ $-msg2                      ; length of second message

msg3:   db "Convert:  "                 ; converted string label
len3:   equ $-msg3

msg4:   db 10, "Read error", 10         ; error message
len4:   equ $-msg4

msg_invalid_esc:	db "Error unknown escape sequence: \ ",10
len_invalid_esc:	equ	$-msg_invalid_esc

msg_octal_overflow:	db "Error octal overflow: \   ", 10
len_octal_overflow: equ $-msg_octal_overflow

        SECTION .bss                    ; uninitialized data section
buf:    resb BUFLEN                     ; buffer for read
newstr: resb BUFLEN                     ; converted string
rlen:   resb 4                          ; length


        SECTION .text                   ; Code section.
        global  _start                  ; let loader see entry point

_start: nop                             ; Entry point.
start:                                  ; address for gdb

        ; prompt user for input
        ;
        mov     eax, SYSCALL_WRITE      ; write function
        mov     ebx, STDOUT             ; Arg1: file descriptor
        mov     ecx, msg1               ; Arg2: addr of message
        mov     edx, len1               ; Arg3: length of message
        int     080h                    ; ask kernel to write

        ; read user input
        ;
        mov     eax, SYSCALL_READ       ; read function
        mov     ebx, STDIN              ; Arg 1: file descriptor
        mov     ecx, buf                ; Arg 2: address of buffer
        mov     edx, BUFLEN             ; Arg 3: buffer length
        int     080h

        ; error check
        ;
        mov     [rlen], eax             ; save length of string read
        cmp     eax, 0                  ; check if any chars read
        jg      read_OK                 ; >0 chars read = OK
        mov     eax, SYSCALL_WRITE      ; ow print error mesg
        mov     ebx, STDOUT
        mov     ecx, msg4
        mov     edx, len4
        int     080h
        jmp     exit                    ; skip over rest
read_OK:


        ; Loop for upper case conversion
        ; assuming rlen > 0
        ;
L1_init:
        mov     ecx, [rlen]             ; initialize count
        mov     esi, 0                ; point to start of buffer
        mov     edi, 0             ; point to start of new string
        mov		ebx, 0

L1_top:
        mov     al, [buf + esi]               ; get a character
        cmp		al, '\'
        je		is_backslash


L1_cont:
        mov     [newstr + edi], al               ; store char in new string
        inc     esi                     ; update source pointer
        inc     edi                     ; update dest pointer
        cmp		esi, [rlen]
        jne     L1_top                  ; loop to top if more chars
		jmp		L1_end

is_backslash:
		inc		esi
		mov		bl, [buf + esi]
		cmp		bl, 'a'
		jne		not_alert
		mov		[newstr + edi], byte 7
		jmp		advance_and_loop

not_alert:
		cmp		bl, 'b'
		jne		not_backspace
		mov		[newstr + edi], byte 8
		jmp		advance_and_loop

not_backspace:
		cmp		bl, 't'
		jne		not_horiz_tab
		mov		[newstr + edi], byte 9
		jmp		advance_and_loop

not_horiz_tab:
		cmp		bl, 'n'
		jne		not_newline
		mov		[newstr + edi], byte 10
		jmp		advance_and_loop

not_newline:
		cmp		bl, 'v'
		jne		not_vert_tab
		mov		[newstr + edi], byte 11
		jmp		advance_and_loop

not_vert_tab:
		cmp		bl, 'f'
		jne		not_ff
		mov		[newstr + edi], byte 12
		jmp		advance_and_loop

not_ff:
		cmp		bl, 'r'
		jne		not_cr
		mov		[newstr + edi], byte 13
		jmp		advance_and_loop

not_cr:
		cmp		bl, '\'
		jne		not_backslash
		mov		[newstr + edi], byte 92
		jmp		advance_and_loop

not_backslash:
		mov		eax, 0
		mov		ecx, 0

octal_loop:
		cmp		bl, '0'
		jb		not_octal_digit
		cmp		bl, '7'
		ja		not_octal_digit
		sub		bl, '0'
		shl		eax, 3
		add		eax, ebx
		inc		ecx
		inc		esi
		mov		bl, [buf + esi]
		cmp		ecx, 3
		jne		octal_loop
		cmp		eax, 255
		jg		octal_out_of_range

not_octal_digit:
		cmp		ecx, 0
		je		invalid_esc_sequence
		mov		[newstr + edi], al
		inc		edi
		jmp		L1_top

invalid_esc_sequence:
		mov		[msg_invalid_esc+len_invalid_esc-2], bl
        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg_invalid_esc
        mov     edx, len_invalid_esc
        int     080h
        inc		esi
        mov		[newstr + edi], byte '\'
        inc		edi
        jmp		L1_top

octal_out_of_range:
		mov		al, [buf + esi - 3]
		mov		[msg_octal_overflow + len_octal_overflow - 4], al
		mov		al, [buf + esi - 2]
		mov		[msg_octal_overflow + len_octal_overflow - 3], al
		mov		al, [buf + esi - 1]
		mov		[msg_octal_overflow + len_octal_overflow - 2], al
        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg_octal_overflow
        mov     edx, len_octal_overflow
        int     080h
		jmp		L1_top

advance_and_loop:
		inc		esi
		inc		edi
		jmp		L1_top

L1_end:


        ; print out user input for feedback
        ;
        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg2
        mov     edx, len2
        int     080h

        mov     eax, SYSCALL_WRITE      ; write user input
        mov     ebx, STDOUT
        mov     ecx, buf
        mov     edx, [rlen]
        int     080h

        ; print out converted string
        ;
        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg3
        mov     edx, len3
        int     080h

        mov     eax, SYSCALL_WRITE      ; write out string
        mov     ebx, STDOUT
        mov     ecx, newstr
        mov     edx, [rlen]
        int     080h


        ; final exit
        ;
exit:   mov     eax, SYSCALL_EXIT       ; exit function
        mov     ebx, 0                  ; exit code, 0=normal
        int     080h                    ; ask kernel to take over
