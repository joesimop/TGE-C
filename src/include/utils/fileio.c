#include "fileio.h"

#define FILEREAD_OK      0  /* Success */
#define FILEREAD_INVALID -1 /* Invalid parameters */
#define FILEREAD_ERROR   -2 /* Stream error */
#define FILEREAD_TOOMUCH -3 /* Too much input */
#define FILEREAD_NOMEM   -4 /* Out of memory */

#define MAX_SHADER_PATH_LEN 100

void read_shader(const char* filename, char** shaderSource, size_t* shaderSize) {

    // Construct filename, make sure it is not too long
    ASSERT(strlen(filename) <= MAX_SHADER_PATH_LEN, "Filename too long: %s", filename);
    char path[MAX_SHADER_PATH_LEN + ARRAY_SIZE(SHADER_DIR)] = SHADER_DIR;
    strcat(path, filename);

    FILE* shaderFile = fopen(path, "r");

    ASSERT(shaderFile != NULL, "Failed to open shader: %s", path);
    ASSERT(read_all(shaderFile, shaderSource, shaderSize, 0) == FILEREAD_OK, "Failed to read file: %s", filename);
}

int read_all(FILE* f, char** buf, size_t* size_ptr, size_t chunk_size) {

    fprintf(stderr, "STARTING FILE READ\n");
    char *data = NULL, *temp;
    size_t size = 0;
    size_t used = 0;
    size_t n;

    chunk_size = chunk_size ? chunk_size : PAGE_SIZE;

    /*
        None of the parameters can be NULL.
        Explicit for error pinpointing
    */
    assert(f != NULL);
    assert(buf != NULL);
    assert(size_ptr != NULL);

    if (ferror(f)) {
        return FILEREAD_INVALID;
    }

    // Inital read parameters
    size += chunk_size;
    data = malloc(sizeof(char*) * size);
    if (data == NULL) {
        return FILEREAD_NOMEM;
    }

    fprintf(stderr, "STARTING LOOP\n");
    while (1) {

        // Check if we are a chunck size away from filling our buffer
        if (size - used < chunk_size) {

            // If so, increase the buffer size by a chunk
            size += chunk_size;
            temp = realloc(data, size);
            if (temp == NULL) {
                free(data);
                return FILEREAD_NOMEM;
            }
            data = temp;
        }

        // Read data and if none is found, or we don't read a full chunk break
        n = fread(data + used, 1, chunk_size, f);
        used += n;
        if (n == 0 || n < chunk_size) {
            break;
        }
    }

    // Make sure there were no errors
    if (ferror(f)) {
        free(data);
        return FILEREAD_ERROR;
    }
    // Optimize the buffer size
    temp = realloc(data, used);
    if (temp == NULL) {
        free(data);
        return FILEREAD_NOMEM;
    }

    data = temp;
    *buf = data;
    *size_ptr = used;

    fprintf(stderr, "File Read Info:\n");
    fprintf(stderr, "Size: %ld\n", used);

    return FILEREAD_OK;
}
