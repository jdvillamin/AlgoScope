#include<stdio.h>
int main(){
	int n,i,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		if(i%3==0){
			printf("%d ",i);
		}else{
			x=i;
			while(x>=13){
				if(x%10==3){
					printf("%d ",x);
					break;
				}else{
					x/=10;
				}
			}
		}
	}
	printf("\n");
}
				
