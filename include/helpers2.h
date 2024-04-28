#ifndef HELPERS_2_H
#define HELPERS_2_H
#include "dlinkedlist.h"
#include "hw2.h"

// Declare all helper functions for hw2 in this file

int compareStr(const char* str1, const char* str2);

void convertBinary(unsigned char c, char* binary);

int strLength(const char* str);

node_t* FindInListWithABC(dlist_t* list, void* token);

void removeIgnore(dlist_t* list, FILE* fp);

void FindAndRemoveABC(dlist_t* list, void* token);

void sortListFrequency(dlist_t* oldList);

void swapInDLL(dlist_t* list, int firstIndexToSwap);

#endif