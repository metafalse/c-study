#include <stdio.h>

void displayBits(unsigned);

int main(void) {
    unsigned number1 = 960;
    printf("The result of left shifting: \n");
    displayBits(number1);
    printf("8 bit positioning using the ");
    printf("left shift operator << is: \n");
    displayBits(number1 << 8);
    printf("The result of right shifting: \n");
    displayBits(number1);
    printf("8 bit positioning using the ");
    printf("Right shift operator >> is: \n");
    displayBits(number1 >> 8);
}

void displayBits(unsigned value) {
    unsigned c, displayMask = 1 << 15;
    printf("%u=", value);
    for (c = 1; c <= 16; c++) {
        putchar(value & displayMask ? '1' : '0');
        value <<= 1;
        if(c % 8 == 0)
            putchar(' ');
    }
    putchar('\n');
}
