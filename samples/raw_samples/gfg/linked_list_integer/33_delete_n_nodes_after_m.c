/* Source: https://www.geeksforgeeks.org/dsa/delete-n-nodes-after-m-nodes-of-a-linked-list/ */
// C program to delete n nodes after
// m nodes of a linked list

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

// Function to skip m nodes and then delete n nodes of the linked list
struct Node *skipMdeleteN(struct Node *head, int m, int n){
    struct Node *curr = head; // Current node pointer
    struct Node *t;           // Temporary node pointer
    int count;                // Counter variable

    // Traverse through the entire linked list
    while (curr != NULL){
        // Skip m nodes
        for (count = 1; count < m && curr != NULL; count++)
            curr = curr->next;

        // If end of the list is reached, return the head
        if (curr == NULL)
            return head;

        // Start from the next node and delete n nodes
        t = curr->next;
        for (count = 1; count <= n && t != NULL; count++){
            struct Node *temp = t;
            t = t->next;
            free(temp);
        }

        // Link the current node to the remaining list
        curr->next = t;

        // Move the current pointer to the next node
        curr = t;
    }

    return head;
}

void printList(struct Node *head){
    struct Node *curr = head;
    while (curr != NULL){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

struct Node *createNode(int data){
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int main(){
    // Create the following linked list: 1->2->3->4->5->6
    struct Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(6);

    int m = 2, n = 2;
    head = skipMdeleteN(head, m, n);
    printList(head);

    return 0;
}
