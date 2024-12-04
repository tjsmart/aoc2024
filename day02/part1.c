#include "slh/list.h"
#include "slh/slh.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_row(const char* line, slh_node_t** rp) {
	const char *start = line;
	while (*start != '\0') {
		char* end;
		int value = strtol(start, &end, 10);
		slh_list_append(rp, value);
		rp = &(*rp)->next;
		if (start == end) {
			break;
		}
		start = end;
	}
}

uint64_t is_safe(slh_node_t* row) {
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
		slh_node_t* row = NULL;
		read_row(line, &row);

		answer += is_safe(row);

		line = strtok(NULL, "\n");
	}

	return slh_solution_answer(answer);
}

int main(int argc, char* argv[]) {
	return slh_main(argc, argv, &solution);
}
