#include<stdio.h>
int d[11];
int N=0;
void f(int B,int C,int n,int j){
	if(n>9)return ;
	if(j){if(B>d[n])return;B=d[n];}
	else {if(C>d[n])return;C=d[n];}
	if(n>N)N=n;
	f(B,C,++n,0);
	n--;
	f(B,C,++n,1);
}
int main(){
	int n,i,j;
	scanf("%d",&n);
	for(j=0;j<n;j++){
		N=0;
		for(i=0;i<10;i++)scanf("%d",&d[i]);
		f(0,0,0,0);
		if(N!=9){N=0;f(0,0,0,1);}
		if(N==9)printf("YES\n");
		else printf("NO\n");
	}exit(0);
}