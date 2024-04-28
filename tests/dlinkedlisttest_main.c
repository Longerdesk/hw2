#include "dlinkedlist.h"
#include "hw2.h"

// The linked list used the data field of the node_t struct as an long (not a pointer to a long). 
// The void* data can hold any value. In this case, we use the (void*) amount of memory space to store the long value itself! 



int intComparator(const void *p, const void *q)
{
    // casting the pointers to long values
    return ((long)p - (long)q);
}

void intPrinter(void *data, FILE* fp)
{
    fprintf((FILE*) fp, "%ld ", (long) data);
}

void intDeleter(void *data)
{
    return;   //Nothing to delete! data field is not a pointer to dynamically allocated data
}

int main(int argc, char** argv) {
    long start = 1;
    long end = 20;
    int i;

    // Create and initialize integer linked list
    dlist_t* list = CreateList(&intComparator, &intPrinter, &intDeleter);

    // Output: List is empty
    printf("**********Empty List**********\n");    
    PrintLinkedList(list, stdout);
    printf("\n");


    // Output: 1
    printf("**********1 List Value**********\n");   
    // Insert first node. Why does start need to be casted?
    InsertAtHead(list, (void*)start);
    PrintLinkedList(list, stdout);
    printf("\n");


    printf("**********Full List except 10**********\n");   
    // Inserting the remaining values, skip value 10
    for (i = start + 1; i <= end; i++) {
        if(i != 10)
            InsertAtTail(list, (void*)(long)i);
    }
    // Output (each value on a line): 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 18 19 20
    PrintLinkedList(list, stdout);
    printf("\n");

    printf("**********Full List**********\n");   
    InsertInOrder(list, (void*)10);
    // Output (each value on a line): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    PrintLinkedList(list, stdout);
    printf("\n");


    printf("**********Duplicate Odd Numbers In List**********\n");   
    // Inserting every other value again, inOrder based on comparator
    for (i = start; i <= end; i=i+2) {
        InsertInOrder(list, (void*)(long)i);
    }
    // Output (each value on a line): 1 1 2 3 3 4 5 5 6 7 7 8 9 9 10 11 11 12 13 13 14 15 15 16 17 17 18 19 19 20
    PrintLinkedList(list, stdout);
    printf("\n");

    // The DestroyLinkedList(&list) function as specified in the HW doc will not work on this integer linked list 
    // because the data field does not point at dynamically allocated elements. This program will LEAK MEMORY.

    return 0;
}
