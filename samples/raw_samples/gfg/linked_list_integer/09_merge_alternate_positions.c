/* Source: https://www.geeksforgeeks.org/dsa/merge-a-linked-list-into-another-linked-list-at-alternate-positions/ */
// C program to merge a linked list into another at
// alternate positions
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void printList(struct Node *head) {
    struct Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Function to merge two linked lists
struct Node *merge(struct Node *head1, struct Node *head2) {
    struct Node *curr1 = head1;
    struct Node *curr2 = head2;
    struct Node *next1, *next2;

    // Traverse both lists and merge them
    while (curr1 != NULL && curr2 != NULL) {
      
        // Save the next nodes of the current 
      	//  nodes in both lists
        next1 = curr1->next;
        next2 = curr2->next;

        // Insert the current node from the second list
      	// after the current node from the first list
        curr2->next = curr1->next;
        curr1->next = curr2;

        // Update the pointers for the next iteration
        curr1 = next1;
        curr2 = next2;
    }

    // Return the remaining part of the second list
    return curr2;
}

struct Node *createNode(int data) {
    struct Node *newNode = 
      (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
  
    // Creating the first linked list: 1->2->3
    struct Node *head1 = createNode(1);
    head1->next = createNode(2);
    head1->next->next = createNode(3);

    // Creating the second linked list: 4->5->6->7->8
    struct Node *head2 = createNode(4);
    head2->next = createNode(5);
    head2->next->next = createNode(6);
    head2->next->next->next = createNode(7);
    head2->next->next->next->next = createNode(8);

    struct Node *remaining = merge(head1, head2);

    // Print merged list and remaining list
    printList(head1);
    printList(remaining);

    return 0;
}
