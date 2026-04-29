/* Source: https://www.geeksforgeeks.org/dsa/traversal-of-circular-linked-list/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    
};

void printList(struct Node* curr, struct Node* head) {

    // return if list is empty
    if (head == NULL) return;
    
    printf("%d ", curr->data);
    
    if (curr->next == head)
        return;
        
    printList(curr->next, head);

}

struct Node* createNode(int data) {
    struct Node* new_node = 
    	(struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int main() {
  	
  	// Create a hard-coded linked list
	// 11 -> 2 -> 56 -> 12
    struct Node* head = createNode(11);
    head->next = createNode(2);
    head->next->next = createNode(56);
    head->next->next->next = createNode(12);

    head->next->next->next->next = head;

    printList(head, head);

    return 0;
}
