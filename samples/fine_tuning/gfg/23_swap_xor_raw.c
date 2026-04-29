/* Source: https://www.geeksforgeeks.org/dsa/swap-two-numbers-without-using-temporary-variable/ */
// C Code to swap two numbers using bitwise XOR
#include <stdio.h>

int main() {
    int a = 10, b = 20;
    
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    
    printf("%d %d\n", a, b);
    return 0;
}
