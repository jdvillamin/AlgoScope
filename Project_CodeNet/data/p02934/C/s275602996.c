#include<stdio.h>
int main(){
  int a;
  int n[101];
  double ans = 0.0;

  scanf("%d\n",&a);

  for (int i = 0; i < a; i++) {
    scanf("%d",&n[i]);
    ans += 1.0 / n[i];
    printf("%f\n",1.0 / ans);
  }

  return 0;
}
