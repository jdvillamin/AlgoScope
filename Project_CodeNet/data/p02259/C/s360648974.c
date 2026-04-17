#include<stdio.h>
void showData(int*, int);

int main()
{
	int n,i,j,tmp,count;
	scanf("%d",&n);
	int array[n];
	for(i=0; i<n; i++){
		scanf("%d",&array[i]);
	}
	
	for(i=0; i<n-1;i++){
		for(j=i+1; j<n; j++){
			if(array[i]>array[j]){
				tmp=array[i];
				array[i]=array[j];
				array[j]=tmp;
				count++;
			}
		}
	}
	showData(array,n);
	printf("%d\n",count);
	return 0;
}

void showData(int* array,int length){
	int i;
	for(i=0; i<length; i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}