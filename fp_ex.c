#include <stdio.h>
#include <stdint.h>

typedef union v32_union {
    float f;
    uint32_t u;
} v32;

void print_bits (float f) {
    v32 v;
    v.f = f;
    uint32_t mask = 1 << 31;
    do {
        if (mask == 0x40000000 || mask == 0x400000)
            putchar(' ');
        putchar(v.u & mask ? '1' : '0');
    } while (mask >>= 1);
    printf("\n");
}

void main() {
    float a = 3.1415928;
    printf("a = %4.2f, ", a);
    print_bits(a);
}