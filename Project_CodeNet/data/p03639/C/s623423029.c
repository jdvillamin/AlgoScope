#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int main(void) {
	int n;
	int a[100000] = { 0 };
	int cnt_four = 0, cnt_two = 0, cnt_one = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if (a[i] % 4 == 0)cnt_four++;
		else if (a[i] % 2 == 0)cnt_two++;
		else cnt_one++;
	}
	if (cnt_two) {
		if (cnt_four >= cnt_one) printf("Yes");
		else printf("No");
	}
	else {
		if (cnt_four >= cnt_one - 1)printf("Yes");
		else printf("No");
	}
	return 0;
}
