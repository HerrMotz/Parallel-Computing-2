#include <stdio.h>
#include <stdlib.h>
#include "inner_prod.h"

int main() {
    int* u = malloc(5 * sizeof(int));
    int* v = malloc(5 * sizeof(int));

    // initialise values
    for (size_t i = 0; i < 5; ++i) {
        u[i] = 1;
        v[i] = i;
    }

    // compute
    int b = 0;
    for (size_t j = 0; j < 5; ++j) {
        b += u[j] * v[j];
    }

    // compute with lib
    int size_v = 5;
    double* u2 = malloc(size_v * sizeof(double));
    double* v2 = malloc(size_v * sizeof(double));
    // init
    for (size_t i = 0; i < size_v; ++i) {
        u2[i] = 1;
        v2[i] = (double) i;
    }
    double b2 = inner_product_double_par(size_v, u2, v2);

    printf("example:  %d\n", b);
    printf("with lib par: %f", b2);

    free(u);
    free(v);
}