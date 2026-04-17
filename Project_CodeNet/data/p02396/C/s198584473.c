#include <stdio.h>

int main(void) 
{
	unsigned int i = 1;
	unsigned int x;
	
	while(x != 0)
	{
		scanf("%d", &x);
		if(x == 0)
		{
			break;
		}
		printf("Case %d: %d\n", i + 1, x);
		i++;
	}
	return 0;
}