/* Source: https://www.geeksforgeeks.org/dsa/function-to-check-if-a-singly-linked-list-is-palindrome/ */
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to reverse a linked list
struct Node* reverse(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* curr = head;
    struct Node* next;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Function to check if two lists are identical
int isIdentical(struct Node* n1, struct Node* n2) {
    for (; n1 && n2; n1 = n1->next, n2 = n2->next)
        if (n1->data != n2->data)
            return 0;

    // returning 1 if data at all nodes are equal.
    return 1;
}

// Function to check whether the list is palindrome
int isPalindrome(struct Node* head) {
    if (!head || !head->next)
        return 1;

    struct Node *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct Node* head2 = reverse(slow->next);
    slow->next = NULL;

    int ret = isIdentical(head, head2);

    head2 = reverse(head2);
    slow->next = head2;

    return ret;
}

struct Node* createNode(int data) {
    struct Node* newNode = 
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
  	
  	// Linked list : 1->2->3->2->1
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(1);

    int result = isPalindrome(head);

    if (result)
        printf("true\n");
    else
        printf("false\n");

    return 0;
}
