/* Source: https://www.geeksforgeeks.org/dsa/find-whether-an-array-is-subset-of-another-array-set-1/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tracer.h"

void sort(int arr[], int n) {
    trace_var_init("n", n);
    trace_line(7);
    for (int i = 0; i < n-1; i++)
    {
        trace_line(7);
        trace_var_init("i", i);
        trace_line(8);
        for (int j = 0; j < n-i-1; j++)
        {
            trace_line(8);
            trace_var_init("j", j);
            trace_line(9);
            trace_array_highlight("a", j);
            trace_array_highlight("a", j+1);
            if (arr[j] > arr[j+1]) {
                trace_line(10);
                int temp = arr[j];
                trace_line(11);
                arr[j] = arr[j+1];
                trace_array("a", j, arr[j]);
                trace_line(12);
                arr[j+1] = temp;
                trace_array("a", j+1, arr[j+1]);
            }
        }
    }
}

bool isSubset(int a[], int b[], int m, int n) {
    trace_var_init("m", m);
    trace_var_init("n", n);
    trace_line(17);
    sort(a, m);
    trace_line(18);
    sort(b, n);

    trace_line(20);
    int i = 0, j = 0;
    trace_var_init("i", i);
    trace_var_init("j", j);

    trace_line(22);
    while (i < m && j < n) {
        trace_line(22);
        trace_array_highlight("a", i);
        trace_array_highlight("b", j);
        trace_line(23);
        if (a[i] < b[j]) {
            // move in a to catch up
            trace_line(25);
            i++;   
            trace_var("i", i);
        }
        else if (a[i] == b[j]) {
            trace_line(28);
            i++;
            trace_var("i", i);
            // matched one element from b
            trace_line(30);
            j++;   
            trace_var("j", j);
        }
        else {
            // a[i] > b[j] → means b[j] is missing
            trace_line(34);
            return false;
        }
    }
    
    // all b[] matched
    trace_line(39);
    return (j == n); 
}

int main() {
    int a[] = {11, 1, 13, 21, 3, 7};
    trace_array_init("a", 6);
    trace_array("a", 0, a[0]);
    trace_array("a", 1, a[1]);
    trace_array("a", 2, a[2]);
    trace_array("a", 3, a[3]);
    trace_array("a", 4, a[4]);
    trace_array("a", 5, a[5]);
    int b[] = {11, 3, 7, 1};
    trace_array_init("b", 4);
    trace_array("b", 0, b[0]);
    trace_array("b", 1, b[1]);
    trace_array("b", 2, b[2]);
    trace_array("b", 3, b[3]);
    trace_line(45);
    int m = sizeof(a)/sizeof(a[0]);
    trace_var_init("m", m);
    trace_line(46);
    int n = sizeof(b)/sizeof(b[0]);
    trace_var_init("n", n);

    trace_line(48);
    if (isSubset(a, b, m, n)) printf("true\n");
    else printf("false\n");

    trace_line(51);
    return 0;
}
