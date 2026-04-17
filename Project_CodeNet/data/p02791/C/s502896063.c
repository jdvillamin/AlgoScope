#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	int n, i, j, min;
	int *num = NULL;
	int cnt = 0;
	bool minFlag;
	
	scanf("%d", &n);
	
	num = (int *)malloc(sizeof(int)*n);
	
	for(i=0; i<n; ++i){
		minFlag = false;
		scanf("%d", &num[i]);
		if(i==0 || min >= num[i]){
			min = num[i];
			++cnt;
			minFlag=true;
		}
		
		if(!minFlag){
			for(j=0; j<i; ++j){
				if(num[i]>num[j])
				break;
			}
			if(i==j){
				++cnt;
			}
		}
	}
	printf("%d", cnt);
	
	free(num);
	
	return 0;
}