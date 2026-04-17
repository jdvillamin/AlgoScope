#include<stdio.h>
#include<string.h>
int main()
{
   int i,j,temp,height[15];
   for(i=0;i<10;i++){
   scanf("%d",&height[i]);
   }
   for(i=0;i<9;i++){
   for(j=0;j<9-i;j++)
   {
   if(height[j]>height[j+1]){
   temp=height[j];
   height[j]=height[j+1];
   height[j+1]=temp;
   }
   }
    for(i=0;i<3;i++){
   printf("%d\n",height[i]);}}
    return 0;
}