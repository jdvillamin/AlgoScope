/* Source: https://www.geeksforgeeks.org/dsa/intersection-of-two-arrays/ */
#include <stdio.h>

#include "tracer.h"

void intersect(int a[], int n1, int b[], 
            int n2, int res[], int *res_size) {
    trace_var_init("n1", n1);
    trace_var_init("n2", n2);
  
    // Traverse through a[] and 
    // search every element a[i] in b[]
    trace_line(9);
    for (int i = 0; i < n1; i++) {
        trace_line(9);
        trace_var_init("i", i);
        trace_array_highlight("a", i);
        trace_line(10);
        for (int j = 0; j < n2; j++) {
            trace_line(10);
            trace_var_init("j", j);
            trace_array_highlight("b", j);

            // If found, check if the element 
            // is already in the result
            trace_line(14);
            int found = 0;
            trace_var_init("found", found);
            trace_line(15);
            if (a[i] == b[j]) {
                trace_line(16);
                for (int k = 0; k < *res_size; k++) {
                    trace_line(16);
                    trace_var_init("k", k);
                    trace_array_highlight("res", k);
                    trace_line(17);
                    if (res[k] == a[i]) {
                        trace_line(18);
                        found = 1;
                        trace_var("found", found);
                        trace_line(19);
                        break;
                    }
                }
                trace_line(22);
                if (!found) {
                    trace_line(23);
                    res[(*res_size)++] = a[i];
                    trace_array("res", *res_size - 1, res[*res_size - 1]);
                }
            }
        }
    }
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
    int res[10];
    trace_array_init("res", 10);
    trace_line(34);
    int res_size = 0;
    trace_var_init("res_size", res_size);

    trace_line(36);
    intersect(a, 5, b, 6, res, &res_size);

    trace_line(38);
    for (int i = 0; i < res_size; i++) {
        trace_line(38);
        trace_var_init("i", i);
        trace_line(39);
        printf("%d ", res[i]);
    }

    trace_line(42);
    return 0;
}
