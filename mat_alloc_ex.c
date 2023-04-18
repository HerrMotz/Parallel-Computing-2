//
// Created by frand on 18.04.23.
//

#include <stdio.h>
#include <stdlib.h>
#define M 4
#define N 5

#include "mat_alloc.h"

int main()
{
    int **A = (int **)malloc(M * sizeof(int *));
    if (A == NULL)
    {
        fprintf(stderr, "out of memory\n");
        exit(0);
    }
    *A = (int *)malloc( M * N * sizeof(int));
    for (int i = 0; i < M; i++) {
        A[i] = (*A + N*i);
    }

    A[0][0] = 2;
    A[3][4] = 3;

    printf("A_0,0: %d\n", A[0][0]);
    printf("A_4,5: %d\n", A[3][4]);

    free(*A);
    free(A);

    A = (int **) mat_alloc(M, N);
    A[3][4] = 1;
    printf("A_4,5: %d", A[3][4]);

    return 0;
}