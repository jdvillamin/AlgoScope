/* Source: https://www.geeksforgeeks.org/dsa/largest-rectangular-area-in-a-histogram-using-stack/ */
#include <stdio.h>
#include <stdlib.h>

// Stack structure
struct Stack {
    int top;
    int capacity;
    int* items;
};

// Function to create an empty stack with dynamic memory allocation
struct Stack* createStack(int capacity) {
    struct Stack* stack = 
                (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int value) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++(stack->top)] = value;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->items[(stack->top)--];
}

// Function to get the top element of the stack
int peek(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top];
    }
    return -1;
}

// Function to find the next smaller element for every element
void nextSmaller(int arr[], int n, int nextS[]) {
    struct Stack* stack = createStack(n);

    for (int i = 0; i < n; i++) {
        nextS[i] = n;
    }

    for (int i = 0; i < n; i++) {
        while (!isEmpty(stack) && arr[i] < arr[peek(stack)]) {
            nextS[peek(stack)] = i;
            pop(stack);
        }
        push(stack, i);
    }
}

// Function to find the previous smaller element for every element
void prevSmaller(int arr[], int n, int prevS[]) {
    struct Stack* stack = createStack(n);

    for (int i = 0; i < n; i++) {
        prevS[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        while (!isEmpty(stack) && arr[i] < arr[peek(stack)]) {
            pop(stack);
        }
        if (!isEmpty(stack)) {
            prevS[i] = peek(stack);
        }
        push(stack, i);
    }
}

// Function to calculate the maximum rectangular
// area in the Histogram
int getMaxArea(int arr[],int n) {

    int* prevS = (int*)malloc(n * sizeof(int));
    int* nextS = (int*)malloc(n * sizeof(int));
    int maxArea = 0;

    // Find previous and next smaller elements
    prevSmaller(arr, n, prevS);
    nextSmaller(arr, n, nextS);

    // Calculate the area for each arrogram bar
    for (int i = 0; i < n; i++) {
        int width = nextS[i] - prevS[i] - 1;
        int area = arr[i] * width;
        if (area > maxArea) {
            maxArea = area;
        }
    }
    return maxArea;
}

// Driver code
int main() {
    int arr[] = {60, 20, 50, 40, 10, 50, 60};
       int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", getMaxArea(arr,n));
    return 0;
}
