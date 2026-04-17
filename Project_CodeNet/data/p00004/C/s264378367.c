#include <stdio.h>

int main(void){
	int a,b,c,d,e,f;
	int i;
	int x,y;
	
	while(scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f) != EOF){
	
		x = (c*e-f*b)/(a*e-b*d);
		y = -(c*d-f*a)/(a*e-b*d);
		printf("%.3f %.3f\n",(double)x,(double)y);
	}
	return 0;
}