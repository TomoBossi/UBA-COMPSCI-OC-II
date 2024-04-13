;Unpacked:
;   NODO_LENGTH = 32
;   LONGITUD_OFFSET = 24
;
;   [N][N][N][N][N][N][N][N]
;   [C][ ][ ][ ][ ][ ][ ][ ]
;   [A][A][A][A][A][A][A][A]
;   [L][L][L][L][ ][ ][ ][ ]
;
;   El struct está alineado a 8 bytes (su atributo más grande es de 8 bytes)

;Packed:
;   PACKED_NODO_LENGTH = 21: 8 + 1 + 8 + 4
;   PACKED_LONGITUD_OFFSET = 17: 8 + 1 + 8
;
;   [N][N][N][N][N][N][N][N]
;   [C][A][A][A][A][A][A][A]
;   [A][L][L][L][L]

NODO_LENGTH EQU 32
LONGITUD_OFFSET EQU 24

PACKED_NODO_LENGTH EQU 21
PACKED_LONGITUD_OFFSET EQU 17

;########### SECCION DE DATOS
section .data

;########### SECCION DE TEXTO (PROGRAMA)
section .text

;########### LISTA DE FUNCIONES EXPORTADAS
global cantidad_total_de_elementos
global cantidad_total_de_elementos_packed

;########### DEFINICION DE FUNCIONES
;extern uint32_t cantidad_total_de_elementos(lista_t* lista);
;registros: lista[rdi]
cantidad_total_de_elementos:
    xor eax, eax
    cmp rdi, 0 ;chequear que el input no sea NULL
    jz exit
    mov rdi, [rdi] ;en [rdi] está el puntero al primer nodo! 
    loop:
        cmp rdi, 0
        jz exit
        add eax, [rdi+LONGITUD_OFFSET]
        mov rdi, [rdi]
        jmp loop
    exit:
	    ret

;extern uint32_t cantidad_total_de_elementos_packed(packed_lista_t* lista);
;registros: lista[rdi]
cantidad_total_de_elementos_packed:
    xor eax, eax
    cmp rdi, 0
    jz exit
    mov rdi, [rdi]
    loop_packed:
        cmp rdi, 0
        jz exit_packed
        add eax, [rdi+PACKED_LONGITUD_OFFSET]
        mov rdi, [rdi]
        jmp loop_packed
    exit_packed:
	    ret
