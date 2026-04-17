#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
	char num[1001];
	int l, i, sum, n;
	while(1) {
		sum = 0;
		fgets(num, 1000, stdin);
		if (num[0] == '0') break;
		l = strlen(num) - 1;
		n = atoi(num);
		for (i = 0; i < l; ++i) {
			sum += n % 10;
			n /= 10;
		}
		printf("%d\n", sum);
	}
	return 0;
}
