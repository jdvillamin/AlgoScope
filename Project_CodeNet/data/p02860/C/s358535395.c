#include<stdio.h>
#include<string.h>
int main()
{
	int n,i;
	char a[100]={};
	char b[100]={};
	while(~scanf("%d",&n)){
		getchar();
		if(n%2){
			for(i=0;i<n;i++)
				scanf("%c",&a[i]);
			printf("No\n");
		}else{
			for(i=0;i<n/2;i++)
			scanf("%c",&a[i]);
			for(i=0;i<n/2;i++)
				scanf("%c",&b[i]);
			if(strcmp(a,b)==0)
				printf("Yes\n");
			else
				printf("No\n");
		}		
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
	}
}