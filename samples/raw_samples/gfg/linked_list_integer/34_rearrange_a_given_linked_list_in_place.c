/* Source: https://www.geeksforgeeks.org/dsa/rearrange-a-given-linked-list-in-place/ */
// C code to rearrange a given linked list in-place

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *reverselist(struct Node *head) {
  
    // Initialize prev and current pointers
    struct Node *prev = NULL, *curr = head, *next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void printList(struct Node *curr) {
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
}

// Function to rearrange a linked list
struct Node *rearrange(struct Node *head) {
  
    // Find the middle point using tortoise 
  	// and hare method
    struct Node *slow = head, *fast = slow->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Split the linked list into two halves
    // head1, head of first half
    // head2, head of second half
    struct Node *head1 = head;
    struct Node *head2 = slow->next;
    slow->next = NULL;
    
    // Reverse the second half
    head2 = reverselist(head2);
    
    // Merge alternate nodes
    struct Node dummy; 
    struct Node *curr = &dummy;
    dummy.next = NULL;
    
    while (head1 || head2) {
      
        // First add the element from head1
        if (head1) {
            curr->next = head1;
            curr = curr->next;
            head1 = head1->next;
        }
      
        // Then add the element from head2
        if (head2) {
            curr->next = head2;
            curr = curr->next;
            head2 = head2->next;
        }
    }
  
    return dummy.next;
}

struct Node *newNode(int key) {
    struct Node *temp = 
      (struct Node *)malloc(sizeof(struct Node));
    temp->data = key;
    temp->next = NULL;
    return temp;
}

int main() {
  
 	// singly linked list 1->2->3->4->5
    struct Node *head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);

    head = rearrange(head);
  
    printList(head);        
    return 0;
}
