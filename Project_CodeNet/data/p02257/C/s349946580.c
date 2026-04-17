#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void)
{
	int i,j,n;
	int sosuu = 0;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &j);

		if (j != 1) {
			if ((j % 2) != 0 || (j == 2)) {
				if ((j % 3) != 0 || (j == 3)) {
						sosuu++;
				}
			}
		}
	}

	printf("%d\n", sosuu);
	return 0;
}
