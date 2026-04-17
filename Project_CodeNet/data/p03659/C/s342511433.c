#include <stdio.h>
#include <stdlib.h>
	int main(){
		int n;
		scanf("%d",&n);
		int a[200000],x,y,min;
		long sum;
		sum = 0;
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
			sum = sum + a[i];
		}
		x = 0;
		min = abs(sum - 2*a[0]);
		for(int i=0;i<n-1;i++){
			x = a[i] + x;
			if( abs(sum - 2*x) < min){
				min = abs(sum - 2*x);
			}
		}
		printf("%d",min);
		return 0;
	}