/* Source: https://www.geeksforgeeks.org/dsa/find-a-tour-that-visits-all-stations/ */
#include <stdio.h>

int startStation(int gas[], int cost[], int n) {
    int startIdx = -1;
    for (int i = 0; i < n; i++) {
        
        // Current Available gas
        int currGas = 0;
        int flag = 1;
        for (int j = 0; j < n; j++) {
            
            // Circular Index
            int idx = (i + j) % n;
            currGas = currGas + gas[idx] - cost[idx];
            
            // If Available gas is less than zero, then it isn't
            // possible to proceed further with this starting point
            if (currGas < 0) {
                flag = 0;
                break;
            }
        }
      
        // If flag is true, then we have found
        // the valid starting point
        if (flag) {
            startIdx = i;
            break;
        }
    }
    
    return startIdx;
}

int main() {
    int gas[] = {4, 5, 7, 4};
    int cost[] = {6, 6, 3, 5};
    int n = sizeof(gas) / sizeof(gas[0]);
    printf("%d\n", startStation(gas, cost, n));
    return 0;
}
