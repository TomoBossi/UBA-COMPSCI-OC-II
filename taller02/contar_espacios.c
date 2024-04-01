#include "contar_espacios.h"
#include <stdio.h>

uint32_t longitud_de_string(char* string) {
    if (string == NULL) {
        return 0;
    }
    uint32_t longitud = 0;
    uint32_t i = 0;
    while (string[i] != '\0') {
        longitud += 1;
        i += 1;
    }
    return longitud;
}

uint32_t contar_espacios(char* string) {
    if (string == NULL) {
        return 0;
    }
    uint32_t espacios = 0;
    uint32_t longitud = longitud_de_string(string);
    uint32_t i = 0;
    while (i < longitud) {
        if (string[i] == ' ') {
            espacios += 1;
        }
        i += 1;
    }
    return espacios;
}

// Pueden probar acá su código (recuerden comentarlo antes de ejecutar los tests!)
/*
int main() {

    printf("1. %d\n", contar_espacios("hola como andas?"));

    printf("2. %d\n", contar_espacios("holaaaa orga2"));
}
*/