#ifndef SLH_LIST_H
#define SLH_LIST_H

#include <stddef.h>
#include <stdint.h>

typedef struct slh_node_t {
    int32_t value;
    struct slh_node_t *next;
} slh_node_t;

slh_node_t *slh_list_create_node(int32_t value);

slh_node_t *slh_list_end(slh_node_t *node);

void slh_list_prepend(slh_node_t **node, int32_t value);

void slh_list_append(slh_node_t **node, int32_t value);

void slh_list_free(slh_node_t *node);

void slh_list_map(slh_node_t *node, void (*map)(slh_node_t *));

void slh_list_print(slh_node_t *node);

void slh_list_sort(slh_node_t **head);

size_t slh_list_size(slh_node_t *node);

slh_node_t *slh_list_index(slh_node_t *node, size_t idx);

slh_node_t *slh_list_find(slh_node_t *node, bool (*predicate)(slh_node_t *));

bool slh_list_contains(slh_node_t *node, int32_t value);

#endif // SLH_LIST_H
