#include<stdio.h>

int x[10000];
int i;

int main(void){
	
	for(i=1;i<=10000;i++){
		scanf("%d",&x[i]);
		if(x[i] == 0){
			break;
		}
	}
	
	for(i=1;i<=10000;i++){
		printf("Case %d: %d\n",i,x[i]);
		if(x[i+1] == 0){
			break;
		}
	}
		return 0;
	}
	