#include "slh/slh.h"
#include <stdio.h>
#include <string.h>

typedef struct {
	int64_t x;
	int64_t y;
} vec2;

vec2 vec2_scale(const vec2 v, const int64_t scale) {
	return (vec2){.x=(v.x * scale), .y=(v.y * scale)};
}

vec2 vec2_add(const vec2 v1, const vec2 v2) {
	return (vec2){.x=(v1.x + v2.x), .y=(v1.y + v2.y)};
}

typedef struct {
	char* buffer;
	vec2 size;
} chart_t;


chart_t create_chart(const slh_sized_ptr_t* input) {
	size_t ysize = 0;
	size_t xsize = 0;

	char* ptr = input->ptr;
	while (*ptr++ != '\n') {
		xsize++;
	}

	ptr = input->ptr;
	while (*ptr++ != '\0') {
		if (*ptr == '\n') {
			ysize++;
		}
	}

	if (input->ptr[input->size-1] != '\n') {
		ysize++;
	}

	return (chart_t){.size=(vec2){.x=xsize, .y=ysize}, .buffer=input->ptr};
}

size_t index_of(const chart_t* chart, const vec2 p) {
	return p.y * (chart->size.x + 1) + p.x;
}

char value_at(const chart_t* chart, const vec2 p) {
	if (
		(p.x < 0)
		|| (p.x >= chart->size.x)
		|| (p.y < 0)
		|| (p.y >= chart->size.y)
	) {
		return '\0';
	}

	return chart->buffer[index_of(chart, p)];
}

const vec2 UP_RIGHT = {-1, 1};
const vec2 DOWN_RIGHT = {1, 1};
const vec2 DOWN_LEFT = {1, -1};
const vec2 UP_LEFT = {-1, -1};


char* read_diagonals(const chart_t* chart, const vec2 p) {
	static char diagonals[] = "0000\0";
	diagonals[0] = value_at(chart, vec2_add(p, UP_LEFT));
	diagonals[1] = value_at(chart, vec2_add(p, UP_RIGHT));
	diagonals[2] = value_at(chart, vec2_add(p, DOWN_LEFT));
	diagonals[3] = value_at(chart, vec2_add(p, DOWN_RIGHT));
	return diagonals;
}

bool has_xmas_at(const chart_t* chart, const vec2 p) {
	if (value_at(chart, p) != 'A') {
		return false;
	}

	char* diagonals = read_diagonals(chart, p);
	return (
		(strcmp(diagonals, "MMSS") == 0)
	    || (strcmp(diagonals, "SSMM") == 0)
		|| (strcmp(diagonals, "MSMS") == 0)
	    || (strcmp(diagonals, "SMSM") == 0)
	);
}


slh_solution_t solution(const slh_sized_ptr_t* input) {
	if (input->size == 0 || input->ptr == NULL) {
		return slh_solution_err("input file is empty");
	}

	int64_t answer = 0;
	chart_t chart = create_chart(input);

	for (size_t y=0; y < chart.size.y; ++y) {
		for (size_t x=0; x < chart.size.x; ++x) {
			answer += has_xmas_at(&chart, (vec2){x, y});
		}
	}

	return slh_solution_answer(answer);
}

int main(int argc, char* argv[]) {
	return slh_main(argc, argv, &solution);
}
