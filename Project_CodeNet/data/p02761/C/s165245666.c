int main(void)
{
  int n, m;
  scanf("%d %d", &n, &m);
  int ans[n], i;
  for (i = 0; i < n; i++)
    ans[i] = 0;
  int s[m], c[m];
  for (i = 0; i < m; i++)
  {
    scanf("%d %d", &s[i], &c[i]);
    if ((ans[s[i] - 1] != 0 && ans[s[i] - 1] != c[i]) || (n >= 2 && s[i] == 1 && c[i] == 0))
    {
      printf("-1");
      return 0;
    }
    else
      ans[s[i] - 1] = c[i]; 
  }
  
  for (i = 0; i < n; i++)
    printf("%d", ans[i]);
}