/*
    What is a linked list?
    A linked list is a set of dynamically allocated nodes, arranged in
    such a way that each node contains one piece of and two pointers.
    The pointer always points to the next member of the list.
    If the pointer is NULL, then it is the last node in the list.

    A linked list struct holds information about the type of data stored in the list. 
    The HEAD pointer points to the first node of the list. If that pointer is NULL, 
    then the list is considered to be empty. 

    Each node in the list holds a data item, a next pointer, and a prev pointer.
    The next pointer refers to the next item in the list. If the node is at the tail 
    (last item in the list), the pointer is NULL. The prev pointer refers to the prior 
    node in the list. If the node is at the head of the list the prev pointer is NULL.
    -------------------------------               ----------------------------              ----------------------------
    |HEAD                         |             \ |        |        |        | /          \ |        |        |        |
    |                             | ------------- |  PREV  |  DATA  |  NEXT  |--------------|  PREV  |  DATA  |  NEXT  |
    |-----------------------------|             / |        |        |        | \          / |        |        |        |
    |LENGTH                       |               ----------------------------              ----------------------------
    |COMPARATOR                   |
    |PRINTER                      |
    |DELETER                      |
    -------------------------------                                         
*/

#include "dlinkedlist.h"
#include "hw2.h"

dlist_t* CreateList(int (*compare)(const void*, const void*), void (*print)(void*, FILE*),
                   void (*delete)(void*)) {
    dlist_t* list = malloc(sizeof(dlist_t));
    list->comparator = compare;
    list->printer = print;
    list->deleter = delete;
    list->length = 0;
    list->head = NULL;
    return list;
}

void InsertAtHead(dlist_t* list, void* val_ref) {
    if(list == NULL || val_ref == NULL)
        return;
    if (list->length == 0) list->head = NULL;

    node_t** head = &(list->head);
    node_t* new_node;
    new_node = malloc(sizeof(node_t));

    new_node->data = val_ref;
    new_node->next = *head;
    new_node->prev = NULL;

    // moves list head to the new node
    if(*head != NULL)
        (*head)->prev = new_node;
    *head = new_node;
    list->length++;
}

void InsertAtTail(dlist_t* list, void* val_ref) {
    if (list == NULL || val_ref == NULL)
        return;
    if (list->length == 0) {
        InsertAtHead(list, val_ref);
        return;
    }

    node_t* head = list->head;
    node_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));
    current->next->data = val_ref;
    current->next->next = NULL;
    current->next->prev = current;
    list->length++;
}


void InsertInOrder(dlist_t* list, void* val_ref) {
    if(list == NULL || val_ref == NULL)
        return;
    if (list->length == 0) {
        InsertAtHead(list, val_ref);
        return;
    }

    node_t** head = &(list->head);
    node_t* new_node;
    new_node = malloc(sizeof(node_t));
    new_node->data = val_ref;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (list->comparator(new_node->data, (*head)->data) < 0) {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    } else if ((*head)->next == NULL) {
        (*head)->next = new_node;
        new_node->prev = *head;
    } else {
        node_t* current = (*head)->next;

        while (current != NULL) {
            if (list->comparator(new_node->data, current->data) > 0) {
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    current->next = new_node;
                    new_node->prev = current;
                    break;
                }
            } else {
                current->prev->next = new_node;
                new_node->prev = current->prev;
                current->prev = new_node;
                new_node->next = current;
                break;
            }
        }
    }
    list->length++;
}

void PrintLinkedList(dlist_t* list, FILE* fp) {
    if(list == NULL)
        return;

    node_t* head = list->head;
    while (head != NULL) {
        list->printer(head->data, fp);
        fprintf(fp, "\n");
        head = head->next;
    }
}
