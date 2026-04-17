#include <stdio.h>

#define MAX pow(10, 18)
int main(void){
	int N;
	long long int a, i, mul=1;
	scanf("%d", &N);
	for (i = 0; i < N; i++){
		scanf("%ld", &a);
		mul = a * mul;

	}
	if (mul > MAX){
		printf("-1");
	}
	else {
		printf("%ld\n",mul);
	}
	return 0;

}