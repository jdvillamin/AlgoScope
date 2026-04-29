/* Source: https://www.geeksforgeeks.org/dsa/find-the-number-occurring-odd-number-of-times/ */
#include <stdio.h>

#include "tracer.h"

// Function to find element occurring
// odd number of times
int getOddOccurrence(int ar[], int ar_size)
{
    trace_var_init("ar_size", ar_size);
    trace_line(8);
    int res = 0;
    trace_var_init("res", res);
    trace_line(9);
    for (int i = 0; i < ar_size; i++)
    {
        trace_line(9);
        trace_var_init("i", i);
        trace_array_highlight("ar", i);
        trace_line(10);
        res = res ^ ar[i];
        trace_var("res", res);
    }

    trace_line(12);
    return res;
}

int main()
{
    int ar[] = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
    trace_array_init("ar", 13);
    trace_array("ar", 0, ar[0]);
    trace_array("ar", 1, ar[1]);
    trace_array("ar", 2, ar[2]);
    trace_array("ar", 3, ar[3]);
    trace_array("ar", 4, ar[4]);
    trace_array("ar", 5, ar[5]);
    trace_array("ar", 6, ar[6]);
    trace_array("ar", 7, ar[7]);
    trace_array("ar", 8, ar[8]);
    trace_array("ar", 9, ar[9]);
    trace_array("ar", 10, ar[10]);
    trace_array("ar", 11, ar[11]);
    trace_array("ar", 12, ar[12]);
    trace_line(18);
    int n = sizeof(ar) / sizeof(ar[0]);
    trace_var_init("n", n);

    // Function calling
    trace_line(21);
    printf("%d", getOddOccurrence(ar, n));
    trace_line(22);
    return 0;
}
