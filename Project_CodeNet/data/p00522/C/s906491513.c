#include<stdio.h>

int main(void){
	int m,n,p[10000],c[2][10000],v[10000],profit;
	profit=0;
	scanf("%d %d",&m,&n);
	int i,j,k,temp,temp0,temp1;
	for(i=0;i<m;i++){
		scanf("%d",&p[i]);
	}
	for(i=0;i<n;i++){
		scanf("%d %d",&c[0][i],&c[1][i]);
	}
	for(i=0;i<n;i++){
		v[i]=c[1][i]/c[0][i];
	}
	for(i=0;i<m;i++){
		for(j=m-1;j>i;j--){
			if(p[j-1]>p[j]){
				temp=p[j-1];
				p[j-1]=p[j];
				p[j]=temp;
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=n-1;j>i;j--){
			if(v[j-1]>v[j]){
				temp=v[j-1];
				v[j-1]=v[j];
				v[j]=temp;
				temp0=c[0][j-1];
				temp1=c[1][j-1];
				c[0][j-1]=c[0][j];
				c[1][j-1]=c[1][j];
				c[0][j]=temp0;
				c[1][j]=temp1;
			}
		}
	}
	temp=0;
	for(i=0;i<c[0][0];i++){
		temp=temp+p[m-1-i];
	}
	i=0;
	k=m-1;
	while(temp>=c[1][i]){
		for(j=0;j<c[0][i];j++){
			profit=profit+p[k];
			k--;
		}
		profit=profit-c[1][i];
		i++;
		temp=0;
		for(j=0;j<c[0][i];i++){
			temp=temp+p[k-i];
		}
	}
	printf("%d\n",profit);
	return 0;
}