/******************************************************************************/
/*                                                                            */
/*  Topic: Linked Lists                                                       */
/*                                                                            */
/*  Objective: Form a linked list with the input numbers from a file          */
/*             and prompt the user for deleting the entries from the list     */
/*                                                                            */
/*  Comments: The code in chapter 24 modified to make it work as desired      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define TRUE 1
#define FALSE 0
#define DEFAULT 9999
#define INFILENAME "input11.doc"
#define OUTFILENAME "output11.doc"

struct listnode {
    int data;
    struct listnode *nextptr;
};
typedef struct listnode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

bool isValidInput(int);
bool isempty(LISTNODEPTR);
void insert(LISTNODEPTR *, int);
char delete(LISTNODEPTR *, int);
void reverse(LISTNODEPTR *);
void printlist(LISTNODEPTR);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;

int main() {
    int item;
    LISTNODEPTR startptr = NULL;

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    printlist(startptr);
    // iteration inserting values into the linked list from the input file
    while (fscanf(pIn, "%d", &item) != EOF) {
        insert(&startptr, item);
        pfprintf(pOut, "%d inserted.\n", item);
        printlist(startptr);
    }

    // reverse the linked list
    pfprintf(pOut, "List is reveresed.\n");
    reverse(&startptr);
    printlist(startptr);

    while (!isempty(startptr)) { // until the linked list is empty
        // prompt user to enter the value to be deleted or quit
        do {
            item = DEFAULT;
            pfprintf(pOut, "Enter a character to be deleted or -1 to quit: ");
            scanf(        "%d",  &item);
            fprintf(pOut, "%d\n", item);
            while (getchar() != '\n')
                continue;
        } while (!isValidInput(item));
        if (item == -1)
            break;

        if (delete(&startptr, item)) {
            pfprintf(pOut, "%d deleted.\n", item);
            printlist(startptr);
        }
        else
            pfprintf(pOut, "%d not found.\n\n", item);
    }

    fclose(pIn);
    fclose(pOut);
}

bool isValidInput(int item) {
    if (item != DEFAULT)
        return TRUE;

    pfprintf(pOut, "invalid input\n");
    return FALSE;
}

bool isempty(LISTNODEPTR sptr) {
    return sptr == NULL;
}

void insert(LISTNODEPTR *sptr, int value) {
    LISTNODEPTR newptr, currptr;
    newptr = (LISTNODEPTR) malloc(sizeof(LISTNODE));
    
    if (newptr == NULL) {
        pfprintf(pOut, "%c not inserted. No memory is available\n", value);
        return;
    }

    newptr->data = value;
    newptr->nextptr = NULL;
    if (*sptr == NULL) {
        *sptr = newptr;
        return;
    }

    currptr = *sptr;
    while (currptr->nextptr != NULL)
        currptr = currptr->nextptr;
    currptr->nextptr = newptr;
}

char delete(LISTNODEPTR *sptr, int value) {
    LISTNODEPTR prevptr, currptr, tempptr;

    if (value == (*sptr)->data) {
        tempptr = *sptr;
        *sptr = (*sptr)->nextptr;
        free(tempptr);
        return value;
    }

    prevptr = *sptr;
    currptr = (*sptr)->nextptr;
    while (currptr != NULL && currptr->data != value) {
        prevptr = currptr;
        currptr = currptr->nextptr;
    }
    if (currptr != NULL) {
        tempptr = currptr;
        prevptr->nextptr = currptr->nextptr;
        free(tempptr);
        return value;
    }

    return '\0';
}

void reverse(LISTNODEPTR *sptr) {
    LISTNODEPTR prevptr, currptr, tempptr;

    if (*sptr == NULL || (*sptr)->nextptr == NULL)
        return;

    currptr = *sptr;

    prevptr = *sptr;
    currptr = (*sptr)->nextptr;
    prevptr->nextptr = NULL;
    tempptr = currptr->nextptr;
    currptr->nextptr = prevptr;

    while (tempptr != NULL) {
        prevptr = currptr;
        currptr = tempptr;
        tempptr = currptr->nextptr;
        currptr->nextptr = prevptr;
    }
    *sptr = currptr;
}

void printlist(LISTNODEPTR currptr) {
    if (currptr == NULL) {
        pfprintf(pOut, "List is empty.\n\n");
        return;
    }

    while (currptr != NULL) {
        pfprintf(pOut, "%d --> ", currptr->data);
        currptr = currptr->nextptr;
    }
    pfprintf(pOut, "NULL\n\n");
}

// a function combining printf and fprintf
int pfprintf(FILE *fp, const char *format, ...) {
    va_list ap;
    int result;

    va_start(ap, format);
    result = vfprintf(fp, format, ap);
    va_end(ap);
    if (fp != stdout && fp != stderr) {
        va_start(ap, format);
        result = vprintf(format, ap);
        va_end(ap);
    }

    return result;
}
