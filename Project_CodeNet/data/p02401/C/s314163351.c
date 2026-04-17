#include<stdio.h>
int main()
{

	int a,b,c[20000],i,j;
	char op;
	i=0;
	while(1)
	{
		scanf("%d%c%d",&a,&op,&b);
		if(op=='?')
		{
		break;
		}
		else if(op == '+')
		{
			c[i]=a+b;
		}
		else if(op == '-')
		{
			c[i]=a-b;
		
		}
		else if(op == '*')
		{
			c[i]=a*b;
		
		}
		else if(op == '/')
		{
			c[i]=a/b;
		}
		i++;
	}

	for(j=0;j<i;j++)
	{
		printf("%d\n",c[j]);
	}
	
	return 0;	
}