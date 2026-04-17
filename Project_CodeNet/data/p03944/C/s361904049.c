#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()//面積
{
	int W, H, N, i, k, Black1,Black2,Black3,Black4;

	int x[100], y[100], a[100];

	scanf("%d", &W);
	scanf("%d", &H);
	scanf("%d", &N);
	
	for (i = 0; i <N; ++i) {
		scanf("%d", &x[i]);
		scanf("%d", &y[i]);
		scanf("%d", &a[i]);
	}
	int White = W * H;

	

	for (k = 0; k < N; k++) {

		if (a[k] == 1) {
			Black1 = H * x[k];
			White -= Black1;
		}

		if (a[k] == 2) {
			Black2 = H * (W - x[k]);
			White -= Black2;
		}

		if (a[k] == 3) {
			Black3 = W * y[k];
			White -= Black3;
		}

		if (a[k] == 4) {
			Black4 = W * (H - y[k]);
			White -= Black4;
		}
		
	}
	printf("白い面積は%d\n",White);

	return 0;
}

