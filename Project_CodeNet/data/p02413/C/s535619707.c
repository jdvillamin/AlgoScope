#include <stdio.h>

int main(void) {
	int r,c,i,j;
	int box[101][101];
	scanf("%d %d",&r,&c);
	for(i=0;i<=r;i++){
		for(j=0;j<c;j++){
			box[i][j]=0;
		}
	}
	for(i=0;i<=r;i++){
		for(j=0;j<c;j++){
			scanf("%d",&box[i][j]);
			printf("%d ",box[i][j]);
			box[i][c] += box[i][j];
			box[r][j] += box[i][j];
		}
		printf("%d\n",box[i][c]);
	}
	for(j=0;j<c;j++){
		printf("%d ",box[r][j]);
		box[r][c] += box[r][j];
	}
	printf("%d\n",box[r][c]);
	return 0;
}