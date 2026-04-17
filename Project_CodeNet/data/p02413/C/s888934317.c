#include<stdio.h>
int main(void){
	int r,c,i,j,a[101][101],b=0;
	scanf("%d %d",&r,&c);
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			scanf("%d",&a[i][j]);
			a[i][c+1]+=a[i][j];
			a[r+1][j]+=a[i][j];
			b+=a[i][j];
		}
	}
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			printf("%d ",a[i][j]);
		}
		printf("%d\n",a[i][j+1]);
	}
	for(j=0;j<c;j++){
		printf("%d ",a[r+1][j]);
	}
	printf("%d\n",b);
	return 0;
}