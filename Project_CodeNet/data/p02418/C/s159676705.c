#include <stdio.h>
#include <string.h>

int main(){
    char s[100],p[100];
    int i,k,cnt[100]={0},result=0,ls,lp,d,n;
    scanf("%s", p);
    scanf("%s", s);
    lp=strlen(p);
    ls=strlen(s);
    //printf("%d,%d",lp,ls);
    for(i=0;i<lp+ls;i++){
        n=i%lp;
        for(k=0;k<ls;k++){
            if(i>=k&&p[n]==s[k]){
                cnt[i-k]++;
                //printf("%d:%d\n",i-k,cnt[i-k]);
            }
        }
    }
    for(i=0;i<lp;i++){
        if(cnt[i]==ls)result=1;
    }
    if(result)printf("Yes\n");
    else printf("No\n");
    return 0;
}