/* Source: https://www.geeksforgeeks.org/dsa/reverse-a-linked-list/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int new_data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

struct Node *reverseList(struct Node *head) {
    
    struct Node *stack[100000];
    int top = -1;
    struct Node *temp = head;

    // push all nodes into stack
    while (temp != NULL) {
        stack[++top] = temp;
        temp = temp->next;
    }

    // make the last node as new head of the linked list
    if (top >= 0) {
        head = stack[top];
        temp = head;

        // pop all the nodes and append to the linked list
        while (top > 0) {
            
            // append the top value of stack in list
            temp->next = stack[--top];

            temp = temp->next;
        }

        // update the next pointer of last node of stack to null
        temp->next = NULL;
    }

    return head;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d", node->data);
        if (node->next)
            printf(" -> ");
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    head = reverseList(head);
    printList(head);

    return 0;
}
