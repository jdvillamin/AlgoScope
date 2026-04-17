#include<stdio.h>
#include<string.h>
double dp[101][101]={0},g[101][101],r;
int n,m,i,j,k;

int main()
{
	for(;scanf("%d%d",&n,&m),n;)
	{
		memset(dp,0,sizeof(dp));
		for(i=0;i<n*n;i++)
			scanf("%lf",&g[i/n][i%n]);
		for(i=0;i<n;i++)
			dp[0][i]=1.0;
		for(i=0;i<m;i++)
			for(j=0;j<n;j++)
				for(k=0;k<n;k++)
					dp[i+1][k]=dp[i+1][k]>dp[i][j]*g[j][k]?dp[i+1][k]:dp[i][j]*g[j][k];
		for(i=r=0;i<n;i++)
			r=r>dp[m-1][i]?r:dp[m-1][i];
		printf("%.2f\n",r);
	}
	return 0;
}