/* Source: https://www.geeksforgeeks.org/dsa/union-of-two-arrays/ */
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

int *findUnion(int a[], int n, int b[], int m, int *size) {
    trace_var_init("n", n);
    trace_var_init("m", m);

    // Allocate enough space for the 
    // result (maximum possible size)
    trace_line(9);
    int *res = (int *)malloc((m + n) * sizeof(int));
    trace_array_init("res", m + n);
    trace_line(10);
    int index = 0;
    trace_var_init("index", index);

    // Traverse through a[] and 
    // search every element
    trace_line(14);
    for (int i = 0; i < n; i++) {
        trace_line(14);
        trace_var_init("i", i);
        trace_array_highlight("a", i);

        // Check if the element is already
        // in the result to avoid duplicates
        trace_line(18);
        int j;
        trace_line(19);
        for (j = 0; j < index; j++) {
            trace_line(19);
            trace_var_init("j", j);
            trace_array_highlight("res", j);
            trace_line(20);
            if (res[j] == a[i])
                break;
        }
        trace_line(23);
        if (j == index) {
            trace_line(24);
            res[index++] = a[i];
            trace_array("res", index - 1, res[index - 1]);
            trace_var("index", index);
        }
    }

    // Traverse through b[] and 
    // search every element
    trace_line(30);
    for (int i = 0; i < m; i++) {
        trace_line(30);
        trace_var_init("i", i);
        trace_array_highlight("b", i);
        
        // Check if the element is already
        // in the result to avoid duplicates
        trace_line(35);
        int j;
        trace_line(36);
        for (j = 0; j < index; j++) {
            trace_line(36);
            trace_var_init("j", j);
            trace_array_highlight("res", j);
            trace_line(37);
            if (res[j] == b[i])
                break;
        }
        trace_line(39);
        if (j == index) {
            trace_line(40);
            res[index++] = b[i];
            trace_array("res", index - 1, res[index - 1]);
            trace_var("index", index);
        }
    }

    // Update the size of the result array
    trace_line(45);
    *size = index;
    trace_line(46);
    return res; 
}

int main() {
    int a[] = {1, 2, 3, 2, 1};
    trace_array_init("a", 5);
    trace_array("a", 0, a[0]);
    trace_array("a", 1, a[1]);
    trace_array("a", 2, a[2]);
    trace_array("a", 3, a[3]);
    trace_array("a", 4, a[4]);
    int b[] = {3, 2, 2, 3, 3, 2};
    trace_array_init("b", 6);
    trace_array("b", 0, b[0]);
    trace_array("b", 1, b[1]);
    trace_array("b", 2, b[2]);
    trace_array("b", 3, b[3]);
    trace_array("b", 4, b[4]);
    trace_array("b", 5, b[5]);
    trace_line(52);
    int n = sizeof(a) / sizeof(a[0]);
    trace_var_init("n", n);
    trace_line(53);
    int m = sizeof(b) / sizeof(b[0]);
    trace_var_init("m", m);
    trace_line(54);
    int size;

    trace_line(56);
    int *result = findUnion(a, n, b, m, &size);
    trace_var_init("size", size);

    trace_line(58);
    for (int i = 0; i < size; i++)
    {
        trace_line(58);
        trace_var_init("i", i);
        trace_line(59);
        printf("%d ", result[i]);
    }

    trace_line(61);
    free(result);
    trace_line(62);
    return 0;
}
