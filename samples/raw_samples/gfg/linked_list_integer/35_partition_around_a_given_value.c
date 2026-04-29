/* Source: https://www.geeksforgeeks.org/dsa/partitioning-a-linked-list-around-a-given-value-and-keeping-the-original-order/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int val);

struct Node* partition(struct Node* head, int x) {
    // Dummy head for nodes less than x
    struct Node* lessHead = createNode(0);

    // Dummy head for nodes equal to x
    struct Node* equalHead = createNode(0);

    // Dummy head for nodes greater than or equal to x
    struct Node* greaterHead = createNode(0);

    struct Node* less = lessHead;
    struct Node* equal = equalHead;
    struct Node* greater = greaterHead;

    struct Node* curr = head;

    while (curr != NULL) {
        if (curr->data < x) {
            less->next = curr;
            less = less->next;
        } else if (curr->data == x) {
            equal->next = curr;
            equal = equal->next;
        } else {
            greater->next = curr;
            greater = greater->next;
        }
        curr = curr->next;
    }

    // Connect the partitions together
    greater->next = NULL;

    // Connect equal to greater
    equal->next = greaterHead->next;

    // Connect less to equal
    less->next = equalHead->next;

    // New head of the rearranged list
    struct Node* newHead = lessHead->next;

    // Clean up dummy nodes
    free(lessHead);
    free(equalHead);
    free(greaterHead);

    return newHead;
}

void printList(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

struct Node* createNode(int val) {
    struct Node* newNode = 
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

int main() {
    // Creating the linked list: 1 -> 4 -> 3 -> 2 -> 5 -> 2
    struct Node* head = createNode(1);
    head->next = createNode(4);
    head->next->next = createNode(3);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(2);
	
  	int x = 3;
    head = partition(head, x);
    printList(head);

    return 0;
}
