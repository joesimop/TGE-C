#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "../utils/helpers.h"

//update header size if changung the header struct
typedef struct {
    int size, capacity;
} da_header_t;
#define DA_HEADER_SIZE 16

#define da_start(_da) (((void*)(_da)) - DA_HEADER_SIZE)
#define da_size(_da)     ((da_header_t*) da_start((_da)))->size
#define da_capacity(_da) ((da_header_t*) da_start((_da)))->capacity
#define da_set_size(_da, _s)    ((da_header_t*) da_start((_da)))->size = (_s)
#define da_set_capacity(_da, _c) ((da_header_t*) da_start((_da)))->capacity = (_c)

//INTERNAL USE ONLY

//allocates data. must be explicit about how many.
void __da_init_impl(void** da, int tsize, int numElements);

//translates data from other array to a new dynamic array
void __da_init_with_data_impl(void** da, int tsize, int numElements, void* data);

//frees the data struct
void __da_free_impl(void* da);

//reallocates the data struct, doubling the capacity
da_header_t* __da_realloc_impl(void** da, int tsize);

//pushes an element to the end of the array, returns a pointer to the element
void* __da_push_impl(void** da, int tsize);

//pops an element from the end of the array, returns a pointer to the element
void* __da_pop_impl(void** da, int tsize);

//removes an element from the array at the given index
void __da_remove_index_impl(void** da, int index, int tsize);

#define DYNAMIC_ARRAY(_T) TYPEOF(((_T*)(NULL)))
#define da_init(_da, _ne)  __da_init_impl((void**) &(_da), sizeof(*(_da)), _ne)
#define da_init_from_data(_da, _data) __da_init_with_data_impl((void**) &(_da), sizeof(*(_da)), ARRAY_SIZE((_data)), (void*)(_data))
#define da_free(_da)       __da_free_impl((void*)(_da))
#define da_realloc(_da)    __da_realloc_impl((void**) &(da), sizeof(*(_da)))
#define da_push(_da)    (TYPEOF(_da))  __da_push_impl((void**) &(_da), sizeof(*(_da)))
#define da_pop(_da)     (TYPEOF(_da))  __da_pop_impl((void**) &(_da), sizeof(*(_da)))
#define da_remove(_da, _i) __da_remove_index_impl((void**) &(_da), _i, sizeof(*(_da)))
#endif