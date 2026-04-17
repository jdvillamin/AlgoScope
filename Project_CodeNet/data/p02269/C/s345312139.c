#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define n_max 1000

int main(){
  int n,i,j=0,k,F,len1,len2,l;
  char st[n_max][12],c1[n_max][12],c2[n_max][12];
  
  scanf("%d",&n);
  
  for(i=0;i<n;i++)
    scanf("%s %s",&c1[i],&c2[i]);
  
  for(i=0;i<n;i++){
    if(c1[i][0]=='i'){
      strcpy(st[j],c2[i]);
      j++;
    }
    len2=strlen(c2[i]);
    if(c1[i][0]=='f'){
      F=0;
      for(k=0;k<j;k++){
	len1=strlen(st[k]);
	if(len1==len2){
	  for(l=0;l<len1;l++){
	    if(st[k][l]!=c2[i][l]){
	      break;
	    }
	    else if(l==len1-1){
	      printf("yes\n");
	      F=1;
	      break;
	    }
	  }
	}
      }
	if(F==0) printf("no\n");
    }
  }
  return 0;
}

