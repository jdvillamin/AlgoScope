/* Source: https://www.geeksforgeeks.org/dsa/delete-middle-of-linked-list/ */
// C program to delete middle of a linked list
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to delete middle node from linked list
struct Node* deleteMid(struct Node* head) {
    // If the list is empty, return NULL
    if (head == NULL)
        return NULL;

    // If the list has only one node,
    // delete it and return NULL
    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    struct Node* prev = NULL;
    struct Node* slow_ptr = head;
    struct Node* fast_ptr = head;

    // Move the fast pointer 2 nodes ahead
    // and the slow pointer 1 node ahead
    // until fast pointer reaches end of the list
    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        fast_ptr = fast_ptr->next->next;

        // Update prev to hold the previous 
        // slow pointer value
        prev = slow_ptr;

        slow_ptr = slow_ptr->next;
    }

    // At this point, slow_ptr points to middle node
    // Bypass the middle node
    prev->next = slow_ptr->next;

    // Delete the middle node
    free(slow_ptr);

    // Return the head of the modified list
    return head;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct Node* newNode(int x) {
    struct Node* temp = 
      (struct Node*)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = NULL;
    return temp;
}

int main() {
    // Create a static hardcoded linked list:
    // 1 -> 2 -> 3 -> 4 -> 5.
    struct Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);

    printf("Original Linked List: ");
    printList(head);

    // Delete the middle node.
    head = deleteMid(head);

    printf("Linked List after deleting the middle node: ");
    printList(head);

    return 0;
}
