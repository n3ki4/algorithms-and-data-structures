//
// Created by n3ki4 on 4/1/22.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct node_s
{
    int data;
    struct node_s *next;
    struct node_s *prev;

} Node;

typedef struct list_s
{
    Node *head;
    Node *tail;
    int size;

} List;

void init_list(List *list)
{
    list->head = list->tail = NULL;
    list->size = 0;
}

/*
 * Creates new node
*/
Node *new_node(int data)
{
    Node *created_node = malloc(sizeof *created_node);
    created_node->data = data;
    created_node->next = created_node->prev = NULL;
}



void push_front(List *list, int data) {
    // check if (head & tail = NULL || head = tail = some node)
    if (list->head == NULL) {
        list->head = new_node(data);
    }
    else if (list->tail == NULL) {
        list->tail = list->head;
        list->head = list->tail->prev = new_node(data);
        list->head->next = list->tail;
    }
    else {
        list->head->prev = new_node(data);
        list->head->prev->next = list->head;
        list->head = list->head->prev;
    }

    list->size++;
}

void push_back(List *list, int data)
{
    // if not initialized list (head & tail = NULL) -> head = tail = new_node(data)?
    if (list->head == NULL) {
        list->head = new_node(data);
        list->tail = list->head;
    }
    // if only head exists
    else if (list->tail == list->head) {
        list->tail = new_node(data);
        list->tail->prev = list->head;
        list->head->next = list->tail;
    }
    else {
        list->tail->next = new_node(data);
        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
        list->tail->next = NULL;
    }
    list->size++;
}

/*
 * Links the node to the left of the selected node with the node to the right of the selected node
 * Don`t unlink the selected node! (selected node = node in the args)
 */
void link_nodes_between(Node *selected_node) {
    // links prev node of selected_node with the next node of the selected_node
    selected_node->prev->next = selected_node->next;
    // links next node of the selected_node with the prev of the selected_node
    selected_node->next->prev = selected_node->prev;
}


void del(List *list, int index) {
    if (list->size == 0 || index < 0 || index > list->size - 1)
        return;

    Node *to_delete;
    // if size == 1 -> tail & head = NULL;
    if (list->size == 1) {
        to_delete = list->head;
        list->head = list->tail = NULL;
    }

    // index = tail
    else if (index == list->size - 1) {
        // unlink tail
        to_delete = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    // index = head;
    else if (index == 0) {
        to_delete = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    // if the searching elem is closer to the tail
    else if (index > list->size - index) {
        // start from tail
        index = list->size - index;
        to_delete = list->tail;
        while(index--) {
            to_delete = to_delete->prev;
        }
        link_nodes_between(to_delete);
    }
    else {
        // start from head
        to_delete = list->head;
        while(index--) {
            to_delete = to_delete->next;
        }
        link_nodes_between(to_delete);
    }
    list->size--;
    free(to_delete);
}

void print_list(List *list)
{
    Node *current_node = list->head;
    while(current_node) {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
}

int main()
{
    List *list = malloc(sizeof (*list));
    init_list(list);

    for (int i = 0; i < 10; i++) {
        push_front(list, i + 5);
    }

    print_list(list);
    // ....

    free(list);
}