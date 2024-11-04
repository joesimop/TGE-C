#include "dynamicarray.h"

void __da_init_impl(void** da, int tsize, int numElements) {
    da_header_t* start = (da_header_t*) malloc(DA_HEADER_SIZE + tsize * numElements);
    start->size = 0;
    start->capacity = numElements;
    *da = (void*) start + DA_HEADER_SIZE;
}

// translates data from other array to a new dynamic array
void __da_init_with_data_impl(void** da, int tsize, int numElements, void* data) {
    int da_size = numElements * 2;
    da_header_t* header = (da_header_t*) malloc(DA_HEADER_SIZE + tsize * da_size);
    header->size = numElements;
    header->capacity = da_size;
    *da = (void*) header + DA_HEADER_SIZE;
    memcpy(*da, data, tsize * numElements);
}

// frees the data struct
void __da_free_impl(void* da) { free(da_start(da)); }

// reallocates the data struct, doubling the capacity
da_header_t* __da_realloc_impl(void** da, int tsize) {
    da_header_t* start = (da_header_t*) da_start(*da);
    int newCapacity = start->capacity * 2;
    start = realloc(start, DA_HEADER_SIZE + newCapacity * tsize);
    start->capacity = newCapacity;
    *da = ((void*) start) + DA_HEADER_SIZE;
    return start;
}

// pushes an element to the end of the array, returns a pointer to the element
void* __da_push_impl(void** da, int tsize) {
    da_header_t* header = (da_header_t*) da_start(*da);
    if (header->size == header->capacity) {
        header = __da_realloc_impl(da, tsize);
    }
    header->size++;
    return *da + ((header->size - 1) * tsize);
}

// pops an element from the end of the array, returns a pointer to the element
void* __da_pop_impl(void** da, int tsize) {
    da_header_t* header = (da_header_t*) da_start(*da);
    if (header->size == 0) {
        return NULL;
    }
    header->size--;
    return *da + (header->size * tsize);
}

// removes an element from the array at the given index
void __da_remove_index_impl(void** da, int index, int tsize) {
    da_header_t* header = (da_header_t*) da_start(*da);
    ASSERT(da_size(*da) != 0 && index < da_size(*da), "Tried to remove from dynamic array or index out of bounds");
    memcpy(*da + (index * tsize), *da + ((index + 1) * tsize), (header->size - index - 1) * tsize);
    header->size--;
}
