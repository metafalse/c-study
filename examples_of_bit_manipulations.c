#include <stdio.h>

void displayBits(unsigned);

int main(void) {
    unsigned x;
    printf("Enter an unsigned integer: ");
    scanf("%u", &x);
    displayBits(x);
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
