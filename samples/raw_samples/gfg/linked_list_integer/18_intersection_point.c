/* Source: https://www.geeksforgeeks.org/dsa/write-a-function-to-get-the-intersection-point-of-two-linked-lists/ */
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = 
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to get the count of nodes in a linked list 
int getCount(struct Node* head) {
    int cnt = 0;
    struct Node* curr = head;
    while (curr != NULL) {
        cnt++;
        curr = curr->next;
    }
    return cnt;
}

// Function to get the intersection point of two
// linked lists where head1 has d more nodes than head2
struct Node* getIntersectionByDiff(int diff, 
                struct Node* head1, struct Node* head2) {
    struct Node* curr1 = head1;
    struct Node* curr2 = head2;

    // Move the pointer forward by d nodes
    for (int i = 0; i < diff; i++) {
        if (curr1 == NULL)
            return NULL;
        curr1 = curr1->next;
    }

    // Move both pointers until they intersect
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1 == curr2)
            return curr1;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return NULL;
}

// Function to get the intersection point of two linked lists
struct Node* intersectPoint(struct Node* head1, struct Node* head2) {
  
    // Count the number of nodes in both linked lists
    int len1 = getCount(head1);
    int len2 = getCount(head2);

    int diff = 0;

    // If the first list is longer
    if (len1 > len2) {
        diff = len1 - len2;
        return getIntersectionByDiff(diff, head1, head2);
    } else {
        diff = len2 - len1;
        return getIntersectionByDiff(diff, head2, head1);
    }
}

int main() {
  
    // creation of first list: 10 -> 15 -> 30
    struct Node* head1 = createNode(10);
    head1->next = createNode(15);
    head1->next->next = createNode(30);

    // creation of second list: 3 -> 6 -> 9 -> 15 -> 30
    struct Node* head2 = createNode(3);
    head2->next = createNode(6);
    head2->next->next = createNode(9);

    // 15 is the intersection point
    head2->next->next->next = head1->next;

    struct Node* interPt = intersectPoint(head1, head2);

    if (interPt == NULL)
        printf("-1\n");
    else
        printf("%d\n", interPt->data);

    return 0;
}
