#include "slh/slh.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

slh_solution_t slh_solution_err(char *err) {
    return (slh_solution_t){.err = err, .answer = 0};
}

slh_solution_t slh_solution_answer(int64_t answer) {
    return (slh_solution_t){.err = NULL, .answer = answer};
}

int slh_main(int argc, char *argv[],
             slh_solution_t (*solution)(const slh_sized_ptr_t *)) {
    slh_args_t slh_args = parse_args(argc, argv);
    if (slh_args.err != NULL) {
        printf("Error: %s\n", slh_args.err);
        return 1;
    }

    slh_sized_ptr_t input = slh_file_read_text(slh_args.filename);
    if (input.ptr == NULL) {
        return 1;
    };

    slh_solution_t solved = solution(&input);
    free(input.ptr);
    if (solved.err != NULL) {
        printf("Error: %s\n", solved.err);
        return 1;
    }

    printf("%ld\n", solved.answer);
    return 0;
}
