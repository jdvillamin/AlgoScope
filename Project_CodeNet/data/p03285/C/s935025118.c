#include <stdio.h>

#define CAKE 4
#define DONUT 7
int main(){
  int n;

  scanf( "%d", &n );

  if ( n < CAKE ){
    puts( "No" );// printf( "%d\n", n );
    return 0;
  }else if ( n % CAKE == 0 ){
    puts( "Yes" ); //printf( "%d\n", n % CAKE );
    return 0;
  }else if ( n % DONUT == 0 ){
    puts( "Yes" ); //printf( "%d\n", n % DONUT );
    return 0;
  }else if ( ( n % DONUT ) % CAKE == 0 ) {
    puts( "Yes" ); //printf( "%d\n", ( n % CAKE ) % DONUT );
    return 0;
  }else if ( ( n % CAKE ) % DONUT == 0 ) {
    puts( "Yes" ); //printf( "%d\n", ( n % CAKE ) % DONUT );
    return 0;
  }else 
    puts( "No" );

  return 0;
}