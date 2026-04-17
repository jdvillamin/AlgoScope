//#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N, T[110];
	int sum1, sum2;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &T[i]);
	}

	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (T[i] < T[j])
			{
				int temp = T[i];
				T[i] = T[j];
				T[j] = temp;
			}
		}
	}
	
	sum1 = 0;
	sum2 = 0;
	for (int i = 0; i < N; i++)
	{
		if (sum1 > sum2)
			sum2 += T[i];
		else
			sum1 += T[i];
	}

	int diff;
	if (sum1 < sum2)
		diff = sum2 - sum1;
	else
		diff = sum1 - sum2;

	printf("%d", diff);
	return 0;
}