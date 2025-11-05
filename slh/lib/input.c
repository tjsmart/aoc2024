#include "slh/ptr.h"
#include <stdio.h>
#include <stdlib.h>

slh_sized_ptr_t slh_file_read_text(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return slh_sized_ptr_create(0);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return slh_sized_ptr_create(0);
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    fclose(file);
    return (slh_sized_ptr_t){.ptr = buffer, .size = file_size};
}

typedef struct {
    char *err;
    char *filename;
} slh_args_t;

slh_args_t parse_args(int argc, char *argv[]) {
    switch (argc) {
    case 1:
        return (slh_args_t){
            .err = "please provide a filename",
            .filename = NULL,
        };
    case 2:
        return (slh_args_t){
            .err = 0,
            .filename = argv[1],
        };
    default:
        return (slh_args_t){
            .err = "too many arguments, expected only one",
            .filename = NULL,
        };
    }
}
