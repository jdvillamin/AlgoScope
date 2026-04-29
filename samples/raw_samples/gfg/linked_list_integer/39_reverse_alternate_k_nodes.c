/* Source: https://www.geeksforgeeks.org/dsa/reverse-alternate-k-nodes-in-a-singly-linked-list/ */
// C program to reverse alternate k nodes

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *kAltReverse(struct Node *head, int k) {

    // Pointer to the tail of the
  	// previous segment
    struct Node *prevTail = NULL;
    int rev = 1;
    struct Node *curr = head;

    while (curr != NULL) {
      
        // Reverse the next k nodes
        if (rev == 1) {

            // Mark the head of the current segment
            struct Node *segHead = curr;
            struct Node *prev = NULL;

            // Reverse the current segment of k nodes
            for (int i = 0; i < k && curr != NULL; i++) {
                struct Node *nxt = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nxt;
            }

            // Update the head of the list if 
          	// this is the first segment
            if (prevTail == NULL) {
                head = prev;
            }
            else {
                // Link previous segment with the 
              	// current reversed segment
                prevTail->next = prev;
            }

            // Update the tail of the current segment
            prevTail = segHead;
            rev = 0;
        }
        else {
            // Skip the next k nodes without reversing
            prevTail->next = curr;
            for (int i = 0; i < k && curr != NULL; i++) {
                prevTail = curr;
                curr = curr->next;
            }
            rev = 1;
        }
    }

    return head;
}

void printList(struct Node *node) {
    struct Node *curr = node;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

struct Node *createNode(int x) {
    struct Node *node = 
      (struct Node *)malloc(sizeof(struct Node));
    node->data = x;
    node->next = NULL;
    return node;
}

int main() {
  
    // Hardcoded linked list: 1->2->3->4->5->6
    struct Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(6);
    head = kAltReverse(head, 2);
    printList(head);

    return 0;
}
