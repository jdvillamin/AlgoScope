#include<stdio.h>

int main(void)
{
	int n, k,num;
	int i;
	scanf("%d %d", &n, &k);
	num = k;
	for (i = 0; i < n - 1; i++)
	{
		num = num*(k - 1);
	}
	printf("%d\n", num);
	return 0;
}