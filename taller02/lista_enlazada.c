#include "lista_enlazada.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h> // longitud


lista_t* nueva_lista(void) {
    lista_t *lista = malloc(sizeof(lista_t));
    lista->head = NULL;
    return lista;
}

uint32_t longitud(lista_t* lista) {
    nodo_t *actual = lista->head;
    uint32_t len = 0;
    while (actual != NULL) {
        actual = actual->next;
        len += 1;
    }
    return len;
}

void agregar_al_final(lista_t* lista, uint32_t* arreglo, uint64_t longitud) {
    nodo_t *actual = lista->head;
    nodo_t *nodo = malloc(sizeof(nodo_t)); // 24
    nodo->next = NULL;
    nodo->arreglo = malloc(longitud * sizeof(uint32_t));
    nodo->longitud = longitud;
    for (uint64_t i = 0; i < longitud; i++) {
        nodo->arreglo[i] = arreglo[i];
    }

    if (actual == NULL) {
        lista->head = nodo;
    } else {
        while (actual->next != NULL) {
            actual = actual->next;
        }
        actual->next = nodo;
    }
}

nodo_t* iesimo(lista_t* lista, uint32_t i) {
    nodo_t *actual = lista->head;
    uint32_t j = 0;
    while (j < i) {
        actual = actual->next;
        j += 1;
    }
    return actual;
}

uint64_t cantidad_total_de_elementos(lista_t* lista) {
    nodo_t *actual = lista->head;
    uint64_t cantidad_total = 0;
    while (actual != NULL) {
        cantidad_total += actual->longitud;
        actual = actual->next;
    }
    return cantidad_total;
}

void imprimir_lista(lista_t* lista) {
    nodo_t *actual = lista->head;
    while (actual != NULL) {
        uint64_t longitud = actual->longitud;
        printf("%s", "| ");
        printf("%" PRIu64, longitud);
        printf("%s", " | -> ");
        actual = actual->next;
    }
    printf("%s", "null");
}

// Función auxiliar para lista_contiene_elemento
int array_contiene_elemento(uint32_t* array, uint64_t size_of_array, uint32_t elemento_a_buscar) {
    int contiene = 0;
    for (uint64_t i = 0; i < size_of_array; i++) {
        if (array[i] == elemento_a_buscar) {
            contiene = 1;
        }
    }
    return contiene;
}

int lista_contiene_elemento(lista_t* lista, uint32_t elemento_a_buscar) {
    nodo_t *actual = lista->head;
    int contiene = 0;
    while (actual != NULL) {
        uint64_t longitud = actual->longitud;
        if (contiene == 0) {
            contiene = array_contiene_elemento(actual->arreglo, longitud, elemento_a_buscar);
        }
        actual = actual->next;
    }
    return contiene;
}

// Devuelve la memoria otorgada para construir la lista indicada por el primer argumento.
// Tener en cuenta que ademas, se debe liberar la memoria correspondiente a cada array de cada elemento de la lista.
void destruir_lista(lista_t* lista) {
    nodo_t *actual = lista->head;
    nodo_t *tmp;
    while (actual->next != NULL) {
        tmp = actual->next;
        free(actual->arreglo);
        free(actual);
        actual = tmp;
    }
    free(actual->arreglo);
    free(actual);
    free(lista);
}