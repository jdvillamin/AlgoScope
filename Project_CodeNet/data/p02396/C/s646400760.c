#include <stdio.h>
int main(void) {
	
	int x[10001];
	int i = 1, j = 1;

	while (1) {
		scanf("%d\n", &x[i]);
		if (x[i] == 0) break;
		i++;
	}

	while (1) {
		printf("Case %d: %d\n", j, x[j]);
		if (j == i) break;
		j++;
	}

	return 0;
}