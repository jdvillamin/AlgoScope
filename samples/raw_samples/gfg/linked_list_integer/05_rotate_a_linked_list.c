/* Source: https://www.geeksforgeeks.org/dsa/rotate-a-linked-list/ */
#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNode(int new_data) {
    struct Node *new_node = 
      			(struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

struct Node* rotate(struct Node *head, int k) {
  
    if (k == 0 || head == NULL)
        return head;

    struct Node *curr = head;
    int len = 1;

    // find the length of linked list
    while (curr->next != NULL) {
        curr = curr->next;
        len += 1;
    }

    // modulo k with length of linked list to
    // handle large values of k
    k %= len;

    if (k == 0)
        return head;
  
  	// make the linked list circular
    curr->next = head;

    // traverse the linked list to find the kth node
    curr = head;
    for (int i = 1; i < k; i++)
        curr = curr->next;

    // update the (k + 1)th node as the new head
    head = curr->next;
    
    // break the loop by updating next pointer
    // of kth node
    curr->next = NULL;
    return head;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d", node->data);
        if(node->next != NULL){
            printf(" -> ");
        }
        node = node->next;
    }
    printf("\n");
}

int main() {
  	
    // create a hard-coded linked list:
    // 10 -> 20 -> 30 -> 40
    struct Node *head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);

    head = rotate(head, 6);
    printList(head);
    return 0;
}
