#include "slh/list.h"

#include <stdio.h>
#include <stdlib.h>

slh_node_t *slh_list_create_node(int32_t value) {
    slh_node_t *list = malloc(sizeof(slh_node_t));
    if (list != NULL) {
        list->value = value;
        list->next = NULL;
    }
    return list;
}

slh_node_t *slh_list_end(slh_node_t *node) {
    if (node == NULL) {
        return NULL;
    }

    slh_node_t *end = node;
    while (end->next != NULL) {
        end = end->next;
    }
    return end;
}

void slh_list_prepend(slh_node_t **node, int32_t value) {
    slh_node_t *first = slh_list_create_node(value);

    first->next = *node;
    *node = first;
}

void slh_list_append(slh_node_t **node, int32_t value) {
    slh_node_t *next = slh_list_create_node(value);

    if (*node == NULL) {
        // list is empty 'insert' single node
        *node = next;
        return;
    }

    slh_node_t *end = slh_list_end(*node);
    if (end != NULL) {
        end->next = next;
    }
}

void slh_list_free(slh_node_t *node) {
    slh_node_t *temp = NULL;
    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
}

void slh_list_map(slh_node_t *node, void (*map)(slh_node_t *)) {
    if (node == NULL) {
        return;
    }
    map(node);
    slh_list_map(node->next, map);
}

void slh_list_print(slh_node_t *node) {
    void print_node(slh_node_t * node) {
        printf("%d", node->value);
        if (node->next != NULL) {
            printf(", ");
        }
    }

    printf("[");
    slh_list_map(node, &print_node);
    printf("]");
}

void slh_list_sort(slh_node_t **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    bool swapped;
    do {
        swapped = false;

        slh_node_t *prev = NULL;
        slh_node_t *curr = *head;
        slh_node_t *next = curr->next;
        while (next != NULL) {
            if (next->value < curr->value) {
                swapped = true;
                // need to update up to three connections here
                // prev->next->curr->(next->next)

                if (prev == NULL) {
                    *head = next;
                } else {
                    prev->next = next;
                }

                curr->next = next->next;
                next->next = curr;
                prev = next;

            } else {
                prev = curr;
                curr = prev->next;
            }

            next = curr->next;
        }
    } while (swapped);
}

size_t slh_list_size(slh_node_t *node) {
    size_t size = 0;
    void inc(slh_node_t * node) { size++; }

    slh_list_map(node, &inc);
    return size;
}

slh_node_t *slh_list_index(slh_node_t *node, size_t idx) {
    size_t loc = 0;
    while ((node != NULL) && (loc != idx)) {
        node = node->next;
        loc++;
    }
    return loc == idx ? node : NULL;
}

slh_node_t *slh_list_find(slh_node_t *node, bool (*predicate)(slh_node_t *)) {
    while ((node != NULL) && (!predicate(node))) {
        node = node->next;
    }
    return node;
}

bool slh_list_contains(slh_node_t *node, int32_t value) {
    bool eq_value(slh_node_t * node) { return node->value == value; }

    return slh_list_find(node, &eq_value) != NULL;
}
