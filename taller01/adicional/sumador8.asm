%define SYS_WRITE 1
%define SYS_EXIT 60

section	.data
msg db '000', 0xA         ; message placeholder
len equ $ - msg           ; message length

op1 db 211                ; operand 1
op2 db 152                ; operand 2

section	.text
	global _start

_start:
	movzx rbx, byte [op1]
	movzx rax, byte [op2]
	add al, bl            ; rax holds the result (al and bl are the lower bytes from rax and rbx)

	mov rbx, msg + 3      ; point after '000'
	mov rsi, 0xA          ; save 10 in rsi, to be used in dividing rax
	loop:
		dec rbx           ; move to next (more significant) digit
        mov rdx, 0        ; clear rdx for division
        div rsi           ; uint-divide rax by 10, saving quotient in rax and remainder in rdx
        add dl, 0x30      ; convert remainder to ASCII character (0x30 is ascii for '0', dl is the lower byte from rdx)
        mov [rbx], dl     ; store ASCII character
        cmp rax, 0        ; check if quotient is zero
        jnz loop          ; if not zero, continue conversion

	mov rax, SYS_WRITE    ; syscall 1
	mov rdx, len          ; message length 
	mov rdi, 1            ; print to stdin
	mov rsi, msg
	syscall

	mov rax, SYS_EXIT     ; syscall 60
	mov rdi, 0            ; exit code 0
	syscall
