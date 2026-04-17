#include<stdio.h>

int main(void)
{
	long a,b,d,r;
	float f;
	
	scanf("%d %d",&a,&b);
	d=a/b;
	r=a%b;
	f=((float)a/(float)b);
	printf("%d %d %f",d,r,f);
	
	return 0;
} 