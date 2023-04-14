//
// Created by frand on 14.04.23.
//

#include <stdio.h>

#ifndef PC2_INNER_PROD_H
#define PC2_INNER_PROD_H

double inner_product_double(int n, const double *u, const double *v) {
    double b = 0;
    for (size_t i = 0; i < n; ++i) {
        b += u[i] * v[i];
    }
    return b;
}

int inner_product_int(int n, const int *u, const int *v) {
    int b = 0;
    for (size_t i = 0; i < n; ++i) {
        b += u[i] * v[i];
    }
    return b;
}

#endif //PC2_INNER_PROD_H
