/* Source: https://www.geeksforgeeks.org/dsa/count-number-of-ways-to-cover-a-distance/ */
// C program to count number of
// ways to reach nth stair.
#include <stdio.h>

int countWays(int n) {

    // Base case for 0th and 1st stair
    if (n == 0 || n == 1)
        return 1;

    // base case for 2nd stair
    if (n == 2)
        return 2;

    // Variables to store values 
    // of previous 3 stairs.
    int prev1, prev2, prev3;

    // insert ans values for 0,1,2 stair
    prev3 = 1;
    prev2 = 1;
    prev1 = 2;

    // building dp in bottom up manner
    for (int i = 3; i <= n; i++) {
        int val = prev1 + prev2 + prev3;

        // Replace previous stair values
        // with next stairs.
        prev3 = prev2;
        prev2 = prev1;
        prev1 = val;
    }

    return prev1;
}

int main() {

    int n = 4;
    printf("%d\n", countWays(n));
    return 0;
}
