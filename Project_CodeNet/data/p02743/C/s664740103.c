#include<stdio.h>
#include<math.h>
int main(void){
	long long int a,b,c;
	scanf("%lld %lld %lld",&a,&b,&c);
	if(sqrt(a)+sqrt(b)<sqrt(c)){
		printf("Yes");
	}else{
		printf("No");
	}
	return 0;
}





