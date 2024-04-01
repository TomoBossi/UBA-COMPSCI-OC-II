#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


vector_t* nuevo_vector(void) {
    vector_t *vector = malloc(sizeof(vector_t));
    vector->size = 0;
    vector->capacity = 2;
    vector->array = malloc(2 * sizeof(uint32_t));
    return vector;
}

uint64_t get_size(vector_t* vector) {
    return vector->size;
}

void push_back(vector_t* vector, uint32_t elemento) {
    if(vector->size == vector->capacity){
        uint32_t *new_array = realloc(vector->array, 2 * vector->capacity * sizeof(uint32_t));
        vector->array = new_array;
        vector->capacity *= 2;
    }
    uint32_t i = vector->size;
    vector->array[i] = elemento;
    vector->size += 1;
}

int son_iguales(vector_t* v1, vector_t* v2) {
    if (v1->size != v2->size) {
        return 0;
    }
    for (uint64_t i = 0; i < v1->size; i++) {
        if (v1->array[i] != v2->array[i]) {
            return 0;
        }
    }
    return 1;
}

uint32_t iesimo(vector_t* vector, size_t index) {
    if (index >= vector->size) {
        return 0;
    }
    return vector->array[index];
}

void copiar_iesimo(vector_t* vector, size_t index, uint32_t* out) {
    uint32_t value = iesimo(vector, index);
    *out = value;
}

// Dado un array de vectores, devuelve un puntero a aquel con mayor longitud.
vector_t* vector_mas_grande(vector_t** array_de_vectores, size_t longitud_del_array) {
    if (longitud_del_array == 0) {
        return 0; // NULL pointer
    }
    uint64_t max_size = array_de_vectores[0]->size;
    vector_t* max_vector = array_de_vectores[0];
    for (size_t i = 1; i < longitud_del_array; i++) {
        uint64_t size = array_de_vectores[i]->size;
        if (size > max_size) {
            max_size = size;
            max_vector = array_de_vectores[i];
        }
    }
    return max_vector;
}