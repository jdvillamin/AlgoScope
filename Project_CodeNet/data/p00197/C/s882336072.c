#include<stdio.h>
int main(void){
	int a,b,r,temp;
	int count = 0;
	while(scanf("%d %d",&a,&b)){
		if(a == 0 && b == 0){
			break;
		}
		if(a < b){
			temp = a;
			a = b;
			b = temp;
		}
		while( count++, (r = a % b) != 0){
			a = b;
			b = r;
		}
		printf("%d %d\n",b,count);
		count = 0;
	}
	return 0;
}