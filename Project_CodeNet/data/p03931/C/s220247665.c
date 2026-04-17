#include <stdio.h>
int main(void){
    int n,k,ans=0;
    scanf("%d%d",&n,&k);
    int a[n];
    for (int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    for (int i=0; i<(1<<n); i++){
        int tmp=0,count=0;
        for (int j=0; j<n; j++){
            if ((1&i>>j)==1){
                tmp=tmp^a[j];
                count++;
            }
        }
        if (tmp==k){
            tmp=1;
            for (int j=1; j<=count; j++){
                tmp=tmp*j%100000007;
            }
            ans=(ans+tmp)%100000007;
        }
    }
    printf("%d\n",ans);
    return 0;
}