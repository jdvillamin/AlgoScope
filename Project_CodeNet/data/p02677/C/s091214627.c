/* ex4_1
   YSK722 */

#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979

int main(void){
    double short_hand, long_hand, hour, minute, ans;
    scanf("%lf %lf %lf %lf", &short_hand, &long_hand, &hour, &minute);
    /* 余弦定理を用いる
       cos(-x) = cos(x)より、回転角の大小は考えない */
    ans = double sqrt(pow(short_hand, 2) + pow(long_hand, 2) \
        - 2 * short_hand * long_hand * double cos(PI(hour/6 - minute/30)));
    printf("%lf", ans);
}