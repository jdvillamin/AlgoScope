#include<stdio.h>
int f_max(int a, int b)
{
	if (a > b)return a;
	else return b;
}
int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	char s[100005];
	scanf("%s", s);
	int c = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		if (s[i] == '0')
			c = 0;
		else
			c++;
		if (c >= m)
		{
			printf("-1\n");
			return 0;
		}
	}
	int v[100005];
	v[0] = 0;
	for (i = 0; i <= n; i++)
	{
		if (s[i] == '0')
			v[i + 1] = v[i];
		else
			v[i + 1] = v[i] + 1;
	}
	int min, mid, max;
	int ans[100005], p = 0;
	i = n;
	while (i > 0)
	{
		if (s[f_max(0, i - m)] == '0')
		{
			ans[p] = i - f_max(0, i - m);
			i = f_max(0, i - m);
			p++;
		}
		else
		{
			max = i;
			min = f_max(0, i - m + 1);
			while (max - min > 1)
			{
				mid = (max + min) / 2;
				if (v[mid + 1] - v[min] < mid - min + 1)
					max = mid;
				else
					min = mid;
			}
			ans[p] = i - min;
			p++;
			i = min;
		}
	}
	for (i = p - 1; i > 0; i--)
		printf("%d ", ans[i]);
	printf("%d\n", ans[0]);
	return 0;
}