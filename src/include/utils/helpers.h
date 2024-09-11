#pragma once

#include <stdlib.h>

//HELPERS
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define TYPEOF(_t) __typeof__(_t)

//Chekcs if variadic macros are empty or not
#define is_empty(...) ( sizeof( (char[]){#__VA_ARGS__} ) == 1 )

//Assert
#define ASSERT(condition, ...)                                                                                 \
    do {                                                                                                       \
        if (!(condition)) {                                                                                    \
            fprintf(stderr, "\n**********************************************************\n");                 \
            fprintf(stderr, "Assertion failed: %s\n", #condition);                                             \
            fprintf(stderr, "Error: %s\n", is_empty(__VA_ARGS__) ? "No message" : #__VA_ARGS__);               \
            fprintf(stderr, "File: %s, Line: %d\n", __FILE__, __LINE__);                                       \
            fprintf(stderr, "**********************************************************\n");                   \
            exit(EXIT_FAILURE);                                                                                \
        }                                                                                                      \
    } while (0)



