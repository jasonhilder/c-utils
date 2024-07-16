#include "vector.h"
#include <stdio.h>

int main() {
    #ifdef _DEBUG
    printf("Debug mode enabled.\n");
    #endif

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
    printf("size: %ld\n", int_vector->size);
    printf("capacity: %ld\n", int_vector->capacity);
    printf("\n---------------\n\n");

    int arr[] = {'1', '2', 3, 4, 5};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);

    vector_join(int_vector, arr, arr_len);

    for(int i = 0; i < int_vector->size; i++) {
        printf("element:\n");
        printf("%d\n", *(int *)vector_get(int_vector, i));
    }
    printf("size: %ld\n", int_vector->size);
    printf("capacity: %ld\n", int_vector->capacity);
    printf("\n---------------\n\n");

    val = 1000;
    vector_add(int_vector, &val);

    printf("size: %ld\n", int_vector->size);
    printf("capacity: %ld\n", int_vector->capacity);

    vector_free(int_vector);
    return 0;
}
