#include "string_h.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

string_t* string_new(const char *str) {
    string_t* s = (string_t *) malloc(sizeof(string_t));
    if (s == NULL) {
        // Handle allocation failure
        return NULL;
    }

    int alloc_size = strlen(str) + 1;
    s->allocated_size = alloc_size;
    s->value = (char *) calloc(alloc_size, sizeof(char));
    if (s->value == NULL) {
        // Free struct if allocation fails
        #ifdef _DEBUG
        fprintf(stderr, "string_h::create_string, allocation failed!\n");
        #endif
        free(s); 
        return NULL;
    }

    strcpy(s->value, str);

    s->last_error = STRING_OK;
    return s;
};

void string_free(string_t *s) {
    if (s == NULL) {
    // Check for NULL pointer
        return; 
    }

    if (s->value != NULL) { 
        // Free the dynamically allocated string
        free(s->value);
        // Set to NULL to avoid dangling pointer
        s->value = NULL; 
    }

    // Free the struct itself
    free(s);
}

void print_string(string_t *s) {
    printf("%s\n", s->value);
};

// The third boolean parameter declares the position ie. is it prepend or append.
void string_add(string_t *s, const char *new_str, bool prepend) {
    char *res;

    s->allocated_size += strlen(new_str);

    if(prepend) {

        res = calloc(s->allocated_size, sizeof(char));

        if(!res) {
            #ifdef _DEBUG
            fprintf(stderr, "string_h::string_add, memory 'allocation' failed!\n");
            #endif
            s->last_error = STRING_ALLOC_ERR;
        }

        sprintf(res, "%s%s", new_str, s->value);

        free(s->value);
        s->value = res;

    } else {
        res = realloc(s->value, s->allocated_size);
        if(!res) {
            #ifdef _DEBUG
                fprintf(stderr, "string_h::string_replace, memory 'reallocation' failed!\n");
            #endif
            s->last_error = STRING_ALLOC_ERR;
        }

        strcat(res, new_str);
        s->value = res;
    }

    s->last_error = STRING_OK;
};

void string_replace(string_t *s, const char *sub_string, const char *replace_string) {

    if(strcmp(sub_string, replace_string) == 0) return;

    char *p = strstr(s->value, sub_string);

    if(p != NULL) {
        size_t len1 = strlen(sub_string);
        size_t len2 = strlen(replace_string);

        if(len1 != len2) {
            int new_alloc_size = s->allocated_size - len1 + len2;

            if(new_alloc_size > s->allocated_size) {
                char *new_value = (char *)malloc(new_alloc_size + 1);
                if(new_value == NULL) {
                    #ifdef _DEBUG
                        fprintf(stderr, "string_h::string_replace, Memory 'allocation' failed\n");
                    #endif
                    s->last_error = STRING_ALLOC_ERR;
                }

                // Copy the part of the string before the replacement
                size_t prefix_len = p - s->value;
                strncpy(new_value, s->value, prefix_len);
                new_value[p - s->value] = '\0';

                // Append the replacement string
                strcat(new_value, replace_string);

                // Append the part of the string after the replacement
                strcat(new_value, p + len1);

                free(s->value);

                s->value = new_value;
                s->allocated_size = new_alloc_size;
            } else {
                // If new_alloc_size is not larger, adjust in place
                memmove(p + len2, p + len1, strlen(p + len1) + 1);
                memcpy(p, replace_string, len2);

                char *tmp = (char *)realloc(s->value, new_alloc_size + 1);
                if(tmp == NULL) {
                    #ifdef _DEBUG
                        fprintf(stderr, "string_h::string_replace, Memory 'reallocation' failed\n");
                    #endif
                    s->last_error = STRING_ALLOC_ERR;
                }

                s->value = tmp;
                s->allocated_size = new_alloc_size;
            }
        } else {
            // If len1 == len2, just replace in place
            memcpy(p, replace_string, len2);
        }
    }

    return;
}

void string_replace_all(string_t *s, const char *sub_string, const char *replace_string) {

    while(true) {
        char *p = strstr(s->value, sub_string);

        if(p != NULL) {
            string_replace(s, sub_string, replace_string);
        } else {
            break;
        }
    }

    return;
}

static stringh_err_t string_last_error(string_t* s) {
    if (s == NULL) {
        // If the String is NULL, return unknown error
        return STRING_UNKNOWN_ERR;
    }

    return s->last_error;
}

void string_get_error(string_t* s) {
    switch (string_last_error(s)) {
        case STRING_OK:
            printf("No error\n");
            break;
        case STRING_ALLOC_ERR: 
            printf("Memory allocation error \n");
            break;
        case STRING_UNKNOWN_ERR:
            printf("Unknown error.\n");
            break;
    }
}

