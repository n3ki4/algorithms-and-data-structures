#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1;
#define FAULT 0;


typedef struct node_s
{
    int data;
    struct node_s *next;

} Node;


typedef struct list_s
{
    Node *head;

} List;

Node *new_node(int value)
{
    Node *node = malloc(sizeof *node);
    node->data = value;
    node->next = NULL;
    return node;
}


void init_list(List *list)
{
    list->head = NULL;
}

void push_back(List *list, int data)
{
    if (list->head == NULL) {
        list->head = new_node(data);;
        return;
    }
    Node *current_node = list->head;
    while(current_node->next != NULL) {
        current_node = current_node->next;
    }
    Node *elem = new_node(data);
    current_node->next = elem;
}

void push_front(List *list, int data) {
    if (list->head == NULL) {
        list->head = new_node(data);;
        return;
    }
    Node *current_node = new_node(data);
    current_node->next = list->head;
    list->head = current_node;

}

void print_list(List *list)
{
    Node* current_node = list->head;
    while(current_node != NULL) {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
}

int del(List *list, int index) {

    // optimize somehow pls!
    if (index < 0)
        return FAULT;
    Node *to_delete = NULL;
    if (index == 0) {
        to_delete = list->head;
        list->head = list->head->next;
    }
    else {
        to_delete = list->head;
        while(index-- != 1) {
            to_delete = to_delete->next;
        }
        // n -> del -> n
        Node *node = to_delete;
        to_delete = to_delete->next;
        node->next = node->next->next;

    }
    free(to_delete);
    return SUCCESS;

}

int main ()
{
    List *list = malloc(sizeof *list);
    init_list(list);
    for (int i = 0; i < 10; ++i) {
        push_front(list, i);
    }
    del(list, 9);
    del(list, 0);
    print_list(list);
    free(list);
}
