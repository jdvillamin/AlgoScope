/* Source: https://www.geeksforgeeks.org/dsa/nth-node-from-the-end-of-a-linked-list/ */
#include <stdio.h>
#include <stdlib.h>

// Link list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node with given data
struct Node* newNode(int new_data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = new_data;
    node->next = NULL;
    return node;
}

// Function to find kth node from the end of linked list
int kthFromEnd(struct Node* head, int k) {

    // Create two pointers main_ptr and ref_ptr
    // initially pointing to head.
    struct Node* main_ptr = head;
    struct Node* ref_ptr = head;

    // Move ref_ptr to the k-th node from beginning.
    for (int i = 1; i < k; i++) {
        ref_ptr = ref_ptr->next;

        // If the ref_ptr reaches NULL, then it means 
        // k > length of linked list
        if (ref_ptr == NULL) {
            return -1;
        }
    }

    // Move ref_ptr and main_ptr by one node until
    // ref_ptr reaches last node of the list.
    while (ref_ptr->next != NULL) {
        ref_ptr = ref_ptr->next;
        main_ptr = main_ptr->next;
    }

    return main_ptr->data;
}

int main() {
    // Create a hard-coded linked list:
    // 35 -> 15 -> 4 -> 20
    struct Node* head = newNode(35);
    head->next = newNode(15);
    head->next->next = newNode(4);
    head->next->next->next = newNode(20);

    // Function Call to find the 4th node from end
    printf("%d\n", kthFromEnd(head, 4));

    return 0;
}
