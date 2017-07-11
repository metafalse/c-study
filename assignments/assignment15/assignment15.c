/******************************************************************************/
/*                                                                            */
/*  Topic: Hashing                                                            */
/*                                                                            */
/*  Objective: Implement a hash table using the Separate Chaining             */
/*                                                                            */
/*  Comments: Hashtable with the Separate Chaining is an array of linked list */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define HASHTABLESIZE 15
#define INFILENAME "input15.doc"
#define OUTFILENAME "output15.doc"

struct listnode {
    int key;
    int record;
    struct listnode *nextptr;
};
typedef struct listnode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

int hash(int);
void insert(LISTNODEPTR *, int, int);
void printHashTable(LISTNODEPTR *);
int pfprintf(FILE *, const char *, ...);

FILE *pIn, *pOut;
LISTNODEPTR hashTable[HASHTABLESIZE];

int main() {
    int key, record, hashkey;

    // open input and output file
    if ((pIn = fopen(INFILENAME, "r")) == NULL) {
        printf("%s could not be opend\n", INFILENAME);
        return -1;
    }
    if ((pOut = fopen(OUTFILENAME, "w")) == NULL) {
        printf("%s could not be opend\n", OUTFILENAME);
        return -1;
    }

    // scan entries from the input file into the hash table
    while (fscanf(pIn, "%d", &key) != EOF && fscanf(pIn, "%d", &record) != EOF) {
        hashkey = hash(key); // make key hashed
        pfprintf(pOut, "Read key:%d record:%d: hash key:%d\n", key, record, hashkey);
        insert(&hashTable[hashkey], key, record);
    }

    pfprintf(pOut, "\nContents of the hash table\n");
    printHashTable(hashTable);

    fclose(pIn);
    fclose(pOut);
}

int hash(int key) {
    int sum = 0;

    while (key > 0) {
        sum += key % 10;
        key /= 10;
    }
    return sum % HASHTABLESIZE;
}

void insert(LISTNODEPTR *sptr, int key, int record) {
    LISTNODEPTR newptr, currptr;
    newptr = (LISTNODEPTR) malloc(sizeof(LISTNODE));

    if (newptr == NULL) {
        pfprintf(pOut, "key %d not inserted. No memory is available\n", key);
        exit(1);
    }

    newptr->key = key;
    newptr->record = record;
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

void printHashTable(LISTNODEPTR *hashTablePtr) {
    LISTNODEPTR currptr;

    for (int i = 0; i < HASHTABLESIZE; i++) {
        if (hashTablePtr[i] == NULL)  {
            pfprintf(pOut, "HashTable[%d] -> NULL\n\n", i);
            continue;
        }

        currptr = hashTablePtr[i];

        pfprintf(pOut, "hashTable[%d] -> ", i);
        while (currptr != NULL) {
            pfprintf(pOut, "key:%d record:%d -> ", currptr->key, currptr->record);
            currptr = currptr->nextptr;
        }
        pfprintf(pOut, "NULL\n\n");
    }
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
