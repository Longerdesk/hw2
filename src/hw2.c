#include "hw2.h"
#include "helpers2.h"
#include "dlinkedlist.h"


// Part 1 Functions to implement
char* copyStr(const char* str, char* prefix, char* delimiters) {
    if (str == NULL) {
        return NULL;
    }
    if (*str == '\0') {
        return NULL;
    }
    int hasPrefix = 0;
    int prefixNum = strLength(prefix);
    int currentIndex = -1;
    if (prefix == NULL) {
        currentIndex = 0;
    }
    else {
        do {
            currentIndex++;
            hasPrefix = 0;
            for (int i = 0; i < prefixNum; i++) {
                if (*(str + currentIndex) == *(prefix + i)) {
                    hasPrefix = 1;
                }
            }
        } while (hasPrefix == 1 && *(str + currentIndex) != '\0');
    }
    int startIndex = currentIndex;

    int hasDelimiters = 0;
    int delimitersNum = strLength(delimiters);
    if (delimiters == NULL) {
        while (*(str + currentIndex) != '\0') {
            currentIndex++;
        }
    }
    else {
        currentIndex--;
        do {
            currentIndex++;
            //std::cout << *(str + currentIndex) << std::endl;
            hasDelimiters = 0;
            for (int i = 0; i < delimitersNum; i++) {
                if (*(str + currentIndex) == *(delimiters + i)) {
                    hasDelimiters = 1;
                    //       std::cout << "this is in delimiters" << std::endl;
                }
            }
        } while (hasDelimiters == 0 && *(str + currentIndex) != '\0');
    }
    int endIndex = currentIndex;
    //printf("endIndex of %s is %d\n", str, endIndex);
    //printf("startIndex of %s is %d\n", str, startIndex);
    //std::cout << "start: " << startIndex << ", end: " << endIndex << std::endl;
    currentIndex = startIndex;
    char* returnPointer = (char*)malloc(sizeof(char) * (endIndex - startIndex + 1));
    for (int i = 0; i < (endIndex - startIndex); i++) {
        *(returnPointer + i) = *(str + currentIndex + i);
    }
    *(returnPointer + (endIndex-startIndex)) = '\0';
    //printf("%s\n", returnPointer);
    return returnPointer;
}

char finalChar(const char* str) {
    char lastChar = '\0';
    if (str == NULL) {
        return lastChar;
    }
    int currentIndex = 0;
    char currentChar = *str;
    while (currentChar != '\0') {
        if (currentChar != ' ' && currentChar != '\t' && currentChar != '\r' && currentChar != '\n' && currentChar != '\v' && currentChar != '\f') {
            lastChar = currentChar;
            //std::cout << "This is a char" << std::endl;
        }
        currentIndex++;
        currentChar = *(str + currentIndex);
    }
    return lastChar;
}

char* inStr(char* str, char c) {
    if(str == NULL){
        return NULL;
    }
    char *current = str;
    int countQuote = 0;
    while(*current != '\0'){
        if(*current == '\"'){
            countQuote++;
        }else if(countQuote%2 == 0 && *current == c){
            return current;
        }
        current++;
    }
    return NULL;
}

//cat emoji.md | ./bin/53markdown -K \"the line\" -C 2> stderr.txt
// Part 2 Functions to implement
unsigned char commandInfo(char* line, char** exeName) {
    if (exeName == NULL) {
        return 0;
    }
    else if (*exeName == NULL) {
        return 0;
    }
    unsigned char base = 0;

    //set prefix and delimiters
    char* prefix = (char*)malloc(3 * sizeof(char));
    *prefix = '.';
    *(prefix + 1) = '/';
    *(prefix + 2) = '\0';
    char* delimiters = (char*)malloc(5 * sizeof(char));
    *(delimiters) = '\n';
    *(delimiters + 1) = ' ';
    *(delimiters + 2) = 13;
    *(delimiters + 3) = '\t';
    *(delimiters + 4) = '\0';
    char* exeNameInLine = copyStr(line, prefix, delimiters);
    //check if line has a valid exeName. if not, return 0
    for(int i = 0; i < strLength(exeNameInLine); i++){
        if(64 < *(exeNameInLine + i) && *(exeNameInLine + i) < 90){
            free(prefix);
            free(delimiters);
            free(exeNameInLine);
            return 0;
        }
    }
    *exeName = exeNameInLine;
    //printf("store %s in exeName\n", *exeName);
    base += 128;
    if(inStr(line, '-') == NULL){
        //printf("NO - in line %s\n", line);
        free(prefix);
        free(delimiters);
        return base;
    }else if(!(*(inStr(line, '-') - 1) == ' ' && (64 < *(inStr(line, '-') + 1) && *(inStr(line, '-') + 1) < 91 ))){
        //printf("NOT VALID in line %s\n", line);
        free(prefix);
        free(delimiters);
        return base;
    }

    if (finalChar(line) == '&') {
        //printf("Detect & in last\n");
        base += 32;
    }
    if (inStr(line, '|') != NULL) {
        base += 16;
    }
    if (inStr(line, '<') != NULL) {
        if (*(inStr(line, '<') - 1) == ' ') {
            base += 4;
        }
    }
    int foundOutErr = 0;
    if (inStr(line, '&') != NULL) {
        if (*(inStr(line, '&') - 1) == ' ' && *(inStr(line, '&') + 1) == '>') {
            base += 3;
            foundOutErr = 1;
        }
    }
    if (inStr(line, '>') != NULL && foundOutErr == 0) {
        if (*(inStr(line, '>') - 1) == ' ') {
            base += 2;
        }
    }
    if (inStr(line, '2') != NULL && foundOutErr == 0) {
        if (*(inStr(line, '2') - 1) == ' ' && *(inStr(line, '2') + 1) == '>') {
            base += 1;
        }
    }
    free(prefix);
    free(delimiters);
    return base;
}

EXEnode* createEXE(char* exeName, unsigned char info) {
    //printf("CREATE EXEnode of [%s]\n", exeName);
    char* infoBinary = (char*)malloc(9 * sizeof(char));
    convertBinary(info, infoBinary);
    EXEnode* infoStruct = (EXEnode*)malloc(sizeof(EXEnode));
    //7
    if (*infoBinary == 48) {
        free(infoStruct);
        free(infoBinary);
        return NULL;
    }
    else if (*infoBinary == 49) {
        infoStruct->executable = exeName;
        infoStruct->totalCount = 1;
    }
    infoBinary++;
    //6
    if (*infoBinary != 48) {
        free(infoStruct);
        free(infoBinary);
        return NULL;
    }
    infoBinary++;
    //5
    if (*infoBinary == 49) {
        infoStruct->numBackground = 1;
    }
    else {
        infoStruct->numBackground = 0;
    }
    infoBinary++;
    //4
    if (*infoBinary == 49) {
        infoStruct->numPiped = 1;
    }
    else {
        infoStruct->numPiped = 0;
    }
    infoBinary++;
    //3
    if (*infoBinary != 48) {
        free(infoStruct);
        free(infoBinary);
        return NULL;
    }
    infoBinary++;
    //2
    if (*infoBinary == 49) {
        infoStruct->r.inCount = 1;
    }
    else {
        infoStruct->r.inCount = 0;
    }
    infoBinary++;
    //1
    if (*infoBinary == 49) {
        infoStruct->r.outCount = 1;
    }
    else {
        infoStruct->r.outCount = 0;
    }
    infoBinary++;
    //0
    if (*infoBinary == 49) {
        infoStruct->r.errCount = 1;
    }
    else {
        infoStruct->r.errCount = 0;
    }
    infoBinary -= 7;
    free(infoBinary);
    return infoStruct;
}

void updateEXE(EXEnode* node, unsigned char info) {
    char* infoBinary = (char*)malloc(9 * sizeof(char));
    convertBinary(info, infoBinary);
    if (*infoBinary == 49) {
        node->totalCount += 1;
        infoBinary++;
        infoBinary++;
        if (*infoBinary == 49) {
            node->numBackground += 1;
        }
        infoBinary++;
        if (*infoBinary == 49) {
            node->numPiped += 1;
        }
        infoBinary++;
        infoBinary++;
        if (*infoBinary == 49) {
            node->r.inCount += 1;
        }
        infoBinary++;
        if (*infoBinary == 49) {
            node->r.outCount += 1;
        }
        infoBinary++;
        if (*infoBinary == 49) {
            node->r.errCount += 1;
        }
    }    
    infoBinary -= 7;
    free(infoBinary);
}

int EXEabcComparator(const void* node1, const void* node2) {
    //printf("Node1: %s\n",((EXEnode*)node1)->executable);
    //printf("Node2: %s\n", ((EXEnode*)node2)->executable);
    int currentIndex = 0;
    while (*((((EXEnode*)node1)->executable) + currentIndex) != '\0') {
        //printf("n1: %d\n",(*((((EXEnode*)node1)->executable) + currentIndex)));
        //printf("n2: %d\n",(*((((EXEnode*)node2)->executable) + currentIndex)));
        if ((*((((EXEnode*)node1)->executable) + currentIndex)) > *((((EXEnode*)node2)->executable) + currentIndex)) {
           // printf("These are different1\n");
            return 1;
        }
        else if (*((((EXEnode*)node1)->executable) + currentIndex) < *((((EXEnode*)node2)->executable) + currentIndex)) {
           // printf("These are different2\n");
            return -1;
        }
        currentIndex++;
    }
    if (*((((EXEnode*)node1)->executable) + currentIndex) > *((((EXEnode*)node2)->executable) + currentIndex)) {
           // printf("These are different3\n");
        return 1;
    }
    else if (*((((EXEnode*)node1)->executable) + currentIndex) < *((((EXEnode*)node2)->executable) + currentIndex)) {
          //  printf("These are different4\n");
        return -1;
    }
    else {
       // printf("These are the same\n");
        return 0;
    }
}

void EXEnode1Print(void* data, FILE* fp) {
    EXEnode* node = (EXEnode*)data;
    if(node != NULL)
        fprintf(fp, "%s (%d)", node->executable, (int)node->totalCount);
}

void EXEnode2Print(void* data, FILE* fp) {
    EXEnode* node = (EXEnode*)data;
    if(node != NULL){
        int totalCount = node->totalCount;
        int executableLength = strLength(node->executable);
        char* outputStr = (char*)malloc((totalCount+executableLength) + 2);
        for (int i = 0; i < totalCount; i++) {
            *(outputStr + i) = '*';
        }
        *(outputStr + totalCount) = ' ';
        for (int i = 0; i < executableLength; i++) {
            *(outputStr + totalCount + i + 1) = *(node->executable + i);
        }
        *(outputStr + totalCount + executableLength + 1) = '\0';
        fprintf(fp, "%s", outputStr);
        free(outputStr);
    }
}

void EXEnode3Print(void* data, FILE* fp) {
    EXEnode* node = (EXEnode*)data;
    if(node != NULL){
        fprintf(fp, "%s, total:%d, &:%d, |:%d, in:%d, out:%d, err:%d", node->executable,
        (int)node->totalCount, (int)node->numBackground, (int)node->numPiped,
        (int)node->r.inCount, (int)node->r.outCount, (int)node->r.errCount);
    }
}

void EXEnodeDeleter(void* data) {
    if (data != NULL) {
        if(((EXEnode*)data)->executable != NULL){
            free(((EXEnode*)data)->executable);
        }
        free(((EXEnode*)data));
    }
}

node_t* FindInList(dlist_t* list, void* token) {
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
            if (list->comparator(currentNode->data, x) == 0) {
                return currentNode;
            }
            else {
                currentNode = currentNode->next;
            }
        }
    }
    return NULL;
}

void DestroyLinkedList(dlist_t** list) {
    if (list == NULL) {
        return;
    }if (*list == NULL) {
        return;
    }
    node_t* currentNode = (*list)->head;
    if ((*list)->length == 1) {
        EXEnodeDeleter(currentNode->data);
        free(currentNode);
        free(*list);
        return;
    }else {
        node_t* nextNode = (*list)->head->next;

        for (int i = 0; i < ((*list)->length) - 1; i++) {
            EXEnodeDeleter(currentNode->data);
            free(currentNode);
            currentNode = nextNode;
            nextNode = nextNode->next;
        }
        EXEnodeDeleter(currentNode->data);
        free(currentNode);
        free(nextNode);
        free(*list);
    }
}

// Part 3 Functions to implement
int parseInput(dlist_t* list, FILE* fp) {
    int bufferSize = 256;
    unsigned char info = 0;
    int count = 0;
    char* buffer = (char*)malloc(bufferSize);
    char* exeName = (char*)malloc(bufferSize);
    free(exeName);
    node_t* nodeFound = (node_t*)malloc(sizeof(node_t));
    free(nodeFound);
    while(fgets(buffer, bufferSize, fp) != NULL){
        info = commandInfo(buffer, &exeName);
        EXEnode* newEXEnode = (EXEnode*)malloc(sizeof(EXEnode));
        free(newEXEnode);
        newEXEnode = createEXE(exeName, info);
        nodeFound = FindInListWithABC(list, newEXEnode);
        if (nodeFound == NULL) {
            InsertInOrder(list, newEXEnode);
        }
        else {
            updateEXE((EXEnode*)(nodeFound->data), info);
            EXEnodeDeleter(newEXEnode);
        }
        count++;
    }
    free(buffer);
    return count;
}

int EXEcntComparator(const void* node1, const void* node2) {
    if(node1 == NULL || node2 == NULL){
        return 0;
    }
    if(((EXEnode*)node1)->totalCount < ((EXEnode*)node2)->totalCount){
    //    printf("return 1.\n%s: %f, %s: %f\n", ((EXEnode*)node1)->executable, ((EXEnode*)node1)->totalCount, ((EXEnode*)node2)->executable, ((EXEnode*)node2)->totalCount);
        return 1;
    }else if(((EXEnode*)node1)->totalCount > ((EXEnode*)node2)->totalCount){
    //    printf("return -1.\n%s: %f, %s: %f\n", ((EXEnode*)node1)->executable, ((EXEnode*)node1)->totalCount, ((EXEnode*)node2)->executable, ((EXEnode*)node2)->totalCount);
        return -1;
    }else{
        return EXEabcComparator(((EXEnode*)node1), ((EXEnode*)node2));
    }
}

// Part 4 Functions to implement
void* FindAndRemove(dlist_t* list, void* token) {
    if(list == NULL || token == NULL){
        return NULL;
    }
    node_t* nodeFound = FindInList(list, token);
    if(nodeFound == NULL){
        return NULL;
    }
    if(list->comparator(list->head, nodeFound) == 0){
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
    return (void*)returnEXEnode;
}

int parseInputRecent(dlist_t* list, FILE* fp) {
    int bufferSize = 256;
    unsigned char info = 0;
    int count = 0;
    char* buffer = (char*)malloc(bufferSize);
    char* exeName = (char*)malloc(bufferSize);
    free(exeName);
    node_t* nodeFound = (node_t*)malloc(sizeof(node_t));
    free(nodeFound);
    while(fgets(buffer, bufferSize, fp) != NULL){
        EXEnode* newEXEnode = (EXEnode*)malloc(sizeof(EXEnode));
        free(newEXEnode);
        info = commandInfo(buffer, &exeName);
        newEXEnode = createEXE(exeName, info);
        //printf("try to input %s\n", exeName);
        nodeFound = FindInListWithABC(list, newEXEnode);
        if (nodeFound == NULL) {
           // printf("not found in list\n");
            InsertAtHead(list, newEXEnode);
        }
        else {
           // printf("found in list\n");
            updateEXE((EXEnode*)(nodeFound->data), info);
            if(list->comparator(list->head->data, nodeFound->data) != 0){//if node not head, move to head
                nodeFound->prev->next = nodeFound->next;
                if(nodeFound->next != NULL){
                    nodeFound->next->prev = nodeFound->prev;
                }
                nodeFound->next = list->head;
                nodeFound->prev = NULL;
                list->head->prev = nodeFound;
                list->head = nodeFound;
            }
            EXEnodeDeleter(newEXEnode);
        }
        count++;
    }
    free(buffer);
    return count;
}

void PrintNLinkedList(dlist_t* list, FILE* fp, int NUM) {
    if(list == NULL)
        return;

    node_t* head = list->head;
    int actualNum = NUM;
    if(NUM > list->length){
        actualNum = list->length;
    }
    for(int i = 0; i < actualNum; i++) {
        list->printer(head->data, fp);
        fprintf(fp, "\n");
        head = head->next;
    }
}

void stats(dlist_t* list, int NUM) {
	double sumTotalCount = 0;
    double countBackground = 0;
    double countPiped = 0;
    double countInput = 0;
    double countOutput = 0;
    double countError = 0;
    node_t* currentNode = list->head;
    int actualNum = NUM;
    if(list->length < NUM)
        actualNum = list->length;

    for(int i = 0; i < actualNum; i++){
        sumTotalCount += (double)(((EXEnode*)(currentNode->data))->totalCount);
        countBackground += ((EXEnode*)(currentNode->data))->numBackground;
        countPiped += ((EXEnode*)(currentNode->data))->numPiped;
        countInput += ((EXEnode*)(currentNode->data))->r.inCount;
        countOutput += ((EXEnode*)(currentNode->data))->r.outCount;
        countError += ((EXEnode*)(currentNode->data))->r.errCount;
        currentNode = currentNode->next;
    }
    fprintf(stderr, "Total number of commands: %d\n", (int)sumTotalCount);
    fprintf(stderr, "Number of unique executables: %d\n", actualNum);
    fprintf(stderr, "Percentage of background commands (&): %.2f%%\n", (countBackground/sumTotalCount)*100);
    fprintf(stderr, "Percentage of piped commands (|): %.2f%%\n", (countPiped/sumTotalCount)*100);
    fprintf(stderr, "Percentage of commands with input redirection (<): %.2f%%\n", (countInput/sumTotalCount)*100);
    fprintf(stderr, "Percentage of commands with output redirection (>): %.2f%%\n", (countOutput/sumTotalCount)*100);
    fprintf(stderr, "Percentage of commands with error redirection (2>): %.2f%%\n", (countError/sumTotalCount)*100);
}


