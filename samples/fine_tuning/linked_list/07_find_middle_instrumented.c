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
    n1->value = 2;
    trace_ll_node("list", n1->id, 2);
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
    n2->value = 7;
    trace_ll_node("list", n2->id, 7);
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
    n3->value = 13;
    trace_ll_node("list", n3->id, 13);
    trace_line(33);
    n3->next = NULL;
    trace_ll_link("list", n3->id, "NULL");
    trace_line(34);
    n2->next = n3;
    trace_ll_link("list", n2->id, n3->id);

    trace_line(36);
    Node* n4 = (Node*)malloc(sizeof(Node));
    trace_line(37);
    counter++;
    trace_var("counter", counter);
    trace_line(38);
    sprintf(n4->id, "n%d", counter);
    trace_line(39);
    n4->value = 18;
    trace_ll_node("list", n4->id, 18);
    trace_line(40);
    n4->next = NULL;
    trace_ll_link("list", n4->id, "NULL");
    trace_line(41);
    n3->next = n4;
    trace_ll_link("list", n3->id, n4->id);

    trace_line(43);
    Node* n5 = (Node*)malloc(sizeof(Node));
    trace_line(44);
    counter++;
    trace_var("counter", counter);
    trace_line(45);
    sprintf(n5->id, "n%d", counter);
    trace_line(46);
    n5->value = 20;
    trace_ll_node("list", n5->id, 20);
    trace_line(47);
    n5->next = NULL;
    trace_ll_link("list", n5->id, "NULL");
    trace_line(48);
    n4->next = n5;
    trace_ll_link("list", n4->id, n5->id);

    trace_line(50);
    Node* slow = head;
    trace_ll_pointer("list", "slow", n1->id);
    trace_line(51);
    Node* fast = head;
    trace_ll_pointer("list", "fast", n1->id);
    trace_line(52);
    while (fast != NULL && fast->next != NULL) {
        trace_line(52);
        trace_ll_highlight("list", slow->id);
        trace_ll_highlight("list", fast->id);
        trace_line(53);
        slow = slow->next;
        trace_ll_pointer("list", "slow", slow->id);
        trace_line(54);
        fast = fast->next->next;
        trace_ll_pointer("list", "fast", fast ? fast->id : "NULL");
    }

    trace_line(57);
    printf("Middle: %d\n", slow->value);

    trace_line(59);
    return 0;
}
