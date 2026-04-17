#include <stdio.h>
int main(void){
	char s[12];
	scanf("%s",s);
	int i,j,len=0,maxlen=0;
	for(i=0;s[i]!='\0';i++){
		if((s[i]=='A')||(s[i]=='T')||(s[i]=='C')||(s[i]=='G')){
			len++;
			for(j=1;s[i+j]!='\0';j++){
				if((s[i+j]=='A')||(s[i+j]=='T')||(s[i+j]=='C')||(s[i+j]=='G')){
					len++;
				}else{
					maxlen=(maxlen<len?len:maxlen);
					len=0;
				}
			}
		}
	}
	printf("%d",maxlen);
	return 0;
}