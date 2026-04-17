#include<stdio.h>

int max(char *s, char B, char W) {
	int i, j = 0, n = 0;
	while(*(s+1) != '\0') {
		n++;
	}
	for(i = n; i > 0; i--) {
		if(*(s+i-1) == B && *(s+i) == W) {
			*(s+i-1) = W;
			*(s+i) = B;
			j++;
		}
	}
	return j;
}

int main(void) {
	char st[2*10000];
	char B, W;
	fgets(st, 2*pow(10,4), stdin);
	printf("%d", max(st, B, W));
	return 0;
}