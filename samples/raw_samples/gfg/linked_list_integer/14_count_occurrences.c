/* Source: https://www.geeksforgeeks.org/dsa/write-a-function-that-counts-the-number-of-times-a-given-int-occurs-in-a-linked-list/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Counts the number of occurrences of a key
// in a linked list using recursion
int count(struct Node* head, int key) {
    if (head == NULL) {
        return 0;
    }
  
  	int ans = count(head->next, key);
  
    if (head->data == key) {
        ans++;
    }
  
  	return ans;
}

struct Node* createNode(int new_data) {
    struct Node* new_node = 
      (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {
  
    // Hard Coded Linked List 
    // 1->2->1->2->1
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(1);

    int key = 1;
  
    printf("%d", count(head, key));

    return 0;
}
