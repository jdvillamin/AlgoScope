#include<stdio.h>
int main(void){
	int n;
	int i,j;
	int b[100000]={0};
	int a[100000]={0};
	if (scanf("%d", &n) == 1) {
	} else {
        printf("Failed to read integer.\n");
    }
	for(i=1;i<=n;i++){
		if (scanf("%d", &a[i]) == 1) {
		} else {
        	printf("Failed to read integer.\n");
    	}
	}
	for(j=1;j<=n;j++){
		for(i=1;i<=n;i++){
			if(j==a[i]){
				b[j]=i;
				break;
			}	
		}
	}
	for(i=1;i<=n;i++){
		printf("%d ",b[i]);
	}
	return 0;
}