#include <stdio.h>
#define ASIZE 15

void swap(int *, int *);
void printarray(int *, int);
void shellsort(int *, int, int *, int);

int main() {
    int iar[ASIZE] = {22, 92, 18, 42, 4, 68, 87, 35, 13, 49, 72, 7, 29, 39, 51};
    int increments[] = {5,3,1}, numinc = 3;
    printf("Data in items in original order\n");
    printarray(iar, ASIZE);
    shellsort(iar, ASIZE, increments, numinc);
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

void shellsort(int x[], int n, int increments[], int numinc) {
    int incr, j, k, span, y;
    printf("\nCalling Shell sort\n");
    printf("*****************\n");
    for (incr = 0; incr < numinc; incr++) {
        span = increments[incr];
        for (j = span; j < n; j++) {
            y = x[j];
            for (k = j - span; k >= 0 && y < x[k]; k -= span)
                x[k + span] = x[k];
            x[k + span] = y;
        }
        printf("\nShell sort pass with Increment: %d, span: %d\n", incr, span);
        printarray(x, n);
    }
    printf("\nShell sort finished\n");
}
