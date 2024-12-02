#include "slh/slh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_t {
	int32_t value;
	struct list_t* next;
} list_t;

list_t* list_create_node(int32_t value) {
	list_t* list = malloc(sizeof(list_t));
	if (list != NULL) {
		list->value = value;
		list->next = NULL;
	}
	return list;
}

list_t* list_end(list_t* node) {
	if (node == NULL) {
		return NULL;
	}

	list_t* end = node;
	while (end->next != NULL) {
		end = end->next;
	}
	return end;
}

void list_append(list_t** node, int32_t value) {
	list_t* next = list_create_node(value);

	if (*node == NULL) {
		// list is empty 'insert' single node
		*node = next;
		return;
	}

	list_t* end = list_end(*node);
	if (end != NULL) {
		end->next = next;
	}
}

void list_map(list_t* node, void(*map)(list_t*)) {
	if (node == NULL) {
		return;
	}
	map(node);
	list_map(node->next, map);
}

void list_print(list_t* node) {
	void print_node(list_t* node) {
		printf("%d", node->value);
		if (node->next != NULL) {
			printf("->");
		} else {
			printf("\n");
		}
	}

	list_map(node, &print_node);
}

void list_sort(list_t** head) {
	if (*head == NULL || (*head)->next == NULL) {
		return;
	}

	bool swapped;
	do {
		swapped = false;

		list_t* prev = NULL;
		list_t* curr = *head;
		list_t* next = curr->next;
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

			next=curr->next;
		}
	} while(swapped);
}

void read_two_cols(char* input, list_t** lp, list_t** rp) {
	char* line = strtok(input, "\n");

	int32_t lv, rv;
	while (line != NULL) {
		if (sscanf(line, "%d %d", &lv, &rv) == 2) {
			list_append(lp, lv);
			list_append(rp, rv);
			lp = &(*lp)->next;
			rp = &(*rp)->next;
		} else {
			printf("bad line: %s", line);
		}
		line = strtok(NULL, "\n");
	}

}

uint32_t get_er_done(list_t* left, list_t* right) {
	uint32_t answer = 0;
	uint32_t value = left->value;
	uint32_t chunk = 0;
	uint32_t multiplier = 0;
	while ((left != NULL) && (right != NULL)) {
		if (value == right->value) {
			chunk += value;
			right = right->next;
		} else if ((chunk != 0) && (value == left->value)) {
			multiplier += 1;
			left = left->next;
		} else if (chunk != 0) {
			answer += chunk * multiplier;
			chunk = multiplier = 0;
			value = left->value;
		} else {
			if (left->value < right->value) {
				left = left->next;
				if (left != NULL) {
					value = left->value;
				}
			} else {
				right = right->next;
			}
		}
	}

	while (left != NULL) {
		if (value == left->value) {
			multiplier += 1;
			left = left->next;
		}
	}

	answer += chunk * multiplier;
	return answer;
}

slh_solution_t solution(const slh_sized_ptr_t* input) {
	if (input->size == 0 || input->ptr == NULL) {
		return slh_solution_err("input file is empty");
	}

	list_t* left = NULL;
	list_t* right = NULL;
	read_two_cols(input->ptr, &left, &right);

	list_sort(&left);
	list_sort(&right);

	uint32_t answer = get_er_done(left, right);
	return slh_solution_answer(answer);
}

int main(int argc, char* argv[]) {
	return slh_main(argc, argv, &solution);
}
