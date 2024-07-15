#include "vector.h"
#include <stdio.h>

int main() {
    vector_t* int_vector = vector_new(sizeof(int), 2);

    int val = 10;
    vector_add(int_vector, &val);
    val = 20;
    vector_add(int_vector, &val);
    val = 33;
    vector_add(int_vector, &val);

    for(int i = 0; i < int_vector->size; i++) {
        printf("element:\n");
        printf("%d\n", *(int *)vector_get(int_vector, i));
    }
    printf("capacity: %ld\n", int_vector->capacity);
    printf("capacity: %ld\n", int_vector->size);

    vector_free(int_vector);
    return 0;
}
