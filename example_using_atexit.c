#include<stdio.h>
#include<stdlib.h>

void print();
int main() {
    int answer;
    atexit(print);
    printf("Enter 1 to terminate program with function exit\n" "Enter 2 to terminate program normally\n");
    scanf("%d", &answer);
    if (answer == 1) {
        printf("\nTerminating program with function exit\n");
        exit(EXIT_SUCCESS);
    }
    printf("\nTerminating program by reaching the end of main\n");
}

void print() {
    printf("Executing function print at program termination\n" "Program terminated\n");
}
