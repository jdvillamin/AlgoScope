#include <stdio.h>
#define N 200000
int main()
{
  int i,j;
  int n;
  int key;
  int ans=0, tmp=0;
  int count =0;
  int input;
  int data[N];

  scanf("%d",&n);
  for( i=0; i<n; i++ )
    {
      scanf("%d",&input);
      if( input >= 1 && input <= 10^9 )
	{
	  data[i] = input;
	}
    }

  for( j=0; j<n; j++ )
    {
      for( i=0; i<n; i++ )
	{
	  if(i<j){
	    if( data[j] - data[i] > 0)
	      {
		tmp = data[j]-data[i];
		if(count==0) ans = data[j]-data[i];
	      }
	    if( tmp > ans) ans = tmp;
	    count++;
	  }}
    }
      printf("%d\n",ans);

  return 0;
}