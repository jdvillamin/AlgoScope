#include <stdio.h>
#include <string.h>

int main(void)
{
	int a=1, b, r, x, tmp,c[3001],i,n,d[3001],y=0;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&c[i]);
	}
	memcpy(d,c,sizeof(c));
 for(i=0;i<n;i++){
 	
  x = a * c[i];
 
  if(a<c[i]){
    tmp = a;
    a = c[i];
    c[i] = tmp;
  }
  r = a % c[i];
  while(r!=0){
    a = c[i];
    c[i] = r;
    r = a % c[i];
  }
 
 a=x/c[i];
 }

	
	for(i=0;i<n;i++){
		y=y+(a-1)%d[i];
	}
	printf("%d\n",y);
 
  return 0;
}