#include<stdio.h>
char s[110],a[110],b,i,t;
main(){
  while(fgets(s,110,stdin),strcmp(s,".\n\0")){
    for(t=1,b=0,i=0;s[i]&&t;++i){
      if(s[i]==40||s[i]==91) a[b++]=s[i];
      else if(s[i]==41||s[i]==93) {
        if(!b){t=0;break;}
        if((s[i]==41&&a[b-1]==40)||(s[i]==93&&a[b-1]==91)) --b;
        else t=0;
      }
    }
    puts((t&&!b?1:0)?"yes":"no");
  }
}