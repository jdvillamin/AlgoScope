#include <stdio.h>

int main(void) {
	int n;
	int f = 0, i = 0, j = 0;
	int ary[101] = {};
	
	scanf("%d", &n);
	if(n % 4 == 0) f = 1;
	if(n % 7 == 0) f = 1;
	for(i = 4; i < 101; i += 4) {
		if(f == 1) break;
		for(j = 7; j < 101; j += 7) {
			if(n % (i + j) == 0) f = 1;
		}
	}
	printf( f ? "Yes\n" : "No\n");
	return 0;
}