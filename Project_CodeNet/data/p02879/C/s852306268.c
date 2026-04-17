#include <stdio.h>
int main(void){
	int a,i,c=0;
	float f;
	scanf("%d",&a);
	f=a;
	for(i=2;i<10;i++){
		if((a%i==0)&&(f/i<10))c=1;
	}
	c==1?printf("Yes"):printf("No");
	return 0;
}