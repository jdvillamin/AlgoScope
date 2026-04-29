/* Source: https://www.geeksforgeeks.org/dsa/reverse-a-doubly-linked-list/ */
#include <stdio.h>
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *reverse(struct Node *head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct Node *prevNode = NULL;
    struct Node *currNode = head;

    // Traverse the list and reverse the links
    while (currNode != NULL) {
      
        // Swap the next and prev pointers
        prevNode = currNode->prev;
        currNode->prev = currNode->next;
        currNode->next = prevNode;

        // Move to the next node in the original list 
      	// (which is now previous due to reversal)
        currNode = currNode->prev;
    }

    if (prevNode != NULL)
        head = prevNode->prev;

    return head;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d", node->data);
        if(node->next != NULL){
            printf(" <-> ");
        }
        node = node->next;
    }
    printf("\n");
}

struct Node *createNode(int new_data){
    struct Node *new_node = 
      (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

int main() {

    struct Node *head = createNode(1);
    head->next = createNode(2);
    head->next->prev = head;
    head->next->next = createNode(3);
    head->next->next->prev = head->next;

    head = reverse(head);
    printList(head);

    return 0;
}
