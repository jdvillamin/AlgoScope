/* Source: https://www.geeksforgeeks.org/dsa/detect-loop-in-a-linked-list/ */
//Driver Code Starts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Driver Code Ends

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int new_data) {
    struct Node* new_node
        = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int detectLoop(struct Node* head) {
  
    // Fast and slow pointers initially points to the head
    struct Node *slow = head, *fast = head;

    // Loop that runs while fast and slow pointer are not
    // nullptr and not equal
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        // If fast and slow pointer points to the same node,
        // then the cycle is detected
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

//Driver Code Starts

int main() {

    struct Node* head = createNode(1);
    head->next = createNode(3);
    head->next->next = createNode(4);
  
    head->next->next->next = head->next;

    if (detectLoop(head))
        printf("true");
    else
        printf("false");

    return 0;
}
//Driver Code Ends
