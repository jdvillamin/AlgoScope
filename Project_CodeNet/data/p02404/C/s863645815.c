#include<stdio.h>
int main(void){
	int H,W,i,j;
	scanf("%d %d",&H,&W);
	for(i = 0;i < H;i++){
		if(W == 0)break;
		for(j = 1;j < W;j++){
			if (i == 0 || H == i + 1)
				{printf("#");
			}
			else if (j == 1){
				printf("#");
			}else{
				printf(".");
			}
		}
		printf("#\n");
	}
printf("\n\");
return 0;
}
