/* Source: https://www.geeksforgeeks.org/dsa/count-trailing-zeroes-factorial-number/ */
#include <stdio.h>

int trailingZeroes(int n)
{
    // Edge Case
    if (n < 0)
        return -1;

    // Initialize result
    int count = 0;

    // Keep dividing n by powers of
    // 5 and update count
    for (int i = 5; n / i >= 1; i *= 5)
        count += n / i;

    return count;
}

int main()
{
    int n = 10;
    printf("%d\n", trailingZeroes(n));
    return 0;
}
