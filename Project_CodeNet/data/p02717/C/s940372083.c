#include <stdio.h>
int main(void){
	int A,B,C,a;
	scanf("%d%d%d",&A,&B,&C);
	a=A;
	A=B;
	B=a;
	a=A;
	A=C;
	C=a;
	printf("%d %d %d",A,B,C);
	return 0;
}
