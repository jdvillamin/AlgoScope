#include <stdio.h>

int main(void)
{
	double r, shuu, men;
	double pi;
	
	scanf("%lf", &r);
	
	pi = 3.1415926535;
	
	shuu = r * 2 * pi;
	men = r * r * pi;
	
	printf("%f %f\n", shuu, men);
	
	return (0);
}