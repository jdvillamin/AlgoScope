int main(){
  char a[10];
  int b=0;
  scanf("%s",a);
  for(int i=0;i<3;i++){
    if(a[i]=='7') b++;
  }
  if(b==0) printf("No");
  else printf("Yes");
  return 0;
}