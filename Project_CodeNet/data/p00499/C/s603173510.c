/*
  AOJ 0576
  Title:
  @kankichi573
*/
#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include <float.h>
// #include <stdlib.h>
int L,A,B,C,D;
int max(int a,int b)
{
        return (a>b)?a:b;

}
main()
{
        int i,j,ret;

        scanf("%d",&L);
        scanf("%d",&A);
        scanf("%d",&B);
        scanf("%d",&C);
        scanf("%d",&D);

        ret=L-max(A/C+((A%C)?1:0),B/D+((B%D)?1:0));
        printf("%d\n",ret);
  return(0);
}