#include<stdio.h>

int main(){
	int R,G;
	int x;
	

	scanf("%d", &R);
	fflush(stdin);

	scanf("%d", &G);
	fflush(stdin);
	
	x = (G*2) - R;
	
	printf("%d", x);
	
	return 0;
}