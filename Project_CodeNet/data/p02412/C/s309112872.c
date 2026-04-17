#include <stdio.h>
int main(void)
{
	int h,n,x,i,j,k,m=0;
	
	for(h=1;h>0;h++)
	{
	
		scanf("%d %d",&n,&x);

	for(i=1;i<=n-2;i++)
		{

			for(j=i+1;j<=n-1;j++)
			{
			
				for(k=j+1;k<=n;k++)
				{
					if(i+j+k==x)
					{
						m++;
					}
				}
			
			}
			
	    }

	if(n==0&&x==0)
	{
		h = h*(-1);
	}
	else
	{
		printf("%d\n",m);
		
		m = 0;
	}
	
  }


	return 0;
}