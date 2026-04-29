/* Source: https://www.geeksforgeeks.org/dsa/delete-occurrences-given-key-linked-list/ */
// Iterative C program to delete all occurrences of a 
// given key in a linked list
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Given the head of a list, delete all occurrences of a 
// given key and return the new head of the list
struct Node* deleteOccurrences(struct Node* head, int key) {

    // Initialize pointers to traverse the linked list
    struct Node *curr = head, *prev = NULL;

    // Traverse the list to delete all occurrences
    while (curr != NULL) {

        // If current node's data is equal to key
        if (curr->data == key) {

            // If node to be deleted is head node
            if (prev == NULL) {
                head = curr->next;
            } 
          
            else {
                prev->next = curr->next;
            }

            // Move to the next node
            curr = curr->next;

        } 
      
         else {
           
            // Move pointers one position ahead
            prev = curr;
            curr = curr->next;
        }
    }

    return head;
}

void printList(struct Node* curr) {
    while (curr != NULL) {
        printf(" %d", curr->data);
        curr = curr->next;
    }
}

struct Node* createNode(int new_data) {
    struct Node* new_node
        = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {

    // Create a hard-coded linked list:
    // 2 -> 2 -> 1 -> 8 -> 2 -> NULL
    struct Node* head = createNode(2);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(8);
    head->next->next->next->next = createNode(2);

    int key = 2;
    head = deleteOccurrences(head, key);
    printList(head);

    return 0;
}
