/* Source: https://www.geeksforgeeks.org/dsa/split-a-circular-linked-list-into-two-halves/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Pair {
    struct Node* first;
    struct Node* second;
};

// Function to split a list (starting with head)
// into two lists and return a pair of their heads
struct Pair splitList(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;
    struct Pair result;

    if (head == NULL) {
        result.first = NULL;
        result.second = NULL;
        return result;
    }

    // For odd nodes, fast->next is head and
    // for even nodes, fast->next->next is head
    while (fast->next != head 
    && fast->next->next != head) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // If there are even elements in the list
    // then move fast
    if (fast->next->next == head) {
        fast = fast->next;
    }

    // Set the head pointer of the first half
    result.first = head;

    // Set the head pointer of the second half
    result.second = slow->next;

    // Make the second half circular
    fast->next = slow->next;

    // Make the first half circular
    slow->next = head;

    return result;
}

void printList(struct Node* head) {
    struct Node* curr = head;
    if (head != NULL) {
        do {
            printf("%d ", curr->data);
            curr = curr->next;
        } while (curr != head);
        printf("\n");
    }
}

struct Node* createNode(int new_data) {
    struct Node* new_node = 
    (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {

    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    // Created linked list will be 1->2->3->4
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = head;

    struct Pair result = splitList(head);
    head1 = result.first;
    head2 = result.second;

    printList(head1);
    printList(head2);

    return 0;
}
