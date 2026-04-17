#include<stdio.h>
int main()
{
	int a,b;
	char op;
	while(1)
	{
		scanf("%d %c %d",&a,&op,&b);

		if(op == 43)
		{
			printf("%d\n",a+b);
		}
		else if(op == 45)
		{
			printf("%d\n",a-b);
		}
		else if(op == 42)
		{
			printf("%d\n",a*b);
		}
		else if(op == 47)
		{
			printf("%d\n",a/b);
		}
		else if(op == 63)
		{
			break;
		}
	}
	return 0;
}