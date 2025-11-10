#include "slh/slh.h"
#include <assert.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
} vec2_t;

size_t calc_dim(size_t inp_size) {
    if (inp_size == 110) { // special case, example input
        return 10;
    }
    if (inp_size == 17030) { // special case, real input
        return 130;
    }
    assert(false);
    return 0;
}

char *at(char *map, int n, vec2_t p) {
    // +1 for newline characters (assumes lf line endings)
    int index = p.x + (n + 1) * p.y;
    return map + index;
}

vec2_t find_start_position(char *map, int n) {
    char *p = map;
    vec2_t pos = {0, 0};
    for (;;) {
        switch (*p++) {
        case '^':
            return pos;
        case '\n':
            pos.y++;
            pos.x = 0;
            break;
        default:
            pos.x++;
        }
    }
}

vec2_t vec2_add(vec2_t l, vec2_t r) {
    return (vec2_t){.x = l.x + r.x, .y = l.y + r.y};
}

vec2_t vec2_rotate(vec2_t vec) { return (vec2_t){.x = -vec.y, .y = vec.x}; }

slh_solution_t solution(const slh_sized_ptr_t *input) {
    if (input->size == 0 || input->ptr == NULL) {
        return slh_solution_err("input file is empty");
    }
    size_t n = calc_dim(input->size);
    char *map = input->ptr;

    vec2_t pos = find_start_position(map, n);

    vec2_t dir = {0, -1};
    do {
        vec2_t next = vec2_add(pos, dir);
        char *np = at(map, n, next);
        if (*np == '#') {
            dir = vec2_rotate(dir);
            continue;
        }
        *np = 'X';
        pos = next;
    } while (pos.x >= 0 && pos.y >= 0 && pos.x < n && pos.y < n);

    int xcount = 0;
    char *p = map;
    for (;;) {
        switch (*p++) {
        case '\0':
            return slh_solution_answer(xcount);
        case 'X':
            xcount++;
        }
    }
}

int main(int argc, char *argv[]) { return slh_main(argc, argv, &solution); }
