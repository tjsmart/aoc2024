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

void read_row(const char* line, list_t** rp) {
	const char *start = line;
	while (*start != '\0') {
		char* end;
		int value = strtol(start, &end, 10);
		list_append(rp, value);
		rp = &(*rp)->next;
		if (start == end) {
			break;
		}
		start = end;
	}
}

uint64_t is_safe(list_t* row) {
	if ((row == NULL) || (row->next == NULL)) {
		return 1;
	}

	bool ascending = row->value < row->next->value;
	while (row->next != NULL) {
		int diff = row->next->value - row->value;
		if (ascending) {
			if ((diff < 1) || (diff > 3)) {
				return 0;
			}
		} else {
			if ((diff > -1) || (diff < -3)) {
				return 0;
			}
		}
		row = row->next;
	}
	return 1;
}

slh_solution_t solution(const slh_sized_ptr_t* input) {
	if (input->size == 0 || input->ptr == NULL) {
		return slh_solution_err("input file is empty");
	}

	uint64_t answer = 0;
	char* line = strtok(input->ptr, "\n");

	while (line != NULL) {
		list_t* row = NULL;
		read_row(line, &row);

		answer += is_safe(row);

		line = strtok(NULL, "\n");
	}

	return slh_solution_answer(answer);
}

int main(int argc, char* argv[]) {
	return slh_main(argc, argv, &solution);
}
