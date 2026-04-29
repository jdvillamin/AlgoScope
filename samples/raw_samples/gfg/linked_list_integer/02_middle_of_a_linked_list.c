/* Source: https://www.geeksforgeeks.org/dsa/write-a-c-function-to-print-the-middle-of-the-linked-list/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int getLength(struct Node* head) {

    int length = 0;
    
    // find length of linked list
    while (head) {
        length++;
        head = head->next;
    }

    return length;
}

int getMiddle(struct Node* head) {

    // finding length of the linked list
    int length = getLength(head);

    // traverse till we reach half of the length
    int midIndex = length / 2;
    while (midIndex--) {
        head = head->next;
    }

    return head->data;
}

struct Node* createNode(int x) {
    struct Node* newNode
        = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

int main() {

    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    head->next->next->next->next = createNode(50);
    head->next->next->next->next->next = createNode(60);

    printf("%d\n", getMiddle(head));

    return 0;
}
