#include <stdio.h>

int main(void) {
	int W, H, x, y, r;
	scanf("%d %d %d %d %d", &W, &H, &x, &y, &r); //60 40 30 -50 3
	
	if ((x < 0) || (y < 0)) {
		printf("No\n");
	} else if ((x + r <= W) && (y + r <= H)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	return 0;
}