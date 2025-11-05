#include "slh/vec.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

typedef struct slh_vec_header_t {
    size_t size;
    size_t cap;
    size_t elemsize;
} slh_vec_header_t;

void *slh_vec_create(size_t cap, size_t elemsize) {
    slh_vec_header_t *header =
        malloc(sizeof(slh_vec_header_t) + elemsize * cap);
    if (header == NULL) {
        assert("memory allocation failed" || false);
        return NULL;
    }
    header->size = 0;
    header->cap = cap;
    header->elemsize = elemsize;
    return (void *)(header + 1);
}

static slh_vec_header_t *slh_vec_header(const void *vec) {
    return ((slh_vec_header_t *)(vec)-1);
}

void slh_vec_free(void *vec) { free(slh_vec_header(vec)); }

size_t slh_vec_cap(const void *vec) { return slh_vec_header(vec)->cap; }

size_t slh_vec_size(const void *vec) { return slh_vec_header(vec)->size; }

void *slh_vec_resize(void *vec, size_t cap) {
    size_t size = slh_vec_size(vec);
    size_t elemsize = slh_vec_header(vec)->elemsize;
    slh_vec_header_t *new_header =
        realloc(slh_vec_header(vec), sizeof(slh_vec_header_t) + cap * elemsize);
    new_header->cap = cap;
    return (void *)(new_header + 1);
}

void *slh_vec_at(void *vec, size_t idx) {
    auto header = slh_vec_header(vec);
    if (idx >= header->size) {
        return nullptr;
    }
    if (idx < 0) {
        idx = header->size + idx;
        if (idx < 0) {
            return nullptr;
        }
    }
    return vec + header->elemsize * idx;
}

void *slh_vec_append(void *vec, const void *value) {
    auto header = slh_vec_header(vec);
    if (header->size >= header->cap) {
        auto new_cap = (header->cap == 0) ? 1 : (header->cap << 1);
        vec = slh_vec_resize(vec, new_cap);
        return slh_vec_append(vec, value);
    }
    auto end = header->size++;
    memcpy(slh_vec_at(vec, end), value, header->elemsize);
    return vec;
}

void slh_vec_map(void *vec, const void (*map)(void *)) {
    auto header = slh_vec_header(vec);
    for (int i = 0; i < header->size; i++) {
        map(slh_vec_at(vec, i));
    }
}

int slh_vec_find(void *vec, const void *value) {
    const auto header = slh_vec_header(vec);
    for (int i = 0; i < header->size; i++) {
        const auto elem = slh_vec_at(vec, i);
        const auto match = memcmp(elem, value, header->elemsize);
        if (match == 0) {
            return i;
        }
    }
    return -1;
}
