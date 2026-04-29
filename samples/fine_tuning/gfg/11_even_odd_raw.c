/* Source: https://www.geeksforgeeks.org/dsa/check-whether-given-number-even-odd/ */
#include <stdio.h>
#include <stdbool.h>

bool isEven(int n)
{
    return n % 2 == 0;
}

// Driver Code
int main()
{
    int n = 15;

    if (isEven(n))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}
