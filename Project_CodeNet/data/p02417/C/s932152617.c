#include<stdio.h>
#define MAX 1200
int main(){
	int i,j,cnt[26];
	char ss[MAX+1];
	gets(ss);
	for(i=0; i<MAX+1; i++){
		if(ss[i]=='\0'){break;}
		for(j=0; j<26; j++){
			if((ss[i]==65+j) || (ss[i]==97+j)){cnt[j]+=1;}
		}
	}
	for(i=0; i<26; i++){
		printf("%c : %d\n", 97+i,cnt[i]);
	}
	return 0;
}