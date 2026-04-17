#include <stdio.h>
#include <math.h>


int main(void)
{
    int X, ans;
    int i;
    scanf("%d", &X);
    ans=1;
    if(X == 1) {
        ans = 1;
    }else {
        i = 2;
        while (pow((double)X,1.0/(double)i)-2.0>=0.0) {
            if(pow((int)(pow((double)X,1.0/(double)i)),i) > ans) {
                ans = pow((int)(pow((double)X,1.0/(double)i)), i);        
            }
            i++;
        }
    }
    printf("%d\n", ans);
    return 0;
}