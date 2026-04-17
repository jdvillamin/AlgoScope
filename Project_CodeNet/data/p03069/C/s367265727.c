#include<stdio.h>

int main(){
	int n,i,a=0,b=0;
	char s[200001],t[200001];
	scanf("%d%s",&n,s);
	for(i=0;i<n;i++)t[i]=s[i];
	int ff=0;
	for(i=0;i<n;i++){
		if(s[i]=='#')ff=1;
		if(s[i]=='.'&&ff==1){
			a++;
		}
	}int f=0;
	for(i=n-1;i>=0;i--){
		if(t[i]=='.')f=1;
		if(t[i]=='#'&&f==1){
			b++;
		}
	}
	printf("%d\n",a>b?b:a);
	return 0;
}