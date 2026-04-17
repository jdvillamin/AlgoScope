#include <stdio.h>
#include <string.h>
#define LIMIT_LINES (10)
#define LIMIT_STEPS (30)

char g_side[LIMIT_STEPS][LIMIT_LINES];

int draw_cross(char line[LIMIT_LINES], int end, int pos, int left) {
	if (left) {
		if (pos < 1 || line[pos-1] == '1')
			return 0;
		else if (pos > 1 && line[pos-2] == '1')
			return 0;
		else if (pos < end && line[pos] == '1')
			return 0;
		line[pos-1] = '1';
		return pos;
	}
	if (pos >= end || line[pos] == '1')
		return 0;
	else if (pos < end-1 && line[pos+1] == '1')
		return 0;
	else if (pos > 0 && line[pos-1] == '1')
		return 0;
	line[pos] = '1';
	return pos + 1;
}

int run(int start, int num_step, int add, int left, int *cross) {
	int end, pos, step;
	char line[LIMIT_LINES];

	end = strlen(g_side[0]);
	pos = start - 1;
	add -= 1;
	*cross = 0;
	for (step = 0; step < num_step; step++) {
		strcpy(line, g_side[step]);
		if (add == step) {
			*cross = draw_cross(line, end, pos, left);
			if (!cross)
				return 0;
		}
		if (pos > 0 && line[pos-1] == '1') {
			pos -= 1;
		}
		else if (pos < end && line[pos] == '1') {
			pos += 1;
		}
	}
	return pos + 1;
}

int main(void) {
	int n, start, hit, num_step, step, cross;

	while (1) {
		scanf(" %d ", &n);
		if (!n)
			break;
		scanf(" %d %d %d ", &start, &hit, &num_step);
		for (step = 0; step < num_step; step++) {
			scanf(" %s ", g_side[step]);
		}

		if (run(start, num_step, 0, 1, &cross) == hit) {
			puts("0");
			continue;
		}
		for (step = 0; step <= num_step; step ++) {
			if (run(start, num_step, step, 1, &cross) == hit) {
				printf("%d %d", step, cross);
				break;
			}
			if (run(start, num_step, step, 0, &cross) == hit) {
				printf("%d %d", step, cross);
				break;
			}
		}
		if (step > num_step) {
			puts("1");
		}
	}
	return 0;
}