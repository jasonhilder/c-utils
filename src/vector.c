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
        #ifdef _DEBUG
        fprintf(stderr, "Failed to allocate memory for vector.");
        #endif
        vec->last_error = VECTOR_ALLOC_ERR;
        return vec;
    }

    vec->data = malloc(initial_capacity * sizeof(items_size));
    if(vec->data == NULL) {
        #ifdef _DEBUG
        fprintf(stderr, "Failed to allocate memory for vector data.");
        #endif
        vec->last_error = VECTOR_ALLOC_ERR;
        return vec;
    }

    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->type_size = items_size;
    vec->last_error = VECTOR_OK;
    return vec;
}

// Add a single element to an array, reallocates if vec is at capacity.
void vector_add(vector_t* vec, void* element) {
    if(vec->size == vec->capacity) {

        vec->capacity *= 2;
        vec->data = realloc(vec->data, (vec->capacity * vec->type_size));

        if(vec->data == NULL) {
            #ifdef _DEBUG
            fprintf(stderr, "Failed to reallocate memory for vector data.");
            #endif

            vec->last_error = VECTOR_ALLOC_ERR;
            return;
        }
    }

    // Pointer to data moved to the end of the data (vec->size * vec->i_size),
    // element to add and then the amount to copy.
    memcpy((char *)vec->data + (vec->size * vec->type_size), element, vec->type_size );
    vec->size++;
}

// Add or "Join" array to the vector
void vector_join(vector_t* vec, void* new_arr, size_t new_arr_len) {
    // Check if there is enough space to just place the new arr in vec space
    size_t free_space = (vec->capacity - vec->size);
    if(new_arr_len > free_space) {
        vec->capacity = (vec->capacity + new_arr_len);
        vec->data = realloc(vec->data, (vec->capacity * vec->type_size));

        if(vec->data == NULL) {
            #ifdef _DEBUG
            fprintf(stderr, "Failed to reallocate memory for vector data.");
            #endif

            vec->last_error = VECTOR_ALLOC_ERR;
            return;
        }
    }
    
    memcpy((char *)vec->data + (vec->size * vec->type_size), new_arr, (new_arr_len * vec->type_size));
    vec->size = vec->size + new_arr_len;
}

void* vector_get(vector_t* vec, size_t index) {
    if (index >= vec->size) {
        vec->last_error = VECTOR_OUT_OF_BOUNDS_ERR;
        return NULL; // Out of bounds
    }

    return (char *)vec->data + index * vec->type_size;
}

vector_err_t vector_last_error(vector_t* vec) {
    if (vec == NULL) {
        // If the vector is NULL, return unknown error
        return VECTOR_UNKNOWN_ERR;
    }

    return vec->last_error;
}


void vector_get_error(vector_t* vec) {
    switch (vector_last_error(vec)) {
        case VECTOR_OK:
            printf("No error\n");
            break;
        case VECTOR_ALLOC_ERR: 
            printf("Memory allocation error \n");
            break;
        case VECTOR_OUT_OF_BOUNDS_ERR: 
            printf("Index out of bounds error.\n");
            break;
        case VECTOR_UNKNOWN_ERR:
            printf("Unknown error.\n");
            break;
    }
}

// Deinit the values and free the vector
void vector_free(vector_t* vec) {
    if(vec->data != NULL) {
        free(vec->data);
    }
    free(vec);
}

