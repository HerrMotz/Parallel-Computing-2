#include <stdio.h>
#include <stdlib.h>
#include "vec_add.h"
#include <time.h>

int main() {
    int size_v = 1000000;

    float* u = malloc(size_v * sizeof(double));
    float* v = malloc(size_v * sizeof(double));


    for (size_t i = 0; i < size_v; ++i) {
        u[i] = 1;
        v[i] = (float) i;
    }

    clock_t start = clock();
    float b = vec_add(size_v, u, v);
    clock_t end = clock();

    printf("result: %10f\ntime: %10lf ms\ntime: %10ld clock cycles", b, (end - start) / (CLOCKS_PER_SEC / 1000.0f), end-start);

    free(u);
    free(v);
}