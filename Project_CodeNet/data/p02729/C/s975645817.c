#include <stdio.h>

int main()
{
	int n, m, result = 0;
	scanf("%d %d", &n, &m);
	result += m * (m - 1) / 2;
	result += n * (n - 1) / 2;
	printf("%d", result);
	return 0;
}