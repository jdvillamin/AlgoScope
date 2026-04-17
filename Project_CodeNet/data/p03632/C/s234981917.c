#include<stdio.h>
int main()
{
	int a,b,c,d,n;
	while(scanf("%d%d%d%d",&a,&b,&c,&d)!=EOF)
	{
		if(a<b&&c<d)
		{
			if(b>c&&b<d)
			printf("%d\n",b-c);
			else if(b>c&&b>d)
			printf("%d\n",d-c);
			else printf("0\n");
		}
	}
	return 0;
}