/* Source: https://www.geeksforgeeks.org/dsa/fizz-buzz-implementation/ */
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

void fizzBuzz(int n) {
    trace_var_init("n", n);
    trace_line(6);
    for (int i = 1; i <= n; ++i) {
        trace_line(6);
        trace_var_init("i", i);
        // Check if i is divisible by both 3 and 5
        trace_line(8);
        if (i % 3 == 0 && i % 5 == 0) {
            // Print "FizzBuzz"
            trace_line(10);
            printf("FizzBuzz ");
        }
        // Check if i is divisible by 3
        else if (i % 3 == 0) {
            // Print "Fizz"
            trace_line(15);
            printf("Fizz ");
        }
        // Check if i is divisible by 5
        else if (i % 5 == 0) {
            // Print "Buzz"
            trace_line(20);
            printf("Buzz ");
        }
        else {
            // Print the current number
            trace_line(24);
            printf("%d ", i);
        }
    }
}

int main() {
    trace_line(30);
    int n = 20;
    trace_var_init("n", n);
    trace_line(31);
    fizzBuzz(n);
    trace_line(32);
    return 0;
}
