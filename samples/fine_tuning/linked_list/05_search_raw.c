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
    n1->value = 6;
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
    n3->value = 17;
    n3->next = NULL;
    n2->next = n3;

    int target = 11;
    int found = 0;
    Node* curr = head;
    while (curr != NULL) {
        if (curr->value == target) {
            found = 1;
            break;
        }
        curr = curr->next;
    }

    if (found) {
        printf("Found %d\n", target);
    } else {
        printf("Not found\n");
    }

    return 0;
}
