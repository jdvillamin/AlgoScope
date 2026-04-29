/* Source: https://www.geeksforgeeks.org/dsa/flattening-a-linked-list/ */
// C program for flattening a Linked List

#include <stdio.h>

struct Node {
    int data;
    struct Node *next, *bottom;
};

// Utility function to merge two sorted linked lists using
// their bottom pointers
struct Node* merge(struct Node* head1, struct Node* head2) {

    // A dummy first node to store the result list
    struct Node dummy;
    dummy.data = -1;
    dummy.bottom = NULL;

    // Tail points to the last result node to add new nodes
    // to the result
    struct Node* tail = &dummy;

    // Iterate till either head1 or head2 does not reach
    // NULL
    while (head1 && head2) {

        if (head1->data <= head2->data) {

            // append head1 to the result
            tail->bottom = head1;
            head1 = head1->bottom;
        }
        else {

            // append head2 to the result
            tail->bottom = head2;
            head2 = head2->bottom;
        }

        // Move tail pointer to the next node
        tail = tail->bottom;
    }

	// Append the remaining nodes of non-null linked list  	
    if (!head1)
        tail->bottom = head2;
    else
        tail->bottom = head1;

    return dummy.bottom;
}

// Function to flatten the linked list
struct Node* flatten(struct Node* root) {
  
    // Base Cases
    if (root == NULL || root->next == NULL)
        return root;

    // Recur for next list
    root->next = flatten(root->next);

    // Now merge the current and next list
    root = merge(root, root->next);

    // Return the root
    return root;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if(temp->bottom)
        printf(" -> ");
        temp = temp->bottom;
    }
    printf("\n");
}

// Function to create a new node
struct Node* createNode(int newdata) {
    struct Node* newnode
        = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = newdata;
    newnode->next = NULL;
  	newnode->bottom = NULL;
    return newnode;
}

int main() {

    /* Create a hard-coded linked list:
        5 -> 10 -> 19 -> 28
        |    |     |
        V    V     V
        7    20    22
        |          |
        V          V
        8          50
        |
        V
        30
    */

    struct Node* head = createNode(5);
    head->bottom = createNode(7);
    head->bottom->bottom = createNode(8);
    head->bottom->bottom->bottom = createNode(30);

    head->next = createNode(10);
    head->next->bottom = createNode(20);

    head->next->next = createNode(19);
    head->next->next->bottom = createNode(22);
    head->next->next->bottom->bottom = createNode(50);

    head->next->next->next = createNode(28);

    head = flatten(head);

    printList(head);

    return 0;
}
