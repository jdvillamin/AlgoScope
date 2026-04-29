/* Source: https://www.geeksforgeeks.org/dsa/write-a-c-program-to-calculate-powxn/ */
#include <stdio.h>
#include <math.h>

double power(double b, int e) {
  
    // Initialize result to 1
    double pow = 1;

    // Multiply b for e times
    for (int i = 0; i < abs(e); i++) 
        pow = pow * b;

    if (e < 0)
        return 1 / pow;

    return pow;
}

int main() {
    double b = 3.0;
    int e = 5;
    double res = power(b, e);
    printf("%f", res);
    return 0;
}
