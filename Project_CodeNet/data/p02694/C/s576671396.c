#include <stdio.h>

int main(void)
{
	int deposit;
	int X;
	int i;

	scanf("%d", &X);

	deposit = 100;

	for (i = 0; deposit < X; i++)
	{
		deposit = deposit * 1.01;
	}

	printf("%d\n", i);

	return 0;
}