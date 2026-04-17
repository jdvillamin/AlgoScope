#include <stdio.h>
#include <stdlib.h>


int main()
{
	int n, q;
	int A[20], m[200];
	int *dp;
	int num, sum;
	int maxi, maxv;
	int i, j, k;


	scanf("%d", &n);
	sum = 0;
	for(i = 0; i < n; i++){
		scanf("%d", &num);
		sum += A[i] = num;
	}

	scanf("%d", &q);
	maxv = 0;
	for(i = 0; i < q; i++){
		scanf("%d", &num);
		m[i] = num;
		if(num > maxv)
			maxv = num;
	}


	// 動的計画法で求める
	dp = (int *)malloc(sizeof(int) * maxv + 1);

	dp[0] = 0;
	for(j = 1; j <= maxv; j++)
		dp[j] = -1;

	maxi = 0;
	for(j = 0; j < n; j++){
		if(A[j] + maxi > maxv)
			k = maxv;
		else
			 k = maxi + A[j];
		for(; k >= A[j]; k--){
			if(dp[k] == -1 && dp[k - A[j]] != -1){
				dp[k] = j;
				if(k > maxi)
					maxi = k;
			}
		}
	}

	for(i = 0; i < q; i++){
		if(dp[m[i]] == -1)
			printf("no\n");
		else
			printf("yes\n");
	}

	return 0;
}
