#include <stdio.h>
#include <math.h>

#define MIN 0
#define MAX 2*pow(10,9)

int main(void){
  int L,R,i,j,n;
  int nmin=0;
  scanf("%d%d",&L,&R);
  if(L<MIN) return 0;
  if(R>MAX) return 0;
  n=L*R;
  if(n<=2018){
    printf("%d",n);
  } else{
    j=L+1;
    for(i=L;i<j;i++){
      for(j=i+1;j<=R;j++){
	n=(i*j)%2019;
	if(nmin>=n)
	  nmin=n;
	if(nmin==0){
	  printf("%d",nmin);
	  return 0;
	}
      }
    }	  
    printf("%d",nmin);
  }
  return 0;
}
