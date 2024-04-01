%define SYS_EXIT 60

extern print_uint64

section	.data
op1 dq 200
op2 dq 128

section	.text
	global _start

_start:
	mov rdi, [op1]
    add rdi, [op2]
    call print_uint64

	mov rax, SYS_EXIT
	mov rdi, 0
	syscall
