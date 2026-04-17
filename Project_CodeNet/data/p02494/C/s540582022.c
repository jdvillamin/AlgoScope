#include<stdio.h>

int main() {
	int i, j, H, W;

	while (1) {
		scanf("%d%d", &H, &W);
		for (i = 0; i < H; i++) {
			for (j = 0; j < W; j++) {
				printf("#");
			}
			printf("\n");
		}
		if (H == 0 && W == 0) {
			break;
		}
	}
	return 0;
}