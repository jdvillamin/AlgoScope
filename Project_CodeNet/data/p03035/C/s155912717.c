#include <stdio.h>

int main(void)
{
	int A, B, ans = 0;
	scanf("%d %d", &A, &B);

	if (A >= 13)
		ans = B;
	else if (A >= 6)
		ans = B / 2;
	printf("%d\n", ans);
	return 0;
}
