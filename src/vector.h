#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H

#include <stddef.h>

typedef enum {
    VECTOR_OK,
    VECTOR_ALLOC_ERR,
    VECTOR_OUT_OF_BOUNDS_ERR,
    VECTOR_UNKNOWN_ERR
} vector_err_t;

typedef struct Vector {
    // pointer to the array of items
    void* data;
    // number of items currently in vector
    size_t size;
    // Total capacity of vector
    size_t capacity;
    // Size of each item in the vector
    size_t type_size;
    // Error information for debugging
    vector_err_t last_error;
} vector_t;

vector_t* vector_new(size_t items_size, size_t initial_capacity);
void* vector_get(vector_t* vec, size_t index);
void vector_add(vector_t* vec, void* element);
void vector_remove(vector_t* vec);
void vector_join(vector_t* vec, void* new_arr, size_t new_arr_len);
void vector_free(vector_t* vec);
void vector_get_error(vector_t* vec);

#endif /* VECTOR_LIB_H */

