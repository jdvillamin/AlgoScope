#include<stdio.h>
#include<stdlib.h>
#define MAXn 1000000
#define MAXq 1000
#define TIMEOV 50000
#define MAXMO 10
#define MAXTIME 1000000
int main(){
  int i,n,q,k,o=0,t=0;
  int time[MAXn];
  char name[MAXMO][MAXn];
  char name1[MAXMO];

  scanf("%d %d",&n,&q);
  if( n > MAXn || q > MAXq ){
    fprintf(stderr,"Error !\n");
    exit(0);
  }

  k=n;

  for( i=0 ; i<n ; i++ ){
    scanf("%s %d",&name[i][0],&time[i]);
    t = t + time[i];
  }
  
  if( t > TIMEOV ){
    fprintf(stderr,"Error !\n");
    exit(1);
  }

  while(k>0){
    for( i=0 ; i<n ; i++ ){
      if(time[i] > q){
	time[i] = time[i] - q;
	o = o+q;
      }
      if(time[i] < q && time[i] > 0){
	k--;
	time[i] = 0;
	o = o + time[i];

	printf("%s %d\n",name[i],o);
      }
    }
  }
  return 0;
}

