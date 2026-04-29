/* Source: https://www.geeksforgeeks.org/dsa/reverse-a-stack-using-recursion/ */
#include <stdio.h>
#include <stdlib.h>

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
    if (st->top == MAX - 1) return;
    st->arr[++st->top] = x;
}

// pop element
int pop(struct myStack* st) {
    if (isEmpty(st)) return -1;
    return st->arr[st->top--];
}

// get top
int peek(struct myStack* st) {
    return st->arr[st->top];
}

// function to reverse the stack
void reverseStack(struct myStack* st) {
    struct myStack aux;
    init(&aux);

    // move all elements to auxiliary stack
    while (!isEmpty(st)) {
        push(&aux, pop(st));
    }

    // replace original stack with auxiliary
    *st = aux;
}

int main() {
    struct myStack st;
    init(&st);

    push(&st, 1);
    push(&st, 2);
    push(&st, 3);
    push(&st, 4);

    reverseStack(&st);

    while (!isEmpty(&st)) {
        printf("%d ", pop(&st));
    }

    return 0;
}
