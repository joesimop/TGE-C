#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


// HELPERS
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define TYPEOF(_t) __typeof__(_t)

#define MIN(_a, _b)                                                                                                    \
    ({                                                                                                                 \
        __typeof__(_a) __a = (_a), __b = (_b);                                                                         \
        __a < __b ? __a : __b;                                                                                         \
    })
#define MAX(_a, _b)                                                                                                    \
    ({                                                                                                                 \
        __typeof__(_a) __a = (_a), __b = (_b);                                                                         \
        __a > __b ? __a : __b;                                                                                         \
    })
#define CLAMP(_x, _mi, _ma) (MIN(MAX(_x, _mi), _ma))

// Assert
#define ASSERT(condition, _fmt, ...)                                                                                   \
    do {                                                                                                               \
        if (!(condition)) {                                                                                            \
            fprintf(stderr, "\n**********************************************************\n");                         \
            fprintf(stderr, "Assertion failed: %s\n", #condition);                                                     \
            fprintf(stderr, _fmt, ##__VA_ARGS__);                                                                      \
            fprintf(stderr, "\nFile: %s, Line: %d\n", __FILE__, __LINE__);                                             \
            fprintf(stderr, "**********************************************************\n");                           \
            exit(EXIT_FAILURE);                                                                                        \
        }                                                                                                              \
    } while (0)
