#include <stdio.h>
int main(void){
	int r,c,i,j;
	scanf("%d %d",&r,&c);
	int a[100+1][100+1]={};
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			printf("%d ",a[i][j]);
			a[i][c]=a[i][c]+a[i][j];
		}
		printf("%d",a[i][c]);
		putchar('\n');
		a[i][c]=0;
	}
	for(j=0;j<c;j++){
		for(i=0;i<r;i++){
			a[r][j]=a[r][j]+a[i][j];
			a[r][c]=a[r][c]+a[i][j];
		}
		printf("%d ",a[r][j]);
		
	}
	printf("%d ",a[r][c]);
	return 0;
}

