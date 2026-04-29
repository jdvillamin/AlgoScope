/* Source: https://www.geeksforgeeks.org/dsa/delete-last-occurrence-of-an-item-from-linked-list/ */
// C program to delete last occurrence 
// of key in singly linked list

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to delete the last occurrence
// of a key in the linked list
struct Node* deleteLastOccurrence(struct Node* head, int key) {
    struct Node *last = NULL, *lastPrev = NULL;
    struct Node *curr = head, *prev = NULL;

    // Traverse the list to find the last
    // occurrence of the key
    while (curr != NULL) {
        if (curr->data == key) {
            lastPrev = prev;
            last = curr;
        }
        prev = curr;
        curr = curr->next;
    }

    // If the key was found
    if (last != NULL) {

        // If last occurrence is not the head
        if (lastPrev != NULL) {
            lastPrev->next = last->next;
        } else {

            // If last occurrence is the head,
            // move head to next node
            head = head->next;
        }
        free(last);
    }

    return head;
}

void print(struct Node* curr) {
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

struct Node* createNode(int new_data) {
    struct Node* newNode = 
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = new_data;
    newNode->next = NULL;
    return newNode;
}

int main() {
  
    // Create a hard-coded linked list:
    // 1 -> 2 -> 2 -> 4 -> 2
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(2);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(2);

    int key = 2;
    head = deleteLastOccurrence(head, key);
    print(head);
    return 0;
}
