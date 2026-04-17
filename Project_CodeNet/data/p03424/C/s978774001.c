#include<stdio.h>
int main()
{
	int n,i,a=0,b=0,c=0,d=0;
	char s;

	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf(" %c ",&s);
		if(s=='P')
			a=1;
		else if(s=='W')
			b=1;
		else if(s=='G')
			c=1;
		else
			d=1;
	}
	printf("%s",(a+b+c+d==4)?"Four":"Three");
	return 0;
}