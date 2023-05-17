#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// This programm is slow because of false sharing

int main() {
    FILE * fp;

    fp = fopen ("benchmark.txt", "a+");
    char name[] = "montecarlo_no_false_sharing";

    size_t N = (int) 10e6;
    size_t inside = 0;
    double pi = 0;
    srand( 1 );

    double start_time = omp_get_wtime();

    // start parallel section
#pragma omp parallel for reduction(+ : inside) default(none) firstprivate(N)
    for (size_t i = 0; i < N / omp_get_num_threads(); i++) {
        double x, y, l;
        y = (double) rand() / RAND_MAX;
        x = (double) rand() / RAND_MAX;
        l = sqrt(x * x + y * y);
        if (l <= 1) {
            inside++;
        }
    }
    // end parallel section
    pi = (double) inside / N * 4;

    double end_time = omp_get_wtime();

    printf("pi: %2.20f\n", pi);
    printf("Time: %lf s\n", end_time - start_time);

    fprintf(fp, "%s,%d,%2.20f,%lf,%d\n", name, N, pi, end_time - start_time, omp_get_num_threads());
    fclose(fp);

    return 0;
}