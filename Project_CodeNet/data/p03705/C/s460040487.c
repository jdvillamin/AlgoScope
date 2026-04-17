#include <stdio.h>
int main()
{
	int n,min,max;
	scanf("%d%d%d",&n,&min,&max);
	if(min>max)
	printf("0");
	else if(n==1&&min<max)
	printf("0");
	else if(n==1&&min==max)
	printf("1");
	else
	{
		int minsum=(n-1)*min+max;
		int maxsum=min+(n-1)*max;
		printf("%d",maxsum-minsum+1);
	}
	return 0;
}