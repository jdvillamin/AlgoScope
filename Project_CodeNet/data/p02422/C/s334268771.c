#include<stdio.h>
#include<string.h>

int main()
{
	int q,a,b,i,j,s;
	char str[1001];
	char meirei[8];
	char p[1000];
	
	scanf("%s",str);
	scanf("%d",&q);
	
	for(i=0;i<q;i++)
	{
		scanf("%s %d %d",meirei,&a,&b);
		if(meirei[2] == 'p'){
			scanf("%s",p);
			
			for(j=a;j<=b;j++){
				str[j]=p[j-a];
			}
		}else if(meirei[2] == 'v'){
			
			for(j=a;j<=(a+b)/2;j++){
				int temp = str[j];
				str[j] = str[b-(j-a)];
				str[b-(j-a)] = temp;
			}
		} else if(meirei[2] == 'i'){
			
			for(j=a;j<=b;j++){
				putchar(str[j]);
		
			}
			putchar('\n');
		}
	}
		
	return 0;
}
