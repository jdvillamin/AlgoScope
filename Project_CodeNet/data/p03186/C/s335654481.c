#include <stdio.h>
int main(){
  int a,b,c,result=0;
  
  scanf("%d %d %d",&a,&b,&c);
  
  if(b>c){
    result=c*2;
    b=b-c;
    result+=b;
  } else {
    result=b*2;
    c=c-b;
    if(a>c){
      result+=c;
    } else {
      result+=a;
      c=c-a;
      if(c!=0){
        result++;
      }
    }
  }
  
  printf("%d",result);
}