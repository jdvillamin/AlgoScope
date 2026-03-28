#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    char id[10];
    struct Node* next;
} Node;

int main() {
    Node* head = NULL;
    int counter = 0;

    Node* n1 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n1->id, "n%d", counter);
    n1->value = 5;
    n1->next = NULL;
    head = n1;

    Node* n2 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n2->id, "n%d", counter);
    n2->value = 11;
    n2->next = NULL;
    n1->next = n2;

    Node* n3 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n3->id, "n%d", counter);
    n3->value = 14;
    n3->next = NULL;
    n2->next = n3;

    Node* n4 = (Node*)malloc(sizeof(Node));
    counter++;
    sprintf(n4->id, "n%d", counter);
    n4->value = 19;
    n4->next = NULL;
    n3->next = n4;

    int target = 14;
    Node* prev = NULL;
    Node* curr = head;
    while (curr != NULL) {
        if (curr->value == target) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL) {
        prev->next = curr->next;
        free(curr);
    }

    curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");

    return 0;
}
