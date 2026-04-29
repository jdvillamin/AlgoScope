/* Source: https://www.geeksforgeeks.org/dsa/find-the-nearest-smaller-numbers-on-left-side-in-an-array/ */
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

int* prevSmaller(int arr[], int n) {
    trace_var_init("n", n);
   
    trace_line(7);
    int* result = (int*)malloc(n * sizeof(int));
    trace_array_init("result", n);

    // stack to keep track of elements
    trace_line(10);
    int* st = (int*)malloc(n * sizeof(int));
    trace_stack_init("S");
    trace_line(11);
    int top = -1;
    trace_var_init("top", top);

    // initialize all PSEs as -1
    trace_line(14);
    for (int i = 0; i < n; i++) {
        trace_line(14);
        trace_var_init("i", i);
        trace_line(15);
        result[i] = -1;
        trace_array("result", i, result[i]);
    }

    trace_line(18);
    for (int i = 0; i < n; i++) {
        trace_line(18);
        trace_var_init("i", i);
        trace_array_highlight("arr", i);
        
        // pop elements from stack which are >= current element
        trace_line(21);
        while (top >= 0 && st[top] >= arr[i]) {
            trace_line(21);
            trace_stack_pop("S");
            trace_line(22);
            top--;
            trace_var("top", top);
        }

        // if stack is not empty, top element is PSE
        trace_line(26);
        if (top >= 0) {
            trace_line(27);
            result[i] = st[top];
            trace_array("result", i, result[i]);
            trace_stack_top("S", st[top]);
        }

        // push current element onto stack
        trace_line(31);
        st[++top] = arr[i];
        trace_var("top", top);
        trace_stack_push("S", arr[i]);
    }

    trace_line(34);
    return result;
}

int main() {
    int arr[] = {1, 5, 0, 3, 4, 5};
    trace_array_init("arr", 6);
    trace_array("arr", 0, arr[0]);
    trace_array("arr", 1, arr[1]);
    trace_array("arr", 2, arr[2]);
    trace_array("arr", 3, arr[3]);
    trace_array("arr", 4, arr[4]);
    trace_array("arr", 5, arr[5]);
    trace_line(39);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);

    trace_line(41);
    int* result = prevSmaller(arr, n);

    trace_line(43);
    for (int i = 0; i < n; i++) {
        trace_line(43);
        trace_var_init("i", i);
        trace_line(44);
        printf("%d ", result[i]);
    }
    trace_line(46);
    printf("\n");

    trace_line(48);
    return 0;
}
