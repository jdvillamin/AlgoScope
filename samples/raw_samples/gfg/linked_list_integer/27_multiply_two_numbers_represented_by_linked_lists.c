/* Source: https://www.geeksforgeeks.org/dsa/multiply-two-numbers-represented-linked-lists/ */
// C program to Multiply two numbers
// represented as linked lists
#include <stdlib.h>
#define MOD 1000000007

struct Node {
    int data;
    struct Node *next;
};

// Multiply contents of two linked lists
long long multiplyTwoLists(struct Node *first, struct Node *second) {
    long long num1 = 0, num2 = 0;

    // Traverse the first list and
    // construct the number with modulo
    while (first != NULL) {
        num1 = (num1 * 10 + first->data) % MOD;
        first = first->next;
    }

    // Traverse the second list and
    // construct the number with modulo
    while (second != NULL) {
        num2 = (num2 * 10 + second->data) % MOD;
        second = second->next;
    }

    // Return the product of the two 
  	// numbers with modulo
    return (num1 * num2) % MOD;
}

void printList(struct Node *curr) {
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
}

struct Node *createNode(int data) {
    struct Node *newNode = 
      (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {

    // Create first list 9->4->6
    struct Node *head1 = createNode(9);
    head1->next = createNode(4);
    head1->next->next = createNode(6);

    // Create second list 8->4
    struct Node *head2 = createNode(8);
    head2->next = createNode(4);
    printf("%lld\n", multiplyTwoLists(head1, head2));

    return 0;
}
