#include<stdio.h>

int main(void){
	int a,b,c;
	printf("put");
	scanf("%d",&b);
	printf("put");
	scanf("%d",&c);
	a = 500 * b;
	if(a >= c) {
		printf("Yes");
	}else{
		printf("No");
	}
	return 0;	
}