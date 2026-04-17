#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int prime(int i) {
	int k;

	if(i==1)
		return 0;

	if(i==2||i==3)
		return 1;

	for(k=2;k<=sqrt(i);k++)
		if(i%k==0) return 0;

	return 1;
}

int main() {

	int a,d,n;
	int i,count;

	for(;;) {
		scanf("%d %d %d",&a,&d,&n);
		if(!a&&!d&&!n) break;
		count=0,i=a;
		while(count<n) {
			if(prime(i)) {
				count++;
			}
			i+=d;
			//printf("%d\n",i);
		}
		printf("%d\n",i-d);
	}

	return 0;
}