/* Source: https://www.geeksforgeeks.org/dsa/check-for-prime-number/ */
#include <stdio.h>
#include <stdbool.h>

#include "tracer.h"

bool isPrime(int n) {
    trace_var_init("n", n);
    trace_line(6);
    if (n <= 1)
        return false;

    // Check divisibility from 2 to n-1
    trace_line(10);
    for (int i = 2; i < n; i++)
    {
        trace_line(10);
        trace_var_init("i", i);
        trace_line(11);
        if (n % i == 0)
            return false;
    }

    trace_line(14);
    return true;
}

int main() {
    trace_line(18);
    int n = 7;
    trace_var_init("n", n);
    trace_line(19);
    if( isPrime(n)) printf("%s","true");
  	else printf("%s","false");
    trace_line(21);
    return 0;
}
