#include <stdio.h>

int main(void) {
	int i, num, count;
	int maxcount = 0;
	double x, y;
	float point[300][2];

	while (1) {
		maxcount = 0;
		count = 0;

		scanf("%d", &num);
		if (num == 0) {
			break;
		}

		for (i = 0; i < num; i++) {
			scanf("%f %f\n", &point[i][0], &point[i][1]);
		}

		for (x = 1; x < 10; x += 0.05) {
			for (y = 1; y < 10; y += 0.05) {
				for (i = 0; i < num; i++) {
					if (1.0 >= (x - point[i][0]) * (x - point[i][0]) + (y - point[i][1]) * (y - point[i][1])) {
						count++;
					}
				}
				if (count > maxcount) {
					maxcount = count;
				}
			}
		}
		printf("%d\n", maxcount);
	}
	return 0;
}