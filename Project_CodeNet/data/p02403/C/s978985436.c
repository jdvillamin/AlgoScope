#include<stdio.h>
main(void)
{
int H, W, i, j;

while(1){
scanf("%d %d", &H, &W);
if(H == 0 && W == 0)break;

for(i = 0; i < W; i++){

for(j = 0; j < H; j++){
printf("#");
}
printf("\n");
}




return 0;
}
