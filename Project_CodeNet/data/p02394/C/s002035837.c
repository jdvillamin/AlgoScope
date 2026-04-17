#include<stdio.h>
int main(void)
{
	int i,p,a[100][100]={0},w,h,x,y,r;
	scanf("%d %d %d %d %d\n",&w,&h,&x,&y,&r);
	for(i=0;i<=w+1;i++){
		for(p=0;p<=h+1;p++){
			a[i][p]=1;
		}
	}
	for(i=x-r;i<=x+r;i++){
		for(p=y-r;p=y+r;p++){
		
			if(i==0&&p<=h+1)
			a[i][p]++;
			else if(i<=w+1&&h==0)
			a[i][p]++;
			else if(i==w+1&&p>=1&&p>=h+1)
			a[i][p]++;
			else if(i>=1&&p==h+1&&i<=w)
			a[i][p]++;
		}
	}
	if(a[i][p]==2)
	printf("Yes\n");
	else
	printf("No\n");
	return 0;
}