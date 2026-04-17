#include <stdio.h>

int main(void) {

	int H, W;
	int i, j;

	

	scanf("%d %d", &H,&W);

	for (i = 0; i < W; i++) {
		for (j = 0; j < H; j++) {

			if (H&&W == 0)
				break;
			printf("#");
		}
		printf("\n");
	}

	return(0);

}
