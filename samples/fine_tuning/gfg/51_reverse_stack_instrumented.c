/* Source: https://www.geeksforgeeks.org/dsa/reverse-a-stack-using-recursion/ */
#include <stdio.h>
#include <stdlib.h>

#include "tracer.h"

#define MAX 100

// stack structure
struct myStack {
    int arr[MAX];
    int top;
};

// initialize stack
void init(struct myStack* st) {
    st->top = -1;
}

// check empty
int isEmpty(struct myStack* st) {
    return st->top == -1;
}

// push element
void push(struct myStack* st, int x) {
    trace_var_init("x", x);
    trace_line(25);
    if (st->top == MAX - 1) return;
    trace_line(26);
    st->arr[++st->top] = x;
    trace_stack_push("S", x);
}

// pop element
int pop(struct myStack* st) {
    trace_line(31);
    if (isEmpty(st)) return -1;
    trace_stack_pop("S");
    trace_line(32);
    return st->arr[st->top--];
}

// get top
int peek(struct myStack* st) {
    return st->arr[st->top];
}

// function to reverse the stack
void reverseStack(struct myStack* st) {
    trace_line(42);
    struct myStack aux;
    trace_line(43);
    init(&aux);

    // move all elements to auxiliary stack
    trace_line(46);
    while (!isEmpty(st)) {
        trace_line(46);
        trace_line(47);
        push(&aux, pop(st));
    }

    // replace original stack with auxiliary
    trace_line(51);
    *st = aux;
}

int main() {
    struct myStack st;
    trace_line(56);
    init(&st);
    trace_stack_init("S");

    trace_line(58);
    push(&st, 1);
    trace_line(59);
    push(&st, 2);
    trace_line(60);
    push(&st, 3);
    trace_line(61);
    push(&st, 4);

    trace_line(63);
    reverseStack(&st);

    trace_line(65);
    while (!isEmpty(&st)) {
        trace_line(65);
        trace_line(66);
        printf("%d ", pop(&st));
    }

    trace_line(69);
    return 0;
}
