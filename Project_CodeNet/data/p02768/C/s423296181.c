#include <stdio.h>
#include <math.h>

long long factorial(long long n)
{
    long long a = 1;
    long long i;
    if (n == 0) {
        return 1;
    } else {
    for (i = 1; i <= n; i++) {
        a *= i;
    }
    return a;
    }
}

long long comb(long long a, long long b)
{
    long long c;
    c = factorial(a) / (factorial(b) * factorial(a - b));
    return c;
    }

int main(void){
    long n, a, b, num;
    scanf("%ld", &n);
    scanf("%ld", &a);
    scanf("%ld", &b);
    
    num = (long)pow(2, n) % (long)(pow(10, 9) + 7) - 1 - comb(n, a) - comb(n, b);
    printf("%ld\n", num % ((long)pow(10, 9) + 7));
    
    return 0;
}
