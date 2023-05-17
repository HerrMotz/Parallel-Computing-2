//
// Created by frand on 05.05.23.
//

#include <stdio.h>

#ifndef PC2_ADD_H
#define PC2_ADD_H

float vec_add(int n, const float *u, const float *v) {
    float b = 0;
    for (size_t i = 0; i < n; ++i) {
        b = u[i] + v[i];
    }
    return b;
}

#endif //PC2_ADD_H
