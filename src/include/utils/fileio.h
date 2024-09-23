#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"

#ifndef PAGE_SIZE
#define PAGE_SIZE sysconf(_SC_PAGE_SIZE);
#endif

//Reads a shader file and stores its contents in shaderSource and its size in shaderSize
//Errors if the file is not found or if there is an error reading the file
void read_shader(const char *filename, char** shaderSource, size_t* shaderSize);

//Read all data from file f and stores it in buf and its size in len
//If chunk_size is 0, it will default to PAGE_SIZE
int read_all(FILE *f, char** buf, size_t* size_ptr, size_t chunk_size);
