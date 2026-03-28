#include "tracer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    char id[10];
    struct Node* next;
} Node;

int main() {
    trace_ll_init("list");
    trace_line(12);
    Node* head = NULL;
    trace_ll_pointer("list", "head", "NULL");
    trace_line(13);
    int counter = 0;
    trace_var_init("counter", 0);

    trace_line(15);
    Node* n1 = (Node*)malloc(sizeof(Node));
    trace_line(16);
    counter++;
    trace_var("counter", counter);
    trace_line(17);
    sprintf(n1->id, "n%d", counter);
    trace_line(18);
    n1->value = 6;
    trace_ll_node("list", n1->id, 6);
    trace_line(19);
    n1->next = NULL;
    trace_ll_link("list", n1->id, "NULL");
    trace_line(20);
    head = n1;
    trace_ll_pointer("list", "head", n1->id);

    trace_line(22);
    Node* n2 = (Node*)malloc(sizeof(Node));
    trace_line(23);
    counter++;
    trace_var("counter", counter);
    trace_line(24);
    sprintf(n2->id, "n%d", counter);
    trace_line(25);
    n2->value = 11;
    trace_ll_node("list", n2->id, 11);
    trace_line(26);
    n2->next = NULL;
    trace_ll_link("list", n2->id, "NULL");
    trace_line(27);
    n1->next = n2;
    trace_ll_link("list", n1->id, n2->id);

    trace_line(29);
    Node* n3 = (Node*)malloc(sizeof(Node));
    trace_line(30);
    counter++;
    trace_var("counter", counter);
    trace_line(31);
    sprintf(n3->id, "n%d", counter);
    trace_line(32);
    n3->value = 17;
    trace_ll_node("list", n3->id, 17);
    trace_line(33);
    n3->next = NULL;
    trace_ll_link("list", n3->id, "NULL");
    trace_line(34);
    n2->next = n3;
    trace_ll_link("list", n2->id, n3->id);

    trace_line(36);
    int target = 11;
    trace_var_init("target", 11);
    trace_line(37);
    int found = 0;
    trace_var_init("found", 0);
    trace_line(38);
    Node* curr = head;
    trace_ll_pointer("list", "curr", n1->id);
    trace_line(39);
    while (curr != NULL) {
        trace_line(39);
        trace_ll_highlight("list", curr->id);
        trace_line(40);
        if (curr->value == target) {
            trace_line(41);
            found = 1;
            trace_var("found", 1);
            trace_line(42);
            break;
        }
        trace_line(44);
        curr = curr->next;
        trace_ll_pointer("list", "curr", curr ? curr->id : "NULL");
    }

    trace_line(47);
    if (found) {
        trace_line(48);
        printf("Found %d\n", target);
    } else {
        trace_line(50);
        printf("Not found\n");
    }

    trace_line(53);
    return 0;
}
