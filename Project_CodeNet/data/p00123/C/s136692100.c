#include<stdio.h>
int main(void)
{
float a,b;
	scanf("%f %f",&a,&b);
	if(a>=70.00||b>=148.00)
	{
		printf("NA\n");
	}
	else if(a<35.50&&b<71.00)
	{
		printf("AAA\n");
	}
	else if(a<37.00&&b<77.00)
	{
		printf("AA\n");
	}
	else if(a<40.00&&b<83.00)
	{
		printf("A\n");
	}
	else if(a<43.00&&b<89.00)
	{
		printf("B\n");
	}
	else if(a<50.00&&b<105.00)
	{
		printf("C\n");
	}
	else if(a<55.00&&b<116.00)
	{
		printf("D\n");
	}
	else
	{
		printf("E\n");
	}
	return 0;
}