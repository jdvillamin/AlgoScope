#include <stdio.h>
#include <string.h>

#define N 12
#define L 14

void insert(char str[N]);
void  find(char str[N]);

char dic[N][L];
int answer[L];
int j=0;
int k=0;

int main(){
  char com[7],str[N];
  int i,n;

  scanf("%d",&n);

  for(i=0;i<n;i++){

    scanf("%s %s",com,str);
    
    if(com[0] == 'i'){
      insert(str);
    }

    else if(com[0] == 'f'){
      find(str);
    }
    else break;
  }

  for(i=0;i<k;i++){
    if(answer[i] == 1){
      printf("yes\n");
    }
    else
      printf("no\n");
  }
return 0;
}

void insert(char str[]){
  strcpy(dic[j],str);
  j++;
}

void find(char str[]){
  int i,hantei = 0;
  for(i=0;i<=j;i++){
    if((strcmp(dic[i],str)) == 0){
      hantei = 1;
      break;
    }
  }
  answer[k] = hantei;
  k++;
}

