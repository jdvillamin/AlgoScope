#include <stdio.h>

int main(void)
{
	int n = 0;
	int m = 0;
	int sum = 0;

	scanf("%d %d", &m, &n);

	if ((2 <= m && m <= 100)
	 && (2 <= n && n <= 100)
	) {
		sum = (m - 1) * (n - 1);
	}

	printf("%d\n", sum);

	return 0;
}