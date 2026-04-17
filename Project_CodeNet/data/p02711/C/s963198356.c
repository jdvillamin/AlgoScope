#include<stdio.h>

int main() {
  int n;
  scanf("%d",&n);
  int j,k,l;
  j = n/100;
  n %= 100;
  k = n/10;
  n %= 10;
  l = n;
  if(j == 7 || k == 7 || l == 7) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }
}
