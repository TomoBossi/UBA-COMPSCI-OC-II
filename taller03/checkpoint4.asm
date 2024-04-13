SYSCALL_WRITE EQU 1
NULL_CHAR EQU 0
SIZEOF_CHAR EQU 1

extern malloc
extern free
extern fprintf

extern fputs ;agregados para prueba en strPrint
extern fileno

section .data
msg_if_null db "NULL", 0xa

section .text

global strCmp
global strClone
global strDelete
global strPrint
global strLen

;int32_t strCmp(char* a, char* b)
;registros: a[rdi], b[rsi]
strCmp:
    xor rax, rax

    loop_cmp:
        cmp byte [rdi], NULL_CHAR
        jz a_null
        cmp byte [rsi], NULL_CHAR ;b terminó, a no
        jz a_gt_b
        ;jmp loop_cmp_not_null ;a no terminó, b tampoco

    loop_cmp_not_null:
        mov dl, byte [rsi] ;dl son los 8 bits más bajos de rdx
        cmp byte [rdi], dl ;no hay cmp m8, m8... sí hay cmp m8, r8
        jne cmp_diff
        inc rdi
        inc rsi
        jmp loop_cmp
    
    cmp_diff:
        ja a_gt_b
        jb b_gt_a

    a_null:
        cmp byte [rsi], NULL_CHAR ;a terminó, b también
        jz exit_cmp
        ;jmp b_gt_a ;a terminó, b no

    b_gt_a:
        mov rax, 1
        jmp exit_cmp

    a_gt_b:
        mov rax, -1
        ;jmp exit_cmp

    exit_cmp:
	    ret

;char* strClone(char* a)
;registros: a[rdi]
strClone:
	push rbp
	mov rbp, rsp

    push rdi
    call strLen ;rax tiene la longitud del string
    add rax, 1 ;rax tiene la longitud del string (incluyendo \0)
    mov r8, SIZEOF_CHAR
    mul r8; rax=rax*r8, rax contiene el tamaño total que hay que pedir a malloc
    mov rdi, rax ;rdi contiene el tamaño total que hay que pedir a malloc
    call malloc ;rax tiene al puntero a la memoria "vacía" ... estrictamente se debería agregar un chequeo de que malloc no haya fallado
    pop rdi
    mov rsi, rax
    push rax
    call strCpy
    pop rax

    pop rbp
    ret

;void strCpy(char* a, char* b) (copia el string a en la posición de memoria valida (allocada) b)
;registros: a[rdi], b[rsi]
strCpy:
    loop_cpy:
        mov al, [rdi] ;no hay mov m8, m8, si hay mov m8, r8
        mov [rsi], al
        cmp al, NULL_CHAR
        jz exit_cpy
        inc rdi
        inc rsi
        jmp loop_cpy

    exit_cpy:
	    ret

;void strDelete(char* a)
;registros: a[rdi]
strDelete:
	push rbp
	mov rbp, rsp

    call free

    pop rbp
	ret

;void strPrint(char* a, FILE* pFile)
;registros: a[rdi], pFile[rsi]
strPrint:
	push rbp
	mov rbp, rsp

    push rdi
    call strLen
    pop rdi ;no push, pop rsi porque conocemos la implmenetación de strLen ... probablemente una mala práctica

    ;### syscall SIN USAR NINGÚN CALL para obtener el file descriptor a partir de pFile
    mov rdx, rax ;longitud en rdx
    xchg rsi, rdi ;string pointer in rsi, stream pointer in rdi
    mov rdi, [rdi+0x70] ;el file descriptor está offseteado por +0x70 en el file struct ... EN MI COMPU ? EN ESTE STRUCT PARTICULAR ¿¿¿???
    cmp rdx, 0
    jnz print
    mov rsi, msg_if_null ;"NULL\n"
    mov rdx, 5
    print:
        mov rax, SYSCALL_WRITE ;syscall code en rax
        syscall

    ;### por su signatura, fprintf requiere intercambiar rsi, rdi ... también requiere prologo y epilogo
    ; xchg rsi, rdi
    ; cmp rax, 0
    ; jnz print
    ; mov rsi, msg_if_null
    ; print:
    ;     call fprintf

    ;### syscall usando fileno para obtener el file descriptor a partir de pFile
    ; mov rdx, rax
    ; xchg rsi, rdi
    ; call fileno
    ; mov rdi, rax
    ; cmp rdx, 0
    ; jnz print
    ; mov rsi, msg_if_null
    ; mov rdx, 5
    ; print:
    ;    mov rax, SYSCALL_WRITE
    ;    syscall

    ;### fputs también funciona, y por su signatura no requiere intercambiar rsi, rdi ... tampoco requiere prologo y epilogo
    ; cmp rax, 0
    ; jnz print
    ; mov rdi, msg_if_null
    ; print:
    ;     call fputs

    pop rbp
	ret

;uint32_t strLen(char* a)
;registros: a[rdi]
strLen:
    xor rax, rax

    loop_len:
        cmp byte [rdi], NULL_CHAR
        jz exit_len
        inc rdi
        inc rax
        jmp loop_len

    exit_len:
	    ret
