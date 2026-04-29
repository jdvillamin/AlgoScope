/* Source: https://www.geeksforgeeks.org/dsa/best-time-to-buy-and-sell-stock/ */
#include <stdio.h>

#include "tracer.h"

int maxProfit(int prices[], int size) {
    trace_var_init("size", size);
    trace_line(5);
    int minSoFar = prices[0];
    trace_var_init("minSoFar", minSoFar);
    trace_line(6);
    int res = 0;
    trace_var_init("res", res);

    trace_line(8);
    for (int i = 1; i < size; i++) {
        trace_line(8);
        trace_var_init("i", i);
        trace_array_cell("prices", "i", i);
        trace_array_highlight("prices", i);

        // Update the minimum value seen so far
        trace_line(11);
        if (prices[i] < minSoFar) {
            trace_line(12);
            minSoFar = prices[i];
            trace_var("minSoFar", minSoFar);
        }

        // Update result if we get more profit
        trace_line(16);
        if (prices[i] - minSoFar > res)
        {
            trace_line(17);
            res = prices[i] - minSoFar;
            trace_var("res", res);
        }
    }
    trace_line(19);
    return res;
}

int main() {
    int prices[] = {7, 10, 1, 3, 6, 9, 2};
    trace_array_init("prices", 7);
    trace_array("prices", 0, prices[0]);
    trace_array("prices", 1, prices[1]);
    trace_array("prices", 2, prices[2]);
    trace_array("prices", 3, prices[3]);
    trace_array("prices", 4, prices[4]);
    trace_array("prices", 5, prices[5]);
    trace_array("prices", 6, prices[6]);
    trace_line(24);
    int size = sizeof(prices) / sizeof(prices[0]);
    trace_var_init("size", size);
    trace_line(25);
    printf("%d\n", maxProfit(prices, size));
    trace_line(26);
    return 0;
}
