#include <stdio.h>

int main(void){
	int num;
	int a;
	int max=0;
	int cnt=0;
	int i;
	
	scanf("%d",&num);
	for(i=0;i<num;i++){
		scanf("%d",&a);
		if(max<a)
			max=a;
		else
			cnt++;
		if(!i)
			cnt++;
	}
	printf("%d\n",cnt);
		
	return 0;
}