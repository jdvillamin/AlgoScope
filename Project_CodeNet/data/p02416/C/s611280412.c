#include<stdio.h>
#include<string.h>

int main(){
  int i,k,sum=0;
  char numbers[1001];

  while(1){
    scanf("%s",&numbers);
    if(numbers[0]==48){break;}
    else{
      k=strlen(numbers);
      for(i=0; i<k; i++){
        sum=sum + (numbers[i]-48);
      }
      printf("%d\n",sum);
      break;
    }
  }

  return 0;
}