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
    n1->value = 4;
    trace_ll_node("list", n1->id, 4);
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
    n2->value = 12;
    trace_ll_node("list", n2->id, 12);
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
    n3->value = 18;
    trace_ll_node("list", n3->id, 18);
    trace_line(33);
    n3->next = NULL;
    trace_ll_link("list", n3->id, "NULL");
    trace_line(34);
    n2->next = n3;
    trace_ll_link("list", n2->id, n3->id);

    trace_line(36);
    int pos = 2;
    trace_var_init("pos", 2);
    trace_line(37);
    Node* newNode = (Node*)malloc(sizeof(Node));
    trace_line(38);
    counter++;
    trace_var("counter", counter);
    trace_line(39);
    sprintf(newNode->id, "n%d", counter);
    trace_line(40);
    newNode->value = 8;
    trace_ll_node("list", newNode->id, 8);

    trace_line(42);
    Node* curr = head;
    trace_ll_pointer("list", "curr", n1->id);
    trace_line(43);
    int i = 1;
    trace_var_init("i", 1);
    trace_line(44);
    while (i < pos - 1) {
        trace_line(44);
        trace_ll_highlight("list", curr->id);
        trace_line(45);
        curr = curr->next;
        trace_ll_pointer("list", "curr", curr->id);
        trace_line(46);
        i++;
        trace_var("i", i);
    }
    trace_line(48);
    newNode->next = curr->next;
    trace_ll_link("list", newNode->id, curr->next ? curr->next->id : "NULL");
    trace_line(49);
    curr->next = newNode;
    trace_ll_link("list", curr->id, newNode->id);

    trace_line(51);
    curr = head;
    trace_ll_pointer("list", "curr", n1->id);
    trace_line(52);
    while (curr != NULL) {
        trace_line(52);
        trace_ll_highlight("list", curr->id);
        trace_line(53);
        printf("%d ", curr->value);
        trace_line(54);
        curr = curr->next;
        trace_ll_pointer("list", "curr", curr ? curr->id : "NULL");
    }
    trace_line(56);
    printf("\n");

    trace_line(58);
    return 0;
}
