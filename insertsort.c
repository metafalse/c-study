#include <stdio.h>
#define ASIZE 15

void swap(int *, int *);
void printarray(int *, int);
void insertsort(int *, int);

int main() {
    int iar[ASIZE] = {22, 92, 18, 42, 4, 68, 87, 35, 13, 49, 72, 7, 29, 39, 51};
    int increments[] = {5,3,1}, numinc = 3;
    printf("Data in items in original order\n");
    printarray(iar, ASIZE);
    insertsort(iar, ASIZE);
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

void insertsort(int x[], int n) {
    int i, k, y;
    printf("\nCalling Insertion sort\n");
    printf("*****************\n");
    for (k = 1; k < n; k++) {
        y = x[k];
        for (i = k - 1; i >= 0 && y < x[i]; i--)
            x[i + 1] = x[i];
        printf("\nInsertion sort Pass: %d: \n", k);
        x[i + 1] = y;
        printarray(x, n);
    }
}
