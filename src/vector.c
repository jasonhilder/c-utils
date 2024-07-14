#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

// Turn a static array into a vector, return a pointer to the new vector instance
// The vector instance needs to be freed by the programmer, with vector_free(vector_t*);
vector_t* vector_new(size_t items_size, size_t initial_capacity) {
    vector_t* vec = (vector_t *)malloc(sizeof(vector_t));
    if(vec == NULL) {
        fprintf(stderr, "Failed to allocate memory for vector.");
        exit(EXIT_FAILURE);
    }

    vec->data = malloc(initial_capacity * sizeof(items_size));
    if(vec->data == NULL) {
        fprintf(stderr, "Failed to allocate memory for vector data.");
        exit(EXIT_FAILURE);
    }

    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->i_size = items_size;
    return vec;
}

void vector_add(vector_t* vec, void* element) {
    if(vec->size == vec->capacity) {

        vec->capacity *= 2;
        vec->data = realloc(vec->data, (vec->capacity * vec->i_size));

        if(vec->data == NULL) {
            fprintf(stderr, "Failed to reallocate memory for vector data.");
            exit(EXIT_FAILURE);
        }
    }

    // Pointer to data moved to the end of the data (vec->size * vec->i_size),
    // element to add and then the amount to copy.
    memcpy((char *)vec->data + (vec->size * vec->i_size), element, vec->i_size );
    vec->size++;
}

void* vector_get(vector_t* vec, size_t index) {
    if (index >= vec->size) {
        return NULL; // Out of bounds
    }

    return (char *)vec->data + index * vec->i_size;
}

// Deinit the values and free the vector
void vector_free(vector_t* vec) {
    if(vec->data != NULL) {
        free(vec->data);
    }
    free(vec);
}

