/* Source: https://www.geeksforgeeks.org/dsa/merge-k-sorted-linked-lists/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data);

// Function to merge only 2 lists
struct Node* mergeTwo(struct Node* head1, struct Node* head2) {
    
    // Create a dummy node to simplify 
    // the merging process
    struct Node* dummy = createNode(-1);
    struct Node* curr = dummy;

    // Iterate through both linked lists
    while (head1 != NULL && head2 != NULL) {
      
        // Add the smaller node to the merged list
        if (head1->data <= head2->data) {
            curr->next = head1;
            head1 = head1->next;
        } else {
            curr->next = head2;
            head2 = head2->next;
        }
        curr = curr->next;
    }

    // If any list is left, append it to
    // the merged list
    if (head1 != NULL) {
        curr->next = head1;
    } else {
        curr->next = head2;
    }

    // Return the merged list starting
    // from the next of dummy node
    struct Node* merged = dummy->next;
    free(dummy);
    return merged;
}

// Function to merge K sorted linked lists
struct Node* mergeKLists(struct Node** arr, int k) {
  
    // Initialize result as empty
    struct Node* res = NULL;
    
    // One by one merge all lists with 
    // res and keep updating res
    for (int i = 0; i < k; i++) 
        res = mergeTwo(res, arr[i]);
        
    return res;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d", node->data);
        if(node->next)
        printf(" -> ");
        node = node->next;
    }
}

struct Node* createNode(int data) {
    struct Node* newNode = 
    (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    int k = 3; 
    struct Node* arr[k];

    arr[0] = createNode(1);
    arr[0]->next = createNode(3);
    arr[0]->next->next = createNode(5);
    arr[0]->next->next->next = createNode(7);

    arr[1] = createNode(2);
    arr[1]->next = createNode(4);
    arr[1]->next->next = createNode(6);
    arr[1]->next->next->next = createNode(8);

    arr[2] = createNode(0);
    arr[2]->next = createNode(9);
    arr[2]->next->next = createNode(10);
    arr[2]->next->next->next = createNode(11);
    
    struct Node* head = mergeKLists(arr, k);

    printList(head);

    return 0;
}
