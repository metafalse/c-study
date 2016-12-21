#include <stdio.h>
#define ASIZE 15

void swap(int *, int *);
void printarray(int *, int);
void bubblesort(int *, int);

int main() {
    int iar[ASIZE] = {22, 92, 18, 42, 4, 68, 87, 35, 13, 49, 72, 7, 29, 39, 51};
    int increments[] = {5,3,1}, numinc = 3;
    printf("Data in items in original order\n");
    printarray(iar, ASIZE);
    bubblesort(iar, ASIZE);
    printf("\nData in ascending order\n");
    printarray(iar, ASIZE);
}

void swap(int *elem1ptr, int *elem2ptr) {
    int temp;
    temp = *elem1ptr;
    *elem1ptr = *elem2ptr;
    *elem2ptr = temp;
}

void printarray(int *pap, int size) {
    int count;
    for (count = 0; count <= size -1; count++)
        printf("%4d", pap[count]);
}

void bubblesort(int *iap, int size) {
    int pass, i;
    printf("\nCalling Bubble sort\n");
    printf("*****************\n");
    for (pass = 1; pass <= size - 1; pass++) {
        for (i = 0; i <= size - 2; i++)
            if (iap[i] > iap[i + 1])
                swap(&iap[i], &iap[i + 1]);
        printf("\nBubble sort Pass: %d:\n", pass);
        printarray(iap, size);
    }
}
