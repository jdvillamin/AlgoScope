/* Source: https://www.geeksforgeeks.org/dsa/evaluation-of-postfix-expression/ */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "tracer.h"

#define MAX 100

typedef struct {
    int top;
    int arr[MAX];
} Stack;

void push(Stack *s, int val) {
    trace_var_init("val", val);
    trace_line(18);
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    trace_line(22);
    s->arr[++s->top] = val;
    trace_stack_push("S", val);
}

int pop(Stack *s) {
    trace_line(26);
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return INT_MIN;
    }
    trace_stack_pop("S");
    trace_line(30);
    return s->arr[s->top--];
}

// Check if token is an operator
bool isOperator(char *token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0
        || strcmp(token, "*") == 0 || strcmp(token, "/") == 0
        || strcmp(token, "^") == 0;
}

// Floor division for negative numbers
int floorDiv(int a, int b) {
    if (a * b < 0 && a % b != 0)
        return (a / b) - 1;
    return a / b;
}

// Evaluate postfix expression
int evaluatePostfix(char **arr, int n) {
    trace_var_init("n", n);
    trace_line(49);
    Stack s = { -1 };

    trace_line(51);
    for (int i = 0; i < n; i++) {
        trace_line(51);
        trace_var_init("i", i);

        // If it's an operand (number), push it onto the stack
        trace_line(54);
        if (isdigit(arr[i][0]) || (strlen(arr[i]) > 1 && arr[i][0] == '-')) {
            trace_line(55);
            push(&s, atoi(arr[i]));
        }

        // Otherwise, it must be an operator
        else if (isOperator(arr[i])) {
            trace_line(60);
            int val1 = pop(&s);
            trace_var_init("val1", val1);
            trace_line(61);
            int val2 = pop(&s);
            trace_var_init("val2", val2);

            trace_line(63);
            if (strcmp(arr[i], "+") == 0) push(&s, val2 + val1);
            else if (strcmp(arr[i], "-") == 0) push(&s, val2 - val1);
            else if (strcmp(arr[i], "*") == 0) push(&s, val2 * val1);
            else if (strcmp(arr[i], "/") == 0) push(&s, floorDiv(val2, val1));
            else if (strcmp(arr[i], "^") == 0) push(&s, (int)pow(val2, val1));
        }
    }
    trace_line(70);
    return pop(&s);
}

int main() {
    trace_stack_init("S");
    char *arr[] = {"2", "3", "1", "*", "+", "9", "-"};
    trace_line(75);
    int n = sizeof(arr) / sizeof(arr[0]);
    trace_var_init("n", n);
    trace_line(76);
    printf("%d\n", evaluatePostfix(arr, n));
    trace_line(77);
    return 0;
}
