/* Source: https://www.geeksforgeeks.org/gcd-in-c/ */
// C program to find GCD of two numbers
#include <math.h>
#include <stdio.h>

#include "tracer.h"

// Function to return gcd of a and b
int gcd(int a, int b)
{
    trace_var_init("a", a);
    trace_var_init("b", b);
    // Find Minimum of a and b
    trace_line(10);
    int result = ((a < b) ? a : b);
    trace_var_init("result", result);
    trace_line(11);
    while (result > 0) {
        trace_line(11);
        // Check if both a and b are divisible by result
        trace_line(13);
        if (a % result == 0 && b % result == 0) {
            trace_line(14);
            break;
        }
        trace_line(16);
        result--;
        trace_var("result", result);
    }
    // return gcd of a nd b
    trace_line(19);
    return result;
}

// Driver program to test above function
int main()
{
    trace_line(25);
    int a = 98, b = 56;
    trace_var_init("a", a);
    trace_var_init("b", b);
    trace_line(26);
    printf("GCD of %d and %d is %d ", a, b, gcd(a, b));
    trace_line(27);
    return 0;
}
// This code is contributed by Suruchi Kumari
