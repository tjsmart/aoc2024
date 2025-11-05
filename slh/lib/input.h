#include "slh/ptr.h"

#ifndef SLH_INPUT
#define SLH_INPUT

slh_sized_ptr_t slh_file_read_text(char *filename);

typedef struct {
    char *err;
    char *filename;
} slh_args_t;

slh_args_t parse_args(int argc, char *argv[]);

#endif
