#include<stdio.h>

#define MAX_N 100
#define MAX_A 2000
int MAP[MAX_N][MAX_N];
int colorflag[MAX_N];

int MinimumSpanningTree(int n) {
	int i, j, k, sum, min, min_node, color[n];

	// 初期化
	sum = 0;
	k = 1;
	colorflag[0] = 1;
	for( i=0; i<n; i++) colorflag[i] = 0;
	color[0] = 0;

	while(1) {
		// ノードk個の最小全域木を求める
		min = MAX_A + 1;
		for( i=0; i<k; i++) {
			for( j=i+1; j<n; j++) {
				if(colorflag[j] == 1) continue;
				if(MAP[ color[i] ][j] < 0) continue;
				if(MAP[ color[i] ][j] < min) {
					min = MAP[ color[i] ][j];
					min_node = j;
				}
			}
		}
		
		// ノードk+1個の最小全域木の作成
		if(++k < n) {
			color[k] = min_node;
			colorflag[min_node] = 1;
			sum += min;
		}
		else break;
	}

	return sum;
}

int main(void) {
	int n, i, j;

	// input
	scanf("%d", &n);
	for( i=0; i<n; i++) {
		for( j=0; j<n; j++) {
			scanf("%d", &MAP[i][j]);
		}
	}

	// output	
	printf("%d\n", MinimumSpanningTree(n) );
	return 0;
}