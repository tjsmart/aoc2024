#include "slh/list.h"
#include "slh/slh.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef enum {
	SEARCH,
	NUMBER1,
	NUMBER2,
} yiggity_state_t;

bool startswith(char* str, char* pattern) {
	while ((*pattern != '\0') && (*str != '\0') && (*str == *pattern)) {
		str++;
		pattern++;
	}
	return *pattern == '\0';
}

uint32_t yo_yiggity(char* c) {
	if (c == NULL) {
		return 0;
	}

	yiggity_state_t state = SEARCH;
	uint32_t number1 = 0;
	uint32_t number2 = 0;
	uint8_t digit = 0;

	uint32_t yiggity = 0;
	while (*c != '\0') {
		switch (state) {
		case SEARCH:
			if (startswith(c, "mul(")) {
				c += 4;
				state++;
			} else {
				c++;
			}
			break;
		case NUMBER1:
			digit = (uint8_t)(*c - '0');
			if ((digit >= 0) && (digit <= 9)) {
				number1 = (10 * number1) + digit;
			} else if ((*c == ',') && (number1 != 0)) {
				state++;
			} else {
				number1 = 0;
				state = 0;
			}
			c++;
			break;
		case NUMBER2:
			digit = (uint8_t)(*c - '0');
			if ((digit >= 0) && (digit <= 9)) {
				number2 = (10 * number2) + digit;
			} else {
				if (*c == ')') {
					yiggity += number1 * number2;
				}
				number1 = 0;
				number2 = 0;
				state = 0;
			}
			c++;
			break;
		}
	}
	return yiggity;
}

uint32_t iter_input_lines(char* input, uint32_t(*something)(char*)) {
	char* line = strtok(input, "\n");

	uint32_t answer = 0;
	while (line != NULL) {
		answer += something(line);
		line = strtok(NULL, "\n");
	}

	return answer;
}

slh_solution_t solution(const slh_sized_ptr_t* input) {
	if (input->size == 0 || input->ptr == NULL) {
		return slh_solution_err("input file is empty");
	}

	uint64_t answer = iter_input_lines(input->ptr, &yo_yiggity);
	return slh_solution_answer(answer);
}

int main(int argc, char* argv[]) {
	return slh_main(argc, argv, &solution);
}
