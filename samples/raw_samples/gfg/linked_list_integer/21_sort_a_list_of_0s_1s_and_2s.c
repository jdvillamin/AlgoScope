/* Source: https://www.geeksforgeeks.org/dsa/sort-a-linked-list-of-0s-1s-or-2s/ */
// C Program to sort a linked list 0s, 1s 
// or 2s by updating links

#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int new_data);

// Sort a linked list of 0s, 1s and 2s 
// by changing pointers 
struct Node* sortList(struct Node* head) {
    if (!head || !(head->next)) 
        return head; 

    // Create three dummy nodes to point to beginning of 
    // three linked lists. These dummy nodes are created to 
    // avoid null checks. 
    struct Node* zeroD = createNode(0); 
    struct Node* oneD = createNode(0); 
    struct Node* twoD = createNode(0);

    // Initialize current pointers for three 
    // lists 
    struct Node *zero = zeroD, *one = oneD, *two = twoD; 

    // Traverse list 
    struct Node* curr = head; 
    while (curr) { 
        if (curr->data == 0) { 
          
            // If the data of current node is 0, 
            // append it to pointer zero and update zero
            zero->next = curr; 
            zero = zero->next; 
        } 
        else if (curr->data == 1) { 
          
            // If the data of current node is 1, 
            // append it to pointer one and update one
            one->next = curr; 
            one = one->next; 
        } 
        else { 
          
            // If the data of current node is 2, 
            // append it to pointer two and update two
            two->next = curr; 
            two = two->next; 
        } 
        curr = curr->next; 
    } 

    // Combine the three lists
    zero->next = (oneD->next) ? (oneD->next) : (twoD->next); 
    one->next = twoD->next; 
    two->next = NULL; 
      
    // Updated head 
    head = zeroD->next; 
    return head; 
} 

void printList(struct Node* node) {
    while (node != NULL) {
        printf(" %d", node->data);
        node = node->next;
    }
    printf("\n");
}

struct Node* createNode(int new_data) {
    struct Node* new_node = 
       (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {
  
    // Create a hard-coded linked list:
    // 1 -> 1 -> 2 -> 1 -> 0 -> NULL 
    struct Node* head = createNode(1);
    head->next = createNode(1);
    head->next->next = createNode(2);
    head->next->next->next = createNode(1);
    head->next->next->next->next = createNode(0);

    printf("Linked List before Sorting:");
    printList(head);

    head = sortList(head);

    printf("Linked List after Sorting:");
    printList(head);

    return 0;
}
