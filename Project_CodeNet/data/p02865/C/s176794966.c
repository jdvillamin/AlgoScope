
#include<stdio.h>
int main()
{

    int a;
    scanf("%d", &a);
  	if(a <= 2){
      printf("0");
      return 0;
    }
  	int ans = 0;
  	if(a %2 == 0){
		ans = a/2 -1;
    }else{
      a = a+1;
      ans = a/2 -1;
    }
    
  printf("%d",ans);
    return 0;
}