#include <stdio.h>

int main(void){
  int n;
  int a[1000];
  
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    scanf("%d ", a[i]);
  }
  
  for(int i=0; i<n; i++){
    if(a[i]%2 == 0){
      if(a[i]%3 != 0 && a[i]%5 != 0){
        printf("DENIED");
        return 0;
      }
    }
  }
  printf("APPROVED");
  return 0;
}