#include <stdio.h>
int main(void)
{
	int N, minj, count = 0, temp, A[100];
	int a, i, j;

	scanf("%d",&N);
	for (a = 0; a < N; a++)
	{
		scanf("%d",&A[a]);
	}

	for (i = 0; i < N; i++)
	{
		minj = i;
		for (j = i; j < N; j++)
		{
			if (A[j] < A[minj])
			{
				minj = j;
			}
		}
		if (i != minj)
		{
			count++;
			temp = A[i];
			A[i] = A[minj];
			A[minj] = temp;
		}
	/*for (a = 0; a < N-1; a++)
	{
		printf("%d ",A[a]);
	}
	printf("%d ", A[N-1]);
	printf("%d\n", count);*/
	}

	for (a = 0; a < N-1; a++)
	{
		printf("%d ",A[a]);
	}
	printf("%d\n", A[N-1]);
	printf("%d", count);
	
	return 0;
}