#include <stdio.h>
#include <math.h>
#define DATANUMBER 300000
 
int main(void) {
	long long  N,i,j,sum;
	long long A[DATANUMBER+1];
 
	
	scanf("%lld",&N);
	for(i=1;i<=N;i++){
		scanf("%lld",&A[i]);
	}
	sum=0;
	for(i=1;i<=N;i++){
		for(j=i+1;j<=N;j++){
			A[i]=A[i]%(long long)(pow(10,9)+7);
			A[j]=A[j]%(long long)(pow(10,9)+7);
			sum+=(A[i]*A[j])%(long long)(pow(10,9)+7);
          	sum=sum%(long long)(pow(10,9)+7);
		}
	}
	printf("%lld",sum);
	return 0;
 
}