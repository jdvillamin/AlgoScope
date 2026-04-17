#include<stdio.h>
int main(){
	int x,y,i;
	char s[15];
	scanf("%d %s %d",&x,s,&y);
	for(i=0;i<x;i++){
		if(s[i]!=s[y-1])s[i]='*';
	}
	puts(s);
	
	
} 