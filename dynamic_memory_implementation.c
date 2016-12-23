#include <stdio.h>
#include <stdlib.h>

struct listnode {
    char data;
    struct listnode *nextptr;
};
typedef struct listnode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

void insert(LISTNODEPTR *, char);
char delete(LISTNODEPTR *, char);
int isempty(LISTNODEPTR);
void printlist(LISTNODEPTR);
void instructions(void);

int main() {
    LISTNODEPTR startptr = NULL;
    int choice;
    char item;
    instructions();
    printf("? ");
    scanf("%d", &choice);
    while (choice != 3) {
        switch (choice) {
            case 1:
                printf("Enter a character: ");
                scanf("\n%c", &item);
                insert(&startptr, item);
                printlist(startptr);
                break;
            case 2:
                if (!isempty(startptr)) {
                    printf("Enter a character to be deleted: ");
                    scanf("\n%c", &item);
                    if (delete(&startptr, item)) {
                        printf("%c deleted.\n", item);
                        printlist(startptr);
                    }
                    else
                        printf("%c not found.\n\n", item);
                }
                else
                    printf("List is empty.\n\n");
                    break;
            default:
                printf("Enter a character to be deleted: ");
                instructions();
                break;
        }
        printf("? ");
        scanf("%d", &choice);
    }
    printf("End of run.\n");
}

void instructions() {
    printf("\nEnter your choice:\n");
    printf("1 to insert an element into the list.\n");
    printf("2 to delete an element from the list.\n");
    printf("3 to end.\n");
}

int isempty(LISTNODEPTR sptr) {
    return sptr == NULL;
}

void insert(LISTNODEPTR *sptr, char value) {
    LISTNODEPTR newptr, prevptr, currptr;
    newptr = (LISTNODEPTR) malloc(sizeof(LISTNODE));
    
    if (newptr != NULL) {
        newptr->data = value;
        newptr->nextptr = NULL;
        prevptr = NULL;
        currptr = *sptr;
        while (currptr != NULL && value > currptr->data) {
            prevptr = currptr;
            currptr = currptr->nextptr;
        }
        if (prevptr == NULL) {
            newptr->nextptr = *sptr;
            *sptr = newptr;
        }
        else {
            prevptr->nextptr = newptr;
            newptr->nextptr = currptr;
        }
    }
    else
        printf("%c not inserted. No memory is available\n", value);
}

char delete (LISTNODEPTR *sptr, char value) {
    LISTNODEPTR prevptr, currptr, tempptr;
    if (value == (*sptr)->data) {
        tempptr = *sptr;
        *sptr = (*sptr)->nextptr;
        free(tempptr);
        return value;
    }
    else {
        prevptr = *sptr;
        currptr = (*sptr)->nextptr;
        while (currptr != NULL && currptr->data != value) {
            prevptr = currptr;
            currptr = currptr->nextptr;
        }
        if (currptr != NULL) {
            tempptr = currptr;
            prevptr->nextptr = currptr->nextptr;
            currptr = currptr->nextptr;
            free(tempptr);
            return value;
        }
    }
    return '\0';
}

void printlist(LISTNODEPTR currptr) {
    if (currptr == NULL) {
        printf("List is empty.\n\n");
    }
    else {
        printf("List is not empty.\n\n");
        while (currptr != NULL) {
            printf("%c --> ", currptr->data);
            currptr = currptr->nextptr;
        }
        printf("NULL\n\n");
    }
}
