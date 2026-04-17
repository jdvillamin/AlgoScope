#include <stdio.h>

int main(void)
{
    int n=0,m=0,flag=1;
    int s[5]={},c[5]={},num[5]={10,10,10,10,10},numflag[5]={};
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d %d",&s[i],&c[i]);
    }
    if(n==1){
        for(int i=0;i<m;i++){
            if(s[i]==1 && numflag[0]==0){
                num[0]=c[i];
                numflag[0]=1;
            }
            if((s[i]==1 && num[0]!=c[i]) || s[i]!=1){
                flag=0;
                break;
            }
        }
    } else {
        for(int i=0;i<m;i++){
            if(s[i]==1){
                if(numflag[0]==0 && c[i]!=0){
                    num[0]=c[i];
                    numflag[0]=1;
                } else {
                    if(num[0]!=c[i]){
                        flag=0;
                        break;
                    }
                }
            } else {
                if(numflag[s[i]-1]==0){
                    num[s[i]-1]=c[i];
                    numflag[s[i]-1]=1;
                } else {
                    if(num[s[i]-1]!=c[i]){
                        flag=0;
                        break;
                    }
                }
            }
        }
    }

    if(flag==1 && numflag[0]==1){
        for(int i=0;i<n;i++){
            if(numflag[i]==1) printf("%d",num[i]);
            else printf("0");
        }
    } else {
        printf("-1");
    }
    return 0;
}
