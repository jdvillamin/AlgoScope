#include<stdio.h>
int main(void)
{
	int a,b,c,n=0,i,j;
	scanf("%d %d %d",&a,&b,&c);
	for(i=1;i<c;i++){
		if(c%i==0){
			for(j=a;j<=b;j++){
				if(i==j){
					n++;
				}
			}
		}
	}
	printf("%d\n",n);
	return 0;
}