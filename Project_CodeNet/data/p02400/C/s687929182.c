#include <stdio.h>
#define PI 3.141592
int main(void)
{
	double r;
	double c,d;

	scanf("%lf", &r);

	c = r * r * PI;
	d = 2 * PI*r;

	printf("%f %f\n", c, d);

	return 0;
}