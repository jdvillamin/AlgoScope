#include <stdio.h>

int main(void){
	int a,b,t;
	
	for(t=0;t<7;t++){
		scanf("%d %d",&a,&b);
		printf("%d\n",a-b);
	}
	return 0;
}