#ifndef SLH_PTR_H
#define SLH_PTR_H

#include <stddef.h>

typedef struct {
    char *ptr;
    size_t size;
} slh_sized_ptr_t;

slh_sized_ptr_t slh_sized_ptr_create(size_t size);

#endif // SLH_PTR_H
