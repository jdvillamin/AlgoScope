#include<stdio.h>
int main(void){

	int data[10];
	int i,j,t;

	for(i=0;i<10;i++){
		scanf("%d",&data[i]);
	}printf("\n");
	for(i=0;i<9;i++){
		for(j=0;j<9-i;j++){
			if(data[j]<data[j+1]){
				t=data[j];
				data[j]=data[j+1];
				data[j+1]=t;
			}
		}
	}
	for(i=0;i<3;i++){
		printf("%d\n",data[i]);
	}
	return 0;
}