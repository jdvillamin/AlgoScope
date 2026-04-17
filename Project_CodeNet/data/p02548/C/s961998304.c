#include<stdio.h>
int main(){
	int i,n,ans=0;
	scanf("%d",&n);
	for (i=1;i<n;i++) ans+=(n-1)/i;/*n>1; if n%i==0 => c==0 but c>0, thats why n-1
    								c==(n-1)%i+1*/
	printf("%d\n",ans);
	return 0;
}
