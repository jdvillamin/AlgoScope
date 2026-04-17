#include <stdio.h>

int main(void)
{
    int n;
    double h, w;

    while (scanf("%d,%lf,%lf", &n, &w, &h) != EOF){
        if (w / h / h >= 25){
            printf("%d\n", n);
        }
    }

    return 0;
}