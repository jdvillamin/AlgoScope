#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long Compare(const void *a, const void *b) {
	return *(long*)b - *(long*)a;
}

int main(void)
{
	long int members[300000] = { 0 }, ans = 0;
	int num;
	scanf("%d", &num);
	for (int i = 0; i < 3 * num; i++) {
		scanf("%d", &members[i]);
	}

	qsort(members, num * 3, sizeof(long int), Compare);

	for (int i = 0; i < 2 * num; i++) {
		if (i % 2 == 1) {
			ans += members[i];
		}
	}
	printf("%ld", ans);
	return 0;
}
