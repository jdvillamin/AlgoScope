#include<stdio.h>
int main(void){
    int h,w,i,j;
    while(1){
        scanf("%d%d",&h,&w);
        if(h==0&&w==0){
            break;
        }
        for(i=0;i<h;i=i+1){
            for(j=0;j<w;j=j+1){
                printf("#");
            }
            printf("\n");
        }
    }
return 0;
}