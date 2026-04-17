#include <stdio.h>
int main(){
	int a,b;
	double f;

	scanf("%d %d",&a,&b);
	f=(double)a/(double)b;
	printf("%d %d %f\n",a/b,a%b,f);
	return 0;
}