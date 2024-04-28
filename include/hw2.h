// DO NOT MODIFY THIS FILE
// Any additions should be placed in helpers2.h

#ifndef HW_2_H
#define HW_2_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dlinkedlist.h"

typedef struct {
    double inCount;    // Count of commands with < 
    double outCount;   // Count of commands with >  
    double errCount;   // Count of commands with 2> 
} redirection_t;

typedef struct {
    char* executable;     // pointer to the string for the executable program 
    double totalCount;    // Total number of occurrences for executable command 
    double numBackground; // Count of & as last char of command
    double numPiped;      // Count of commands which contain 1+ pipes |
    redirection_t r;        // Fields for collection for redirection statistics
} EXEnode;

// Part 1 Functions to implement
char* copyStr(const char*, char*, char*);
char finalChar(const char* );
char* inStr(char*, char);

// Part 2 Functions to implement
unsigned char commandInfo(char*, char**);
EXEnode* createEXE(char*, unsigned char);
void updateEXE(EXEnode*, unsigned char );
int EXEabcComparator(const void*, const void*);
void EXEnode1Print(void*, FILE*);
void EXEnode2Print(void*, FILE*);
void EXEnode3Print(void*, FILE*);
void EXEnodeDeleter(void*);
node_t* FindInList(dlist_t*, void*);
void DestroyLinkedList(dlist_t**);

// Part 3 Functions to implement
int parseInput(dlist_t*, FILE*);
int EXEcntComparator(const void*, const void*);

// Part 4 Functions to implement
void* FindAndRemove(dlist_t*, void*);
int parseInputRecent(dlist_t*, FILE* );
void PrintNLinkedList(dlist_t*, FILE*, int);
void stats(dlist_t* list, int NUM);



#endif
