#include "slh/slh.h"
#include <stdio.h>

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

bool xmas_found_at_dir(const chart_t* chart, vec2 p, const vec2 dir) {
	const char* XMAS = "XMAS";
	bool match = true;
	for (int64_t i = 1; i < 4; ++i) {
		p = vec2_add(p, dir);
		char value = value_at(chart, p);
		if (value != XMAS[i]) {
			match = false;
			break;
		}
	}
	return match;
}

const vec2 UP = {-1, 0};
const vec2 UP_RIGHT = {-1, 1};
const vec2 RIGHT = {0, 1};
const vec2 DOWN_RIGHT = {1, 1};
const vec2 DOWN = {1, 0};
const vec2 DOWN_LEFT = {1, -1};
const vec2 LEFT = {0, -1};
const vec2 UP_LEFT = {-1, -1};

const vec2 DIRECTIONS[8] = {
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
};

size_t count_xmas_at(const chart_t* chart, const vec2 p) {
	size_t count = 0;
	if (value_at(chart, p) != 'X') {
		return count;
	}

	for (uint8_t i = 0; i < 8; ++i) {
		vec2 dir = DIRECTIONS[i];
		count += xmas_found_at_dir(chart, p, dir);
	}
	return count;
}


slh_solution_t solution(const slh_sized_ptr_t* input) {
	if (input->size == 0 || input->ptr == NULL) {
		return slh_solution_err("input file is empty");
	}

	int64_t answer = 0;
	chart_t chart = create_chart(input);

	for (size_t y=0; y < chart.size.y; ++y) {
		for (size_t x=0; x < chart.size.x; ++x) {
			answer += count_xmas_at(&chart, (vec2){x, y});
		}
	}

	return slh_solution_answer(answer);
}

int main(int argc, char* argv[]) {
	return slh_main(argc, argv, &solution);
}
