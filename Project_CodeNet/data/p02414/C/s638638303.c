#include<stdio.h>

int main(void)
{
	int n,m,l,i,j,k;
	int a[100][1000]={0,};
	int b[100][100]={0,};
	int c[100][100]={0,};

	scanf("%d %d %d",&n,&m,&l);

	for(j=0;j<n;j++){
		for(i=0;i<m;i++){
			scanf("%d",&a[i][j]);
		}
	}
	for(j=0;j<m;j++){
		for(i=0;i<l;i++){
			scanf("%d",&b[i][j]);
		}
	}
	for(k=0;k<n;k++){
		for(j=0;j<m;j++){
			for(i=0;i<l;i++){
				c[i][k]+=a[j][k]*b[i][j];
			}
		}
	}
	
	for(j=0;j<n;j++){
		for(i=0;i<l;i++){
			if(i!=0) printf(" ");
			printf("%d",c[i][j]);
		}
		printf("\n");
	}


	return 0;	
}	