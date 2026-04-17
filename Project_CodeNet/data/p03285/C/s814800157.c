#include <stdio.h>

int main(void)
{
	int N, x, a;
	scanf("%d", &N);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++) {
			x = (4 * i) + (7 * j);
			if (N%x == 0)
			{
				a++;
			}
		}
	}
	if (a > 0) {
		printf("Yes");
	}
	else
	{
		printf("No");
	}
}
