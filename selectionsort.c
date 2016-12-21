#include <stdio.h>
#define ASIZE 15

void swap(int *, int *);
void printarray(int *, int);
void selectionsort(int *, int);

int main() {
    int iar[ASIZE] = {22, 92, 18, 42, 4, 68, 87, 35, 13, 49, 72, 7, 29, 39, 51};
    printf("Data in items in original order\n");
    printarray(iar, ASIZE);
    selectionsort(iar, ASIZE);
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

void selectionsort(int numbers[], int array_size) {
    int i, j;
    int min, temp;
    printf("\nCalling Selection sort\n");
    printf("*****************\n");
    for (i = 0; i < array_size - 1; i++) {
        min = i;
        for (j = i + 1; j < array_size; j++) {
            if (numbers[j] < numbers[min])
                min = j;
        }
        swap(&numbers[i], &numbers[min]);
        printf("\nSelection sort iteration: %d:\n", i);
        printarray(numbers, ASIZE);
    }
}
