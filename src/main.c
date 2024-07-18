#include "vector.h"
#include "string_h.h"
#include <stdio.h>
#include <string.h>

int main() {
    #ifdef _DEBUG
    printf("Debug mode enabled.\n");
    #endif

    // ===============================================
    // Vector examples
    // ===============================================

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

    // ===============================================
    // String examples
    // ===============================================

    string_t *sh = string_new("Hello");

    print_string(sh);
    printf("String len: %d\n", (int)strlen(sh->value));
    printf("Allocation len: %d\n", sh->allocated_size);
    // ===============================================

    string_add(sh, " World!", false);
    print_string(sh);
    printf("String len: %d\n", (int)strlen(sh->value));
    printf("Allocation len: %d\n", sh->allocated_size);
    // ===============================================

    string_add(sh, "the begining, ", true);
    print_string(sh);
    printf("String len: %d\n", (int)strlen(sh->value));
    printf("Allocation len: %d\n", sh->allocated_size);
    // ===============================================

    string_replace(sh, "World", "World, World, World");
    print_string(sh);
    printf("String len: %d\n", (int)strlen(sh->value));
    printf("Allocation len: %d\n", sh->allocated_size);
    // ===============================================

    string_replace_all(sh, "World", "Cats");
    print_string(sh);
    printf("String len: %d\n", (int)strlen(sh->value));
    printf("Allocation len: %d\n", sh->allocated_size);
    // ===============================================

    string_free(sh);

    return 0;
}
