/* Source: https://www.geeksforgeeks.org/dsa/merge-two-sorted-linked-lists/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data);

struct Node* sortedMerge(struct Node* head1,
                             struct Node* head2) {
  
    // create a dummy node to simplify
    // the merging process
    struct Node* dummy = createNode(-1);
    struct Node* curr = dummy;

    // iterate through both linked lists
    while (head1 != NULL && head2 != NULL) {
      
        // add the smaller node to the merged list
        if (head1->data <= head2->data) {
            curr->next = head1;
            head1 = head1->next;
        } else {
            curr->next = head2;
            head2 = head2->next;
        }
        curr = curr->next;
    }

    // if any list is left, append it to 
    // the merged list
    if (head1 != NULL) {
        curr->next = head1;
    } else {
        curr->next = head2;
    }

    // return the merged list starting 
    // from the next of dummy node
    return dummy->next;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

struct Node* createNode(int data) {
    struct Node* newNode
      = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
  
    struct Node* head1 = createNode(5);
    head1->next = createNode(10);
    head1->next->next = createNode(15);
    head1->next->next->next = createNode(40);

    struct Node* head2 = createNode(2);
    head2->next = createNode(3);
    head2->next->next = createNode(20);

    struct Node* res = sortedMerge(head1, head2);

    printList(res);

    return 0;
}
