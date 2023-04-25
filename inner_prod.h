//
// Created by frand on 14.04.23.
//

#include <stdio.h>
#include <omp.h>
#include <math.h>

#ifndef PC2_INNER_PROD_H
#define PC2_INNER_PROD_H

double inner_product_double(int n, const double *u, const double *v) {
    double b = 0;
    for (size_t i = 0; i < n; ++i) {
        b += u[i] * v[i];
    }
    return b;
}

double inner_product_double_par(int n, const double *u, const double *v) {

    double result = 0;

    printf("num_threads %d num_el %d\n", omp_get_num_threads(), n);

    #pragma omp parallel default(none) shared(result) firstprivate(n, u, v)
    {
        // calculate the number of elements which this thread will handle

        // we have m := N_THREADS threads
        // we compute n elements
        // each thread has to compute r = n/m threads

        int r = ceilf((float)n / (float)omp_get_num_threads());
        double* v_private = malloc(r * sizeof(double));

        int j = 0;
        for (int i = omp_get_thread_num(); i < n; i += omp_get_num_threads()) {
            v_private[j] = u[i] * v[i];
            j++;
            printf("thread: %d, i: %d, j: %d, u_i: %f, v_i: %f\n", omp_get_thread_num(), i, j, u[i], v[i]);
        }


#pragma omp critical
        {
            for (int i = 0; i < r; ++i) {
                result += v_private[i];
                printf("thread: %d, ADD: %d, v_private_j: %f\n", omp_get_thread_num(), i, v_private[i]);
                printf("result: %f\n", result);
            }
        }
    }

    return result;

// oder man kann es einfacher machen:
//#pragma omp parallel for reduction(+:sum)
//    for (int i = 0; i < num_steps; i++) {
//        double x = (i + 0.5) * width; // midpoint
//        sum = sum + (1.0 / (1.0 + x * x)); // add new height of a rectangle
//    }
}

int inner_product_int(int n, const int *u, const int *v) {
    int b = 0;
    for (size_t i = 0; i < n; ++i) {
        b += u[i] * v[i];
    }
    return b;
}

#endif //PC2_INNER_PROD_H
