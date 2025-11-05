#ifndef SLH_SLH_H
#define SLH_SLH_H

#include "slh/ptr.h"
#include <stdint.h>

typedef struct {
    char *err;
    int64_t answer;
} slh_solution_t;

slh_solution_t slh_solution_err(char *err);
slh_solution_t slh_solution_answer(int64_t answer);

int slh_main(int argc, char *argv[],
             slh_solution_t (*solution)(const slh_sized_ptr_t *));

#endif // SLH_SLH_H
