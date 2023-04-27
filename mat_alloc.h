//
// Created by frand on 18.04.23.
//

#include <stdio.h>
#include <stdlib.h>

#ifndef PC2_MAT_ALLOC_H
#define PC2_MAT_ALLOC_H

int** mat_alloc(int m, int n) {
    int **A = (int **)malloc(m * sizeof(int *));
    if (A == NULL)
    {
        fprintf(stderr, "out of memory\n");
        exit(0);
    }

    *A = (int *)malloc( m * n * sizeof(int));
    for (int i = 0; i < m; i++) {
        A[i] = (*A + n*i);
    }

    return A;
}

// nnz = number of non zero values
// DAS ERGIBT KEINEN SINN!
void alloc_spmat(int nnz, int** col, int** row, double **val) {

}

#endif //PC2_MAT_ALLOC_H
