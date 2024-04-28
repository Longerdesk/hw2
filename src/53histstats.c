#include "constants2.h"
#include "helpers2.h"
#include "hw2.h"

int main(int argc, char** argv) {
	int A_flag = 0;
	int F_flag = 0;
	int U_flag = 0;
    int NUM_arg = 0;
	int p_flag = 0;
    int LEVEL_arg = 0;
	int s_flag = 0;
    char* OUTFILE = NULL;
    char* IGNOREFILE = NULL;

    // Use basic getopt to parse flags and respective arguments
    int option;
    while ((option = getopt(argc, argv, "AFU:o:i:p:sh" )) != -1) {
        switch (option) {
            case 'h':
				fprintf(stdout, USAGE_MSG);
				return EXIT_SUCCESS;
            case 'A':
                A_flag = 1;
                break;
            case 'F':
				F_flag = 1;
                break;
            case 'U':
                U_flag = 1;
				NUM_arg = atoi(optarg);
                break;
            case 'p':
                p_flag = 1;
				LEVEL_arg = atoi(optarg);
                break;
            case 's':
				s_flag = 1;
                break;
            case 'o':
				OUTFILE = optarg;
                break;
            case 'i':
				IGNOREFILE = optarg;
                break;
            default:
                fprintf(stderr, USAGE_MSG);
                return EXIT_FAILURE;
        }
    }

    // validate a required option was specified - Does not check for more than 1
    if ( !(A_flag | F_flag | U_flag) )
    {
        fprintf(stderr, "ERROR: Required option was not specified.\n\n" USAGE_MSG);
        return EXIT_FAILURE;
    } 
    if((A_flag == 1 && F_flag == 1) || (A_flag == 1 && U_flag == 1) || (F_flag == 1 && U_flag == 1)){
        fprintf(stderr, USAGE_MSG);
        return 2;
    }
    // getopts only stored the arguments and performed basic checks. More error checking is still needed!!!!
    
    //invalid p flag arg
    if(p_flag == 1 && (!(LEVEL_arg == 1 || LEVEL_arg == 2 || LEVEL_arg == 3))){
        fprintf(stderr, USAGE_MSG);
        return 2;
    }
    if(U_flag == 1 && (NUM_arg < 0)){
        fprintf(stderr, USAGE_MSG);
        return 2;
    }
    //o option 
    FILE *fpOut = stdout;
    if(OUTFILE != NULL){
        fpOut = fopen(OUTFILE, "w");
        if(fpOut == NULL){
            fprintf(stderr, USAGE_MSG);
            return 1;
        }
    }
    FILE *fpIgnore = NULL;
    if(IGNOREFILE != NULL){
        fpIgnore = fopen(IGNOREFILE, "r");
        if(fpIgnore == NULL){
            fprintf(stderr, USAGE_MSG);
            return 1;
        }
    }

    dlist_t* list = CreateList(&EXEabcComparator, &EXEnode1Print, &EXEnodeDeleter);
    if(A_flag == 1){
        if(p_flag == 1){
            if(LEVEL_arg == 2){
                list -> printer = &EXEnode2Print;
            }else if(LEVEL_arg == 3){
                list -> printer = &EXEnode3Print;
            }
        }
        parseInput(list, stdin);
        if(IGNOREFILE != NULL){
            removeIgnore(list, fpIgnore);
        }
        PrintLinkedList(list, fpOut);
        if(s_flag == 1){
            stats(list, list->length);
        }
        DestroyLinkedList(&list);
    }else if(F_flag == 1){
        if(p_flag == 1){
            if(LEVEL_arg == 2){
                list -> printer = &EXEnode2Print;
            }else if(LEVEL_arg == 3){
                list -> printer = &EXEnode3Print;
            }
        }
        parseInput(list, stdin);
        if(IGNOREFILE != NULL){
            removeIgnore(list, fpIgnore);
        }
        sortListFrequency(list);
        PrintLinkedList(list, fpOut);
        if(s_flag == 1){
            stats(list, list->length);
        }
        DestroyLinkedList(&list);
    }else if(U_flag == 1){
        if(p_flag == 1){
            if(LEVEL_arg == 2){
                list -> printer = &EXEnode2Print;
            }else if(LEVEL_arg == 3){
                list -> printer = &EXEnode3Print;
            }
        }  
        parseInputRecent(list, stdin);
        if(IGNOREFILE != NULL){
            removeIgnore(list, fpIgnore);
        }
        if(NUM_arg == 0){
            NUM_arg = list->length;
        }
        PrintNLinkedList(list, fpOut, NUM_arg);
        if(s_flag == 1){
            stats(list, list->length);
        }
        DestroyLinkedList(&list);
    }
    return 0;
}
