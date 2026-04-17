#include <stdio.h>

int main(void){
	int a[10000];
	int i,n,max,min,sum;

	scanf("%d",&n);

	min=1000000;
	max=0;
	sum=0;

	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(i=0;i<n;i++){		
		sum=a[i]+sum;
	}
	for(i=0;i<n;i++){
		if(max<a[i]){
			max=a[i];
		}
	}
	for(i=0;i<n;i++){
		if(min>a[i]){
			min=a[i];
		}
	}
	printf("%d %d %d\n",min,max,sum);

	return 0;
}