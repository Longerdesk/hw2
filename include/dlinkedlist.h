// DO NOT MODIFY THIS FILE
// Any additions should be placed in hw2_helpers.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void* data;          // pointer to the data to be stored
    struct node* next;   // pointer to the next node in the linked list
    struct node* prev;   // pointer to the prev node in the linked list
} node_t;

typedef struct list {
    node_t* head;        // pointer to the node_t at the head of the list
    int length;          // number of items in the list
    int (*comparator)(const void*,const  void*);     // function pointer for in order insertion
    void (*printer)(void*, FILE*);       // function pointer for printing the data stored
    void (*deleter)(void*);              // function pointer for deleting any dynamically 
                                         // allocated items within the data stored
} dlist_t;

// Functions already implemented
dlist_t* CreateList(int (*compare)(const void*, const void*), void (*print)(void*,FILE*),
                   void (*delete)(void*));
void InsertAtHead(dlist_t* list, void* val_ref);
void InsertAtTail(dlist_t* list, void* val_ref);
void InsertInOrder(dlist_t* list, void* val_ref);
void PrintLinkedList(dlist_t* list, FILE* fp);

#endif
