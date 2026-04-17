#include<stdio.h>
main(){
  char s[1020][1020];
  int n,i,j,k,max=0,l,a,flg;
  scanf("%d",&n);
  if(n==0)return 0;
  for(i=0;i<n;i++){
    scanf("%s",s[i]);
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(s[i][j]=='.'){
	for(k=0;i+k<=n&&j+k<=n;k++){
	  for(l=i;l<i+k;l++){
	    for(a=j;a<j+k;a++){
	      if(s[l][a]=='*'){
		goto exit;
	      }
	    }
	  }
	}
      exit:
	if(max<k-1)max=k-1;
      }
    }
  }
  printf("%d\n",max);
  return main();
}