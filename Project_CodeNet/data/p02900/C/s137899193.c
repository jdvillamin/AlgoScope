#include <stdio.h>
#include <math.h>


int sosuu(long int num){
	long int i,c = sqrt(num);
	for(i=2;i<=c;i++){
		if(num % i == 0) return 1;
	}
	return 2;
}

long int divisor(long int numa,long int numb){
	long int ans = 1;
	long int i;
	long int g;
	for(i=2;i<=(int)sqrt(numa);i++){
		if(numa%i==0&&numb%i==0){
			if(sosuu(i) == 2) ans++;
			g = numa / i;
			if(numb % g == 0 && sosuu(g) == 2){
				ans++;
			}
		}
	}
	return ans;
}

int main(void){
	long int A,B;
	scanf("%ld %ld",&A,&B);
	long int ans;
	if(A > B) ans = divisor(B,A);
	else ans = divisor(A,B);
	printf("%ld",ans);
	return 0;
}

//1000000000000

