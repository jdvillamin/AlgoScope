#include <stdio.h>

int main(){
    double a,b,c,d,e,f,x,y;
	while (scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f) != EOF)
	{
		x = (c*e-f*b)/(a*e-d*b);
		y = (c-a*x)/b;
		printf("%1.3f %1.3f\n",x,y);
	}
}