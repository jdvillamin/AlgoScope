#include<stdio.h>
int main()
{
	int k;
	scanf("%d", &k);
	char s[102];
	scanf("%s", s);
	int i = 0;
	while (s[i] != '\0')
		i++;
	if (i <= k)
		printf("%s\n", s);
	else
	{
		for (i = 0; i < k; i++)
			printf("%c", s[i]);
		printf("...\n");
	}
	return 0;
}