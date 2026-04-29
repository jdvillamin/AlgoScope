/* Source: https://www.geeksforgeeks.org/dsa/fizz-buzz-implementation/ */
#include <stdio.h>
#include <stdlib.h>

void fizzBuzz(int n) {
    for (int i = 1; i <= n; ++i) {
        // Check if i is divisible by both 3 and 5
        if (i % 3 == 0 && i % 5 == 0) {
            // Print "FizzBuzz"
            printf("FizzBuzz ");
        } 
        // Check if i is divisible by 3
        else if (i % 3 == 0) {
            // Print "Fizz"
            printf("Fizz ");
        } 
        // Check if i is divisible by 5
        else if (i % 5 == 0) {
            // Print "Buzz"
            printf("Buzz ");
        } 
        else {
            // Print the current number
            printf("%d ", i);
        }
    }
}

int main() {
    int n = 20;
    fizzBuzz(n);
    return 0;
}
