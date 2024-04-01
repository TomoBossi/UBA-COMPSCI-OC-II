#include "classify_chars.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void classify_chars_in_string(char* string, char** vowels_and_cons) {
    if (string == NULL) {
        return;
    }
    size_t c = 0;
    size_t v = 0;
    size_t i = 0;
    while (string[i] != '\0') {
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u') {
            vowels_and_cons[0][v] = string[i];
            v++;
        } else {
            vowels_and_cons[1][c] = string[i];
            c++;
        }
        i++;
    }
}

void classify_chars(classifier_t* array, uint64_t size_of_array) {
    for (uint64_t i = 0; i < size_of_array; i++) {
        classifier_t *current_classifier = &array[i];
        current_classifier->vowels_and_consonants = calloc(2, sizeof(char*));
        current_classifier->vowels_and_consonants[0] = calloc(64, sizeof(char));
        current_classifier->vowels_and_consonants[1] = calloc(64, sizeof(char));
        if (current_classifier->vowels_and_consonants == NULL || current_classifier->vowels_and_consonants[0] == NULL || current_classifier->vowels_and_consonants[1] == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        classify_chars_in_string(current_classifier->string, current_classifier->vowels_and_consonants);
    }   
}

////////////////////////////////////////////////////////////////////////////////

// Devolver el puntero al array de arrays

char** classify_chars_in_string_ret_pointer(char* string, char** vowels_and_cons) {
    if (string == NULL) {
        return vowels_and_cons;
    }
    size_t c = 0;
    size_t v = 0;
    size_t i = 0;
    while (string[i] != '\0') {
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u') {
            vowels_and_cons[0][v] = string[i];
            v++;
        } else {
            vowels_and_cons[1][c] = string[i];
            c++;
        }
        i++;
    }
    return vowels_and_cons;
}

// Devolver un struct que encapsule al array de arrays

typedef struct {
    char **array;
    size_t size;
} ArrayOfPointers;

ArrayOfPointers classify_chars_in_string_ret_struct(char* string, char** vowels_and_cons) {
    ArrayOfPointers result;
    result.size = 2;
    result.array = vowels_and_cons;

    if (string == NULL) {
        return result;
    }
    size_t c = 0;
    size_t v = 0;
    size_t i = 0;
    while (string[i] != '\0') {
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u') {
            vowels_and_cons[0][v] = string[i];
            v++;
        } else {
            vowels_and_cons[1][c] = string[i];
            c++;
        }
        i++;
    }
    return result;
}