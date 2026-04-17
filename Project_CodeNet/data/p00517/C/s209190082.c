#include <stdio.h>
 
int abs(int n)
{
    if (n > 0) return (n);
     
    return (n * -1);
}
 
int max(int a, int b)
{
    a = abs(a);
    b = abs(b);
     
    if (a > b) return (a);
     
    return (b);
}
 
int main(void)
{
    int i;
    int n;
    int x[3], y[3];
    int t[2];
    int sum;
     
    scanf("%d %d %d", &t[0], &t[1], &n);
     
    x[0] = y[0] = 1;
    sum = 0;
    scanf("%d %d", &x[0], &y[0]);
    for (i = 0; i < n - 1; i++){
        scanf("%d %d", &x[1], &y[1]);
         
        x[2] = x[1] - x[0];
        y[2] = y[1] - y[0];
         
        if ((x[2] > 0 && y[2] > 0) || x[2] < 0 && y[2] < 0){
            sum += max(x[2], y[2]);
        }
        else {
            sum += abs(x[2]) + abs(y[2]);
        }
         
        x[0] = x[1];
        y[0] = y[1];
    }
     
    printf("%d\n", sum);
     
    return 0;
}
