#include <stdio.h>

int main(void){
    int n,k;
    int ans=0;
    scanf("%d %d",&n,&k);
    for(int a=1;a<=n;a++){
        for(int b=1;b<=n;b++){
            if(!((a+b)%k==0)){
                continue;
            }else{
                for(int c=1;c<=n;c++){
                    if(!((b+c)%k==0)){
                        continue;
                    }else{
                        if((c+a)%k==0){
                            ans++;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}