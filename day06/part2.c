#include "slh/mat.h"
#include "slh/slh.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t n = 0;
char *map = nullptr;

size_t calc_dim(size_t inp_size) {
    if (inp_size == 110) { // special case, example input
        return 10;
    }
    if (inp_size == 17030) { // special case, real input
        return 130;
    }
    slh_panic("unexpected inp size: %zu", inp_size);
}

char *at(char *map, int n, slh_vec2_t p) {
    // +1 for newline characters (assumes lf line endings)
    int index = p.x + (n + 1) * p.y;
    return map + index;
}

slh_vec2_t find_start_position(char *map, int n) {
    char *p = map;
    slh_vec2_t pos = {0, 0};
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

int check_for_loop(slh_vec2_t obstacle, slh_vec2_t pos, slh_vec2_t dir,
                   slh_vec2_t *visited) {
    for (;;) {
        slh_vec2_t next = slh_vec2_add(pos, dir);
        if (next.x < 0 || next.y < 0 || next.x >= n || next.y >= n) {
            return 0;
        }
        char *np = at(map, n, next);
        if ((*np == '#') || slh_vec2_eq(next, obstacle)) {
            dir = slh_vec2_rotate(dir);
            continue;
        }
        slh_vec2_t *vp = &visited[next.x + next.y * n];
        if (slh_vec2_eq(*vp, dir)) {
            return 1;
        }
        *vp = dir;
        pos = next;
    };
}

slh_solution_t solution(const slh_sized_ptr_t *input) {
    if (input->size == 0 || input->ptr == NULL) {
        return slh_solution_err("input file is empty");
    }
    n = calc_dim(input->size);
    map = input->ptr;

    slh_vec2_t pos = find_start_position(map, n);

    slh_vec2_t visited[n * n];
    slh_vec2_t visited_copy[n * n];
    memset(visited, 0, sizeof(visited));

    slh_vec2_t dir = {0, -1};
    int loops = 0;
    for (;;) {
        slh_vec2_t next = slh_vec2_add(pos, dir);
        if (next.x < 0 || next.y < 0 || next.x >= n || next.y >= n) {
            break;
        }
        char *np = at(map, n, next);
        if (*np == '#') {
            dir = slh_vec2_rotate(dir);
            continue;
        }
        slh_vec2_t *vp = &visited[next.x + next.y * n];
        if (slh_vec2_eq(*vp, (slh_vec2_t){0, 0})) {
            // first time test if it can lead to a loop
            memcpy(visited_copy, visited, sizeof(visited));
            loops += check_for_loop(next, pos, dir, visited_copy);
        }
        *vp = dir;
        pos = next;
    }

    return slh_solution_answer(loops);
}

int main(int argc, char *argv[]) { return slh_main(argc, argv, &solution); }
