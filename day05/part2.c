#include "slh/list.h"
#include "slh/slh.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMSLOTS 100
slh_node_t *rules[NUMSLOTS];

int check_update(char *p, int lineno) {
    slh_node_t *pages = nullptr;
    int numpages = 0;

    bool problem_detected = false;
    while (p) {
        char *next = strchr(p, ',');
        if (next)
            *next = '\0';

        int32_t current = atoi(p);
        slh_node_t *previous = pages;
        slh_node_t *insert_at = nullptr;
        while (previous) {
            if (slh_list_contains(rules[current], previous->value)) {
                // printf("update %d violates rule: %d|%d\n", lineno, current,
                //        previous->value);
                insert_at = previous;
            }
            previous = previous->next;
        }

        if (insert_at == nullptr) {
            slh_list_prepend(&pages, current);
        } else {
            problem_detected = true;
            slh_list_insert(&insert_at, current);
        }
        numpages++;
        p = next ? next + 1 : nullptr;
    }

    if (!problem_detected) {
        return 0;
    }

    assert(numpages % 2);
    int middlepage = numpages / 2;
    slh_node_t *middle = pages;
    while (middlepage--) {
        middle = middle->next;
    }
    printf("lineno %d has middle: %d\n", lineno, middle->value);
    return middle->value;
}

int dothatthingthing(char *line) {
    int lineno = 0;
    int sum = 0;
    while (line != NULL) {
        lineno++;
        sum += check_update(line, lineno);
        line = strtok(NULL, "\n");
    }
    return sum;
}

slh_solution_t solution(const slh_sized_ptr_t *input) {
    if (input->size == 0 || input->ptr == NULL) {
        return slh_solution_err("input file is empty");
    }

    memset(rules, 0, NUMSLOTS * sizeof(slh_node_t *));

    char *line = strtok(input->ptr, "\n");
    int32_t key, value;
    while (line != NULL) {
        if (sscanf(line, "%d|%d", &key, &value) != 2) {
            break;
        }
        assert(key < 100 && key >= 0);
        assert(value < 100 && value >= 0);
        slh_list_prepend(&rules[key], value);
        line = strtok(NULL, "\n");
    }

    int answer = dothatthingthing(line);

    for (int i = 0; i < NUMSLOTS; i++) {
        slh_list_free(rules[i]);
    }

    return slh_solution_answer(answer);
}

int main(int argc, char *argv[]) { return slh_main(argc, argv, &solution); }
