#include <stdio.h>
#include <math.h>

int main() {

	int i, j, n, x, count;
	double m;

	count = 0;

	scanf("%d", &n);

	for (i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		m = sqrt(x);
		if (x == 2)
			count++;
		for (j = 3; j <= m + 1; j += 2)
		{
			if (x % j == 0)
			{
				break;
			}
			if (j >= m)
			{
				count++;
				break;
			}
		}
	}

	printf("%d\n", count);

	return 0;

}
