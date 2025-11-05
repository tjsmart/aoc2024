#include "slh/ptr.h"
#include <stdlib.h>

slh_sized_ptr_t slh_sized_ptr_create(size_t size) {
    char *ptr = malloc(size * sizeof(char));
    if (ptr == NULL) {
        size = 0;
    }
    return (slh_sized_ptr_t){.ptr = ptr, .size = size};
}
