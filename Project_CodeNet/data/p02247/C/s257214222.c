#include <stdio.h>
#include <string.h>

#define N 1000

int main(){
	
	int i;
	int count=0;
	int ans[N];
	int str_length;
	int cmp_length;
	char str[N];
	char cmp[N];
	
	scanf("%s %s",str,cmp);
	
	str_length = strlen(str);
	cmp_length = strlen(cmp);
	
	 for(i=0;i<str_length;i++){
	if( strncmp(str+i,cmp,cmp_length) ==0 ){
	ans[count] = i;
	count++;
	 }
	}
	
	if(count!=0){
	for(i=0;i<count;i++){
	printf("%d\n",ans[i]);
	 }
	}
	
	else printf("\n");
	
	return 0;
}