#include<stdio.h>

int main(){
  int tou;
  int kai;
  int situ;
  int t[4][3][10];
  int n,c,i,j,k;
  
  scanf("%d",&c);
  
  for(i=0;i>=0;i++){
    for(j=0;j<3;j++){
      for(k=0;k<10;k++){
    t[i][j][k]=0;}}
  if(i==3){
    break;}}
  
  for(i=0;i<c;i++){
    scanf("%d %d %d %d",&tou,&kai,&situ,&n);
    t[tou-1][kai-1][situ-1]=n;}

  for(i=0;i>=0;i++){
    for(j=0;j<3;j++){
      for(k=0;k<10;k++){
      printf(" %d",t[i][j][k]);}
    printf("\n ");}
  if(i==3){
    break;}
  printf("####################\n");}
return 0;
}
