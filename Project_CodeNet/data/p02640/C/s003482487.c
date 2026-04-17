#include<stdio.h>
int main(void)
{
	int x,y,flg,t,k,i;
	scanf("%d %d",&x,&y);
	for(i=0;i<=x;i++){
		t=i;
		k=x-i;
		if(t*2+k*4==y){
			flg=1;
		}
	}
	if(flg==1){
		printf("Yes\n");
	}
	else{
		printf("No\n");
	}
	return 0;
}