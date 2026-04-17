#include <stdio.h>
#include <math.h>

int main(){	//Time Limit Exceeded
	int n, i, j, count1, count2;
	while(scanf("%d", &n) != EOF){
		if(n < 2){
			count2=0;
		}else{
			count2=1;
		}
		for(i=3; i<=n; i+=2){
			count1=0;
			for(j=3; j<=sqrt(i); j+=2){
				if(i%j == 0){
					count1++;
				}
				if(count1 > 0)	break;
			}
			if(count1 == 0){
				count2++;					
			}
		}
		printf("%d\n", count2);
	}
}