#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H

#include <stddef.h>

typedef struct Vector {
    // pointer to the array of items
    void* data;
    // number of items currently in vector
    size_t size;
    // Total capacity of vector
    size_t capacity;
    // Size of each item in the vector
    size_t i_size; 
} vector_t;

vector_t* vector_new(size_t items_size, size_t initial_capacity);
void vector_add(vector_t* vec, void* element);
void* vector_get(vector_t* vec, size_t index);
void vector_free(vector_t* vec);

#endif /* VECTOR_LIB_H */

