#include<stdio.h>
#include<stdlib.h>

int main(void){
        int n;
        scanf("%d", &n);
        long long  a[n+1];
        a[0] = 0;
        for(int i=1; i<=n; i++){
                scanf("%lld", &a[i]);
                a[i] += a[i-1];
        }

        long long ans = 1e18;
        for(int i=1; i<n; i++){
                long long x = llabs(a[n]-a[i]*2);
                if(x<ans) ans = x;
        }
        printf("%lld\n", ans);
        return 0;
}
