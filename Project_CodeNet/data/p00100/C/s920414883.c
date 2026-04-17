#include <stdio.h>

int main(void)
{
	int n, i;
	int e, p1, p2, cnt;
	long long num[4000] = {0};
	int flag[4000] = {0};
	long long tmp;

	while (1) {
		scanf("%d", &n);
		if (n == 0) {
			break;
		}
		cnt = 1;
		for (i = 0; i < 4000; ++i) {
			num[i] = 0;
			flag[i] = 0;
		}
		
		for (i = 0; i < n; ++i) {
			scanf("%d %d %d", &e, &p1, &p2);
			num[e] += p1 * p2;
			
			
			if (num[e] >= 1000000) {
				cnt = 0;
				if (flag[e] == 0) {
					printf("%d\n", e);
					flag[e] = 1;
				}
			}
		}
		if (cnt) printf("NA\n");
	}
	
	return 0;
}