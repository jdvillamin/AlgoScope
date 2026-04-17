#include <stdio.h>

int main(void)
{

	int a,b,c,i;

	scanf("%d%d%d",&a,&b,&c);

	if(a<1||100<c)
	{
		return 1;
	}
	else if(a>b)
	{
		printf("0");
		return 1;
	}

	for(i=0; i>c; i++)
	{
		b=b-a;
		if(b<0)
		{
			 break;
		}
	}

	printf("%d",i);

	return 0;
}