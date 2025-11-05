#ifndef SLH_VEC_H
#define SLH_VEC_H

#include <stddef.h>
#include <stdint.h>

void *slh_vec_create(size_t cap, size_t elem_size);

void slh_vec_free(void *vec);

size_t slh_vec_cap(const void *vec);

size_t slh_vec_size(const void *vec);

void *slh_vec_resize(void *vec, size_t cap);

void *slh_vec_at(void *vec, size_t idx);

void *slh_vec_append(void *vec, const void *value);

void slh_vec_map(void *vec, const void (*map)(void *));

int slh_vec_find(void *vec, const void *value);

#endif // SLH_VEC_H
