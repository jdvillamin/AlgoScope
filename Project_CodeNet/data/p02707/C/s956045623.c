#include<stdio.h>
int main(void)
{
  int n,i;
  int a[200001];
  int ans[200001];

  scanf("%d",&n);

  for(i=2;i<=n;i++)
    scanf("%d",&a[i]);

  for(i=2;i<=n;i++)
    ans[a[i]]++;

  for(i=1;i<=n;i++)
  printf("%d\n",ans[i]);

  return 0;
}
