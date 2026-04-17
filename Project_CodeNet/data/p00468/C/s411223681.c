  int main(){
while(1){int n,m,i,j,a,b,x[501]={},c[501][501]={},num[501]={},sum=0;
  scanf("%d%d",&n,&m); if(n==0) break; for(i=1;i<=m;i++){scanf("%d %d",&a,&b); if(a==1){ num[b]++;}c[a][b]++;
  c[b][a]++;} for(i=1;i<=n;i++){for(j=1;j<=n;j++){
 if(c[1][i]==1 && c[i][j]==1){num[j]++;}}}
for(i=2;i<=n;i++){if(num[i]!=0) sum++;}
printf("%d\n",sum);return 0;}