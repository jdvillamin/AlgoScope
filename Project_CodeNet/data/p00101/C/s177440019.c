#include<string.h>
int main(){
  int i,j,n,flag=0;
  char a[1000]={0};

  scanf("%d",&n);
  for(j=0;j<n;j++){
flag=0;
    scanf("%s",a);
    for(i=0;a[i]!=0;i++){
      if(flag==0){
        if(a[i]=='H')flag++;
      }
      else if(flag==1){
        if(a[i]=='o')flag++;
        else if(a[i]=='H')flag=1;
        else flag=0;
      }
      else if(flag==2){
        if(a[i]=='s')flag++;
        else if(a[i]=='H')flag=1;
        else flag=0;
      }
      else if(flag==3){
        if(a[i]=='h')flag++;
        else if(a[i]=='H')flag=1;
        else flag=0;
      }
      else if(flag==4){
        if(a[i]=='i')flag++;
        else if(a[i]=='H')flag=1;
        else flag=0;
      }
      else if(flag==5){
        if(a[i]=='n')flag++;
        else if(a[i]=='H')flag=1;
        else flag=0;
      }
      else if(flag==6){
        if(a[i]=='o')a[i]='a';
        else if(a[i]=='H')flag=1;
        else flag=0;
      }
    }
    for(i=0;a[i]!=0;i++)printf("%c",a[i]);puts("");
    for(i=0;a[i]!=0;i++)a[i]=0;
  }
  return 0;
}