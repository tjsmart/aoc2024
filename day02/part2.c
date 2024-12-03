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

int sign(int value) {
	return value == 0 ? 0 : value > 0 ? 1 : -1;
}

int get_dir(list_t* node) {
	int asc = 0;
	int des = 0;
	int flt = 0;

	int i = 0;
	while ((node->next != NULL) && (++i < 6)) {
		switch (sign(node->next->value - node->value)) {
		case 1:
			asc++;
			break;
		case 0:
			flt++;
			break;
		case -1:
			des++;
			break;
		}

		node = node->next;
	}

	if ((asc > 1) && (des <= 1)) {
		return 1;
	}
	if ((des > 1) && (asc <= 1)) {
		return -1;
	}
	return 0;
}


bool diff_okay(int diff) {
	return (diff >= 1) && (diff <= 3);
}

bool is_safe(list_t* node) {
	int dir = get_dir(node);

	if (dir == 0) {
		return false;
	}

	list_t* prev = NULL;
	bool made_omission = false;
	while (node->next != NULL) {
		int diff = dir * (node->next->value - node->value);
		if (diff_okay(diff)) {
			prev = node;
			node = prev->next;
			continue;
		}

		if (made_omission) {
			return false;
		}

		made_omission = true;

		// if we are at the end
		if (node->next->next == NULL) {
			// we can remove node->next, but then we are all done!
			return true;
		}

		diff = dir * (node->next->next->value - node->value);
		if (diff_okay(diff)) {
			// remove the next node
			node->next = node->next->next;
			prev = node;
			node = prev->next;
			continue;
		}

		int diff1 = (prev == NULL) ? 1 : (node->next->value - prev->value);
		int diff2 = dir * (node->next->next->value - node->next->value);
		if (diff_okay(diff1) && diff_okay(diff2)) {
			// remove the current node
			prev = node;
			node = prev->next;
			continue;
		}

		// no omissions work ...
		return false;
	}

	return true;
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
