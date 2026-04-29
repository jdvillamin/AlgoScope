/* Source: https://www.geeksforgeeks.org/dsa/reverse-sublist-linked-list/ */
// C program to reverse a linked list
// from position m to position n
#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

// Function to reverse a linked list
struct Node *reverse(struct Node *head) {
    struct Node *prevNode = NULL;
    struct Node *currNode = head;
    while (currNode) {
        struct Node *nextNode = currNode->next;
        currNode->next = prevNode;
        prevNode = currNode;
        currNode = nextNode;
    }
    return prevNode;
}

// Function to reverse a linked list
// from position m to n
struct Node *reverseBetween(struct Node *head, int m, int n) {
  
    // If m and n are the same, no reversal is needed
    if (m == n)
        return head;

    struct Node *revs = NULL, *revs_prev = NULL;
    struct Node *revend = NULL, *revend_next = NULL;

    // Traverse the list to locate the nodes
    // and pointers needed for reversal
    int i = 1;
    struct Node *currNode = head;
    while (currNode && i <= n) {
      
        // Track the node just before the start
        // of the reversal segment
        if (i < m)
            revs_prev = currNode;
      
        // Track the start of the reversal segment
        if (i == m)
            revs = currNode;
      
        // Track the end of the reversal
        // segment and the node right after it
        if (i == n) {
            revend = currNode;
            revend_next = currNode->next;
        }
        currNode = currNode->next;
        i++;
    }

    // Detach the segment to be reversed from 
  	// the rest of the list
    revend->next = NULL;

    // Reverse the segment from position m to n
    revend = reverse(revs);

    // Reattach the reversed segment back to the list
    // If the reversal segment was not at the head of the list
    if (revs_prev)
        revs_prev->next = revend;
    else
        head = revend;

    // Connect the end of the reversed
    // segment to the rest of the list
    revs->next = revend_next;

    return head;
}

void print(struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

struct Node *createNode(int new_data) {
    struct Node *new_node = 
      (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {
  
    // Initialize linked list:
    // 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70
    struct Node *head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    head->next->next->next->next = createNode(50);
    head->next->next->next->next->next = createNode(60);
    head->next->next->next->next->next->next = createNode(70);

    printf("Original list: ");
    print(head);

    head = reverseBetween(head, 3, 6);

    printf("Modified list: ");
    print(head);

    return 0;
}
