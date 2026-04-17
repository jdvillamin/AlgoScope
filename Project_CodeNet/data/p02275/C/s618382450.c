#include <stdio.h>

#define Max 10000
#define N 200000
#define INFTY 1000000000

void  swap(int *x, int *y)
{
    int  buff;
	
	buff = *x;
	*x = *y;  
	*y = buff;
}

void printA(int A[Max], int k) {
	int i;

	for (i = 0; i < k - 1; i++)
		printf("%d ", A[i]);
	printf("%d\n", A[k - 1]);
}

void CountingSort(int A[Max], int B[Max], int k) {
	int i, j;
	int C[N] = {0};

	/* C[i] ??? i ???????????°????¨?????????? */
	for (j = 0; j < k; j++) C[A[j]]++;

	/* C[i] ??? i ??\????????°???????????°????¨??????????*/
	for (i = 1; i < k; i++) C[i] = C[i] + C[i-1];

	for (j = k - 1; j >= 0; j--) {
		B[C[A[j]] - 1] = A[j];
		C[A[j]]--;
	}
}

int main( ) {
	int k, i, count;
	int A[Max], B[Max];

	scanf("%d", &k);

	for (i = 0; i < k; i++) scanf("%d", &A[i]);

	CountingSort(A, B, k);

	printA(B, k);

	return 0;
}