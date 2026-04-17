#include <stdio.h>

char change(char c){
  if(c>='A'&&c<='Z')return c+'a'-'A';
  return c;
}

int b_end(char W[]){
  char T[12]="END_OF_TEXT";
  int j,b=1,i;
  for(j=0; j<11; j++){
    if(T[j]!=W[j])break;
    if(j==10)b=0;
  }
  if(!b) return 1;
  else return 0;
}
int main(){
  char W[11],T[1001];
  int ans=0,i,j=0,k,b=1;
  for(i=0; i<11; i++){
    scanf("%c",&W[i]);
    W[i]=change(W[i]);
    if(W[i]=='\n')break;
  }
while(b){
    scanf("%s",&T);
    if(b_end(T)){
      b=0;
      break;
    }
    for(k=0; k<i; k++){
      T[k]=change(T[k]);
      if(T[k]!=W[k])break;
      if(k==i-1)ans+=1;
    }
    // printf("1 %s\n",T);                                                      
  }
  printf("%d\n",ans);
  return 0;
}