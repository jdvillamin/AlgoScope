#include <stdio.h>
int main(void) {
	int a, b, d, i;
	a = 0;
	b = 0;
	d = 0;
	i = 0;
	scanf("%d", &a);
	d = 100000;
	for (i = 1; i <= a; i++) {
		d = d * 1.05;
		b = d % 1000;
		if (b >= 1) {
			d = d - b;
			d = d + 1000;
		}
	}
	printf("%d", d);


	return 0;
}