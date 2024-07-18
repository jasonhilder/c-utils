#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    STRING_OK,
    STRING_ALLOC_ERR,
    STRING_UNKNOWN_ERR
} stringh_err_t;

typedef struct String {
    int allocated_size;
    char *value;
    stringh_err_t last_error;
} string_t;

string_t *string_new(const char *str);
void string_free(string_t* s);
void print_string(string_t* s);
void string_add(string_t* s, const char *new_str, bool prepend);
void string_replace(string_t* s, const char *sub_string, const char *replace_string);
void string_replace_all(string_t* s, const char *sub_string, const char *replace_string);
void string_get_error(string_t* s);

#endif /* STRING_H */

