#include<stdio.h>

int main(void) {
	int d1[10] = { 20,19,20,19,20,19,20,19,20,19 };
	int d2[10] = { 20,20,20,20,20,20,20,20,20,20 };
	int y1 = 195;
	int y2 = 200;

	int n;
	int Y, M, D;

	scanf("%d", &n);

	int i,j;
	int days;
	for (i = 0; i < n; i++) {
		days = 0;
		scanf("%d", &Y);
		scanf("%d", &M);
		scanf("%d", &D);

		if (Y % 3 == 0) {
			days += 20 - D + 1;
			j = M;
			while (j < 10) {
				days += d2[j];
				j++;
			}
		}else {
			days += d1[M - 1] - D + 1;
			j = M;
			while (j < 10) {
				days += d1[j];
				j++;

			}
		}
		//printf("%d ", days);
	

		j = Y + 1;
		//int day2 = 0;
		while (j < 1000) {
			if (j % 3 == 0) {
				days += y2;
			}else {
				days += y1;
			}
			j++;
		}
		//printf("%d ", day2);

		printf("%d\n", days);


	}
	return 0;

}
