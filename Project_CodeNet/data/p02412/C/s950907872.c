#include <stdio.h>

int main(void){
    int a,b,n,x,i;
    
    for(;;){
        i=0;
        scanf("%d%d",&n,&x);
        if(n+x == 0) break;
        
        for(a=1;a<=n;a++)
            for(b=a+1;b<=n;b++)
                if(b < x-a-b && x-a-b <= n)
                    i++;
        
        printf("%d\n", i);
    }
    
    return 0;
}
