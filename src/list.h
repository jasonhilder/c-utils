
#ifndef LIST_LIB_H
#define LIST_LIB_H

#include <stddef.h>

typedef struct Node {
    // pointer to the array of items
    void* data;
    // pointer to next linked list node
    struct Node* next;
    // pointer to previous linked list node
    struct Node* prev;
} node_t;

node_t* list_new(void);
node_t* list_free(void);

#endif /* LIST_LIB_H */

