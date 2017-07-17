/******************************************************************************/
/*                                                                            */
/*  Topic: Long Integer                                                       */
/*                                                                            */
/*  Objective: Add two long integers using linked lists                       */
/*                                                                            */
/*  Comments: Utilized remainder and quotient after dividing the sum by 10000 */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#define BUFSIZE 50
#define NODEDIGITS 4
#define TRUE 1
#define FALSE 0
#define INFILENAME "input18.doc"
#define OUTFILENAME "output18.doc"

struct listnode {
    int data;
    struct listnode *nextptr;
};
typedef struct listnode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

void read(LISTNODEPTR *);
LISTNODEPTR add(LISTNODEPTR, LISTNODEPTR);
bool isempty(LISTNODEPTR);
void insert(LISTNODEPTR *, int);
int delete(LISTNODEPTR *);
void reverse(LISTNODEPTR *);
void printlist(LISTNODEPTR);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;

int main() {
    LISTNODEPTR list1ptr = NULL, list2ptr = NULL, resulistptr = NULL;

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    // read two long integer inputs from an input file into two linked lists
    read(&list1ptr);
    read(&list2ptr);

    pfprintf(pOut, "list1 :");
    printlist(list1ptr);
    pfprintf(pOut, "list2 :");
    printlist(list2ptr);

    resulistptr = add(list1ptr, list2ptr);
    pfprintf(pOut, "result:");
    printlist(resulistptr);

    fclose(pIn);
    fclose(pOut);
}

// read the input from the input file into the linked list
void read(LISTNODEPTR *sptr) {
    char buf[BUFSIZE];
    char tmp[NODEDIGITS + 1]; // assuming '\0'
    int length, remain, pos = 0;

    fscanf(pIn, "%s\n", buf);
    length = strlen(buf);
    remain = length % NODEDIGITS;

    while (pos < length) {
        if (remain > 0 && pos < remain) { // if there will be a list node that have digits less than NODEDIGITS
            strncpy(tmp, buf, remain);
            tmp[remain] = '\0';
            pos = pos + remain;
        }
        else { // list node with NODEDIGITS digits
            strncpy(tmp, buf + pos, NODEDIGITS);
            pos = pos + NODEDIGITS;
        }
        insert(sptr, atoi(tmp));
    }
}

// return a linked list with number added of the two linked list of long integer
LISTNODEPTR add(LISTNODEPTR sptr1, LISTNODEPTR sptr2) {
    LISTNODEPTR resulistptr = NULL;
    int sum = 0;

    while (!isempty(sptr1) || !isempty(sptr2)) {
        sum += delete(&sptr1) + delete(&sptr2);
        insert(&resulistptr, sum % 10000); // insert the ramainder after dividing sum by 10,000 into result list
        sum = sum / 10000; // if sum is greater than 9999, 1 is added into next sum
    }
    reverse(&resulistptr); // reverse the linked list to be displayed in desired order

    return resulistptr;
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

// delete node of the bottom from the linked list
int delete(LISTNODEPTR *sptr) {
    LISTNODEPTR prevptr, currptr, tempptr;
    int tempdata;

    if (*sptr == NULL) // if list is empty
        return 0;

    if ((*sptr)->nextptr == NULL) { // if top node is the bottom
        tempdata = (*sptr)->data;
        tempptr = *sptr;
        *sptr = NULL;

        free(tempptr);
        return tempdata;
    }

    prevptr = *sptr;
    currptr = (*sptr)->nextptr;

    while (currptr->nextptr != NULL) {
        prevptr = currptr;
        currptr = currptr->nextptr;
    }
    tempdata = currptr->data;
    prevptr->nextptr = NULL;

    free(currptr);
    return tempdata;
}

// reverse contents of the linked list
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
    char result[61];
    char tmp[NODEDIGITS + 2]; // assuming '\0'

    // initialize output string buffer by '\0'
    memset(result, '\0', strlen(result));
    memset(tmp, '\0', strlen(tmp));

    if (currptr == NULL) {
        pfprintf(pOut, "List is empty.\n\n");
        return;
    }

    // write values of the linked list into output string buffer result
    while (currptr != NULL) {
        sprintf(tmp, " %04d", currptr->data);
        strcat(result, tmp);
        currptr = currptr->nextptr;
    }
    pfprintf(pOut, "%60s\n", result);
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
