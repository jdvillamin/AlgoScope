/* Source: https://www.geeksforgeeks.org/dsa/add-two-numbers-represented-by-linked-list/ */
#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int val);

// Function to reverse the linked list
struct Node *reverse(struct Node *head) {
    struct Node *prev = NULL, *curr = head, *next;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Function to trim leading zeros in linked list
struct Node* trimLeadingZeros(struct Node* head) {
    while (head->next != NULL && head->data == 0)
        head = head->next;
    return head;
}

// Function to add two numbers represented by linked list
struct Node *addTwoLists(struct Node *num1, struct Node *num2) {
    struct Node *res = NULL, *curr = NULL;
    int carry = 0;
  
	num1 = trimLeadingZeros(num1);
	num2 = trimLeadingZeros(num2);
  
    num1 = reverse(num1);
    num2 = reverse(num2);

    // Iterate till either num1 is not empty or num2 is
    // not empty or carry is greater than 0
    while (num1 != NULL || num2 != NULL || carry != 0) {
        int sum = carry;

        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }

        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }
      
        struct Node* newNode = createNode(sum % 10);

        carry = sum / 10;

        // If this is the first node, then make this node
        // as the head of the resultant linked list
        if (res == NULL) {
            res = newNode;
            curr = newNode;
        } 
      	else {
            
          	// Append new node to resultant linked list
            // and move to the next node
            curr->next = newNode;
            curr = curr->next;
        }
    }

    return reverse(res);
}

void printList(struct Node *head) {
    struct Node *curr = head;
    while (curr != NULL) {
        printf("%d", curr->data);
        if(curr->next != NULL){
            printf(" -> ");
        }
        curr = curr->next;
    }
    printf("\n");
}

struct Node *createNode(int val) {
    struct Node *node = 
      		(struct Node *)malloc(sizeof(struct Node));
    node->data = val;
    node->next = NULL;
    return node;
}

int main() {

    struct Node *num1 = createNode(1);
    num1->next = createNode(2);
    num1->next->next = createNode(3);

    struct Node *num2 = createNode(9);
    num2->next = createNode(9);
    num2->next->next = createNode(9);

    struct Node *sum = addTwoLists(num1, num2);
    printList(sum);

    return 0;
}
