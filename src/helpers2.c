// Define all helper functions for hw2 in this file
#include "helpers2.h"
#include <stdlib.h>


int compareStr(const char* str1, const char* str2) {
    int length1 = strLength(str1);
    int length2 = strLength(str2);
    if (length1 != length2) {
        return 0;
    }
    int currentIndex = 0;
    while (*(str1 + currentIndex) != '\0') {
        if (*(str1 + currentIndex) != *(str2 + currentIndex)) {
            return 0;
        }
        currentIndex++;
    }
    //if (*(str1 + currentIndex) != *(str2 + currentIndex)) {
    //    return 0;
    //}
    //else {
        return 1;
    //}
}

void convertBinary(unsigned char c, char* binary) {
    int num = (int)c;
    binary += 8;
    *binary = '\0';
    binary--;
    for (int i = 0; i < 8; i++) {
        *(binary - i) = (char)((num % 2)+48);
        num = num / 2;
    }
}


int strLength(const char* str) {
    int currentIndex = 0;
    while (*(str + currentIndex) != '\0') {
        currentIndex++;
    }
    return currentIndex;
}


node_t* FindInListWithABC(dlist_t* list, void* token) {
    if (list == NULL) {
        return NULL;
    }
    if (token == NULL) {
        return NULL;
    }
    node_t* currentNode = (list->head);
    EXEnode* x = (EXEnode*)token;
    for (int i = 0; i < list->length; i++) {
        if (currentNode != NULL) {
            if (EXEabcComparator(currentNode->data, x) == 0) {
                return currentNode;
            }
            else {
                currentNode = currentNode->next;
            }
        }
    }
    return NULL;
}

void removeIgnore(dlist_t* list, FILE* fp){
    int bufferSize = 64;
    char* buffer = (char*)malloc(bufferSize);
    char* bufferWithoutNL = NULL;
    char* prefix = (char*)malloc(1);
    *prefix = '\0';
    char* delimiters = (char*)malloc(3);
    *delimiters = '\n';
    *(delimiters + 1) = 13;
    *(delimiters + 2) = '\0';
    while(fgets(buffer, bufferSize, fp) != NULL){
        bufferWithoutNL = copyStr(buffer, prefix, delimiters);
        EXEnode* nodeToIgnore = createEXE(bufferWithoutNL, 128);
        FindAndRemoveABC(list, nodeToIgnore);
        free(bufferWithoutNL);
        free(nodeToIgnore);
    }
    free(buffer);
    free(prefix);
    free(delimiters);
}

void FindAndRemoveABC(dlist_t* list, void* token) {
    if(list == NULL || token == NULL){
        return;
    }
    node_t* nodeFound = FindInListWithABC(list, token);
    if(nodeFound == NULL){
        return;
    }
    if(EXEabcComparator(list->head, nodeFound) == 0){
        list->head = nodeFound->next;
    }else{
        nodeFound->prev->next = nodeFound->next;
        if(nodeFound->next != NULL){
            nodeFound->next->prev = nodeFound->prev;
        }
    }
    EXEnode* returnEXEnode = nodeFound->data;
    free(nodeFound);
    list->length -= 1;
    EXEnodeDeleter(returnEXEnode);
}

void sortListFrequency(dlist_t* list){
    if(list == NULL){
        return;
    }
    int swapped = 0;
    int n = list->length;
    node_t* firstNode = list->head;
    for(int i = 0; i < n-1; i++){
        swapped = 0;
        firstNode = list->head;
        for(int j = 0; j < n - i - 1; j++){
            if(EXEcntComparator(firstNode->data, firstNode->next->data) > 0){
                swapInDLL(list, j);
                swapped = 1;
            }else{
                firstNode = firstNode -> next;
            }
        }
        if(swapped == 0){
            break;
        }
    }
}

void swapInDLL(dlist_t* list, int firstIndexToSwap){
    if(list->length - 1 <= firstIndexToSwap){
        return;
    }
    node_t* firstNode = list->head;
    for(int i = 0; i < firstIndexToSwap; i++){
        firstNode = firstNode->next;
    }
    if(firstIndexToSwap == 0){
        list->head = firstNode->next;
        firstNode->next = list->head->next;
        list->head->next = firstNode;
        firstNode->prev = list->head;
        list->head->prev = NULL;
        if(firstNode->next != NULL){
            firstNode->next->prev = firstNode;
        }
    }else{
        firstNode->prev->next = firstNode->next;
        firstNode->next = firstNode->next->next;
        firstNode->prev->next->next = firstNode;
        firstNode->prev->next->prev = firstNode->prev;
        firstNode->prev = firstNode->prev->next;
        if(firstNode->next != NULL){
            firstNode->next->prev = firstNode;
        }
    }
}