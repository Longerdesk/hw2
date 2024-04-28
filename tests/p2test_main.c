#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Can be used in testing files

#include "helpers2.h"
#include "hw2.h"
#include "dlinkedlist.h"

int main(void) {
    /*char testInfo[] = "53markdown -E -C < rsrc/sample_emoji.md > out.txt 2> err.txt";
    char* exeName1 = (char*)malloc(256);
    unsigned char info1 = commandInfo(testInfo, &exeName1);
    printf("info is %d\n", info1);
*/
    //printf("size of nodet is %d\n", sizeof());
    /*char line1[] = "./bin/53markdown  -A < rsrc/sample_1.md";  // edittable copy of string
    char *exeName = ((char*)malloc(256));
    unsigned char info = commandInfo(line1, &exeName);

    EXEnode* f1 = createEXE(exeName, info);
    if(f1 == NULL){
        printf("fail\n");
    }else{
        printf("success creating EXEnode.\n");
        EXEnode3Print(f1, stdout);
        printf("\n");
    }*/

    dlist_t* list = CreateList(&EXEabcComparator, &EXEnode1Print, &EXEnodeDeleter);

    //int parseInput(dlist_t* list, FILE* fp);
    //printf("**********Empty List**********\n");    
    //PrintLinkedList(list, stdout);
    //printf("\n");


    // Output: 1
   /* printf("**********1 List Value**********\n");   
    InsertInOrder(list, (void*)f1);
    PrintLinkedList(list, stdout);
    printf("\n");*/
//  TEST PARSEINPUT
    printf("**********List Value**********\n"); 
    FILE *fp = fopen("/root/ics53/hw2/rsrc/bash_history_3.txt", "r");
    parseInputRecent(list, fp);
    PrintLinkedList(list, stdout);
    printf("List length: %d", list->length);
    printf("\n");
    //swapInDLL(list, 1);
    //swapInDLL(list, 2);
    //swapInDLL(list, 3);
    //swapInDLL(list, 4);
    sortListFrequency(list);
    printf("**********AFTER SORT**********\n"); 
    PrintLinkedList(list, stdout);
    
/*
    FILE *fp = fopen("/root/ics53/hw2/rsrc/test_history_1.txt", "r");
    printf("**********3 List Value**********\n"); 
    parseInputRecent(list, fp);
    PrintLinkedList(list, stdout);
    printf("List length: %d", list->length);
    printf("\n");*/

/*  TEST REMOVE
    FindAndRemove(list, (void*)f1);
    printf("**********AFTER REMOVAL**********\n");
    PrintLinkedList(list, stdout);
    printf("List length: %d", list->length);
    printf("\n");  
*/ 
    /*
    printf("\n****Create new EXEnode*****\n");
    char line1[] = "./bin/53markdown  -A < rsrc/sample_1.md";  // edittable copy of string

    printf("bash history line is: %s\n", line1);
    EXEnode* f1 = createEXE(line1, 132);  // info in binary: 10000100

    if(f1 == NULL)
        printf("OOPS!!! Failed to allocate a new EXEnode struct\n");
    else {
        printf("New EXEnode struct? Double check the address on the heap using proc map\n");
    }
        
    printf("\n****Compare EXEnode by ASCII ABC: before*****\n");
    EXEnode f2 = {"a.out",8,2,7,{2,0,1}};   // f2 struct is initialized with static string
    EXEnode f3 = {"a1.out",0,0,0,{0,0,0}};  // f4 struct is initialized with static string

    int success = EXEabcComparator(&f2, &f3);
    if(success == -1)
        printf("EXEnode f2 (%s) is before EXEnode f3 (%s)\n", f2.executable, f3.executable);
    else if (success == 1)
        printf("EXEnode f2 (%s) is after EXEnode f3 (%s)\n", f2.executable, f3.executable);
    else if (success == 0)
        printf("EXEnode f2 (%s) equal to EXEnode f3 (%s)\n", f2.executable, f3.executable);
    else
        printf("OOPS invalid return value");

    printf("\n****Compare EXEnode by ASCII ABC: after*****\n");
    success = EXEabcComparator(&f3, &f2);
    if(success == -1)
        printf("EXEnode f3 (%s) is before EXEnode f2 (%s)\n", f3.executable, f2.executable);
    else if (success == 1)
        printf("EXEnode f3 (%s) is after EXEnode f2 (%s)\n", f3.executable, f2.executable);
    else if (success == 0)
        printf("EXEnode f3 (%s) equal to EXEnode f2 (%s)\n", f3.executable, f2.executable);
    else
        printf("OOPS invalid return value");

    printf("\n****Print EXEnode at different levels*****\n");
    node_t n = {f1, NULL, NULL};
    EXEnode1Print(n.data, stdout);
    printf("\n");
    EXEnode2Print(n.data, stdout);
    printf("\n");
    EXEnode3Print(n.data, stdout);
    printf("\n");

    updateEXE(f1, 177);   // info in binary: 10110001
    EXEnode3Print(n.data, stdout);
    printf("\n");
    updateEXE(f1, 135);   // info in binary: 10000111
    EXEnode3Print(n.data, stdout);
    printf("\n");
    */
    return 0;
}
