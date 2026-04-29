/* Source: https://www.geeksforgeeks.org/dsa/stock-buy-sell/ */
#include <stdio.h>

int maxProfit(int prices[], int n) {
    int lMin = prices[0];  
    int lMax = prices[0]; 
    int res = 0;
  
    int i = 0;
    while (i < n - 1) {
      
        // Find local minima
        while (i < n - 1 && prices[i] >= prices[i + 1]) { i++; }
        lMin = prices[i];
       
        // Local Maxima
        while (i < n - 1 && prices[i] <= prices[i + 1]) { i++; }
        lMax = prices[i];
      
        // Add current profit
        res += (lMax - lMin);
    }
  
    return res;
}

// Driver Code
int main() {
    int prices[] = {100, 180, 260, 310, 40, 535, 695};
    int n = sizeof(prices) / sizeof(prices[0]);
    printf("%d\n", maxProfit(prices, n));
    return 0;
}
