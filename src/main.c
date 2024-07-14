#include "vector.h"
#include <stdio.h>

int main() {
    vector_t* int_vector = vector_new(sizeof(int), 10);

    int val = 10;
    vector_add(int_vector, &val);

    for(int i = 0; i < int_vector->size; i++) {
        printf("element:\n");
        printf("%d\n", *(int *)vector_get(int_vector, i));
    }

    vector_free(int_vector);
    return 0;
}
