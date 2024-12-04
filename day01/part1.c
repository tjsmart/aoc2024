#include "slh/list.h"
#include "slh/slh.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_two_cols(char* input, slh_node_t** lp, slh_node_t** rp) {
	char* line = strtok(input, "\n");

	int32_t lv, rv;
	while (line != NULL) {
		if (sscanf(line, "%d %d", &lv, &rv) == 2) {
			slh_list_append(lp, lv);
			slh_list_append(rp, rv);
			lp = &(*lp)->next;
			rp = &(*rp)->next;
		} else {
			printf("bad line: %s", line);
		}
		line = strtok(NULL, "\n");
	}

}

uint32_t get_er_done(slh_node_t* left, slh_node_t* right) {
	uint32_t answer = 0;
	while ((left != NULL) && (right != NULL)) {
		answer += abs(left->value - right->value);
		left = left->next;
		right = right->next;
	}
	return answer;
}

slh_solution_t solution(const slh_sized_ptr_t* input) {
	if (input->size == 0 || input->ptr == NULL) {
		return slh_solution_err("input file is empty");
	}

	slh_node_t* left = NULL;
	slh_node_t* right = NULL;
	read_two_cols(input->ptr, &left, &right);

	slh_list_sort(&left);
	slh_list_sort(&right);

	uint32_t answer = get_er_done(left, right);
	return slh_solution_answer(answer);
}

int main(int argc, char* argv[]) {
	return slh_main(argc, argv, &solution);
}
