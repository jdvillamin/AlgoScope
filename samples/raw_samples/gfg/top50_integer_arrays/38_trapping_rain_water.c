/* Source: https://www.geeksforgeeks.org/dsa/trapping-rain-water/ */
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int *array;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is -1
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to add an item to stack
void push(struct Stack* stack, int item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack
int pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

// Function to return the top from the stack without popping
int top(struct Stack* stack) {
    return stack->array[stack->top];
}

int maxWater(int* arr, int n) {

    struct Stack* st = createStack(n);
    int res = 0;

    for (int i = 0; i < n; i++) {
       
        // Pop all items smaller than arr[i]
        while (!isEmpty(st) && arr[top(st)] < arr[i]) {          
            
            int pop_height = arr[pop(st)];

            if (isEmpty(st))
                break;

            // arr[i] is the next greater for the removed item
            // and new stack top is the previous greater 
            int distance = i - top(st) - 1;

            // Take the minimum of two heights (next and prev greater)
            int water = (arr[top(st)] < arr[i]) ? arr[top(st)] : arr[i];

            // Find the amount of water
            water -= pop_height;
            
            res += distance * water;
        }
        push(st, i);
    }
    free(st->array);
    free(st);
    return res;
}

int main() {
    int arr[] = {2, 1, 5, 3, 1, 0, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", maxWater(arr, n));
    return 0;
}
