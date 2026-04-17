#include <stdio.h>

int main(void)
{
	int a;
	int b;
	int d;
	int r;
	float f;
	float z;
	
	scanf("%d %d", &a, &b);
	z = a * 1.0;
	d = a / b;
	r = a % b;
	f = z / b;
	
	printf("%d %d %.5f\n", d, r, f);
	
	return (0);
}	 