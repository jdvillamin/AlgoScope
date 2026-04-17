#include <stdio.h>
#include <limits.h>

int max ( int x, int y ) {
  if ( x > y )
    return x;
  else
    return y;
}

int min ( int x, int y ) {
  if ( x > y )
    return y;
  else
    return x;
}

int main ( void ) {

  int n, t, minv;
  int maxv = INT_MIN;
  int R[200000];
  scanf( "%d", &n );
  scanf( "%d", &R[0] );
  minv = R[0];
  for ( t = 1; t < n; t++ ) {
    scanf ( "%d", &R[t] );
    maxv = max ( R[t] - minv, maxv );
    minv = min ( R[t], minv );
  }
  printf ( "%d\n", maxv );
}

