#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define ll long long
#define pai 3.1415926535897932384626433832795028841971693
long long min(long long a, long long b){
    if(a < b) return a;
    else return b;
}
long long max(long long a, long long b){
    if(a < b) return b;
    else return a;
}
int main(){
  char s[21];
  scanf("%s",s);
  printf("%c%c%c",s[0],s[1],s[2]);
  return 0;
}