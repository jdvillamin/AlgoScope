#include<stdio.h>
int main (void)
{
	int x[10000],y[10000],empty,i=0,j;
	do {
		scanf("%d %d",&x[i],&y[i]);
		if(x[i]>y[i]){
			empty=x[i];
			x[i]=y[i];
			y[i]=empty;
		}
		i++;
	}while(x[i-1]!=0 && y[i-1]!=0);
	for(j=0;j<i-1;j++){
	printf("%d %d\n",x[j],y[j]);
	}
	return 0;
}