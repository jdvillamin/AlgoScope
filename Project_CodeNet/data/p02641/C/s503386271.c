#include <stdio.h>

int main(void)
{
	int x,n;
	int i;
	int j=0;
	int p[101];
	int k=0;
	int min;
	int mi;
	int count=0;
	int c=0;
	
	scanf("%d",&x);
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
	}
	while(j!=1001)
	{
		for(i=0;i<n;i++)
		{
			if(x-j!=p[i])
			{
				count++;
			}
			if(count==n)
			{
				min=j;
				break;
			}
		}
		j++;
	}
	
	while(k!=1001)
	{
		for(i=0;i<n;i++)
		{
			if(x+j!=p[i])
			{
				c++;
			}
			if(c==n)
			{
				mi=k;
				break;
			}
		}
		j++;
	}

	
	if(min<=mi)
	{
		printf("%d",x-min);
	}
	else
	{
		printf("%d",x-mi);
	}	
			

}