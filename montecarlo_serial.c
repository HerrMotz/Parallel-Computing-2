#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    FILE * fp;

    fp = fopen ("benchmark.txt", "w+");
    int N = (int) 10e6;
    char name[] = "montecarlo_serial";

    int I = 0;
    double x,y,l, pi;
    srand( 1 );

    double start_time = omp_get_wtime();

    for(int i = 0; i < N; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        l = sqrt(x * x + y * y);
        if( l <= 1 ) {
            I++;
        }
    }

    pi = (double) I / N * 4;

    double end_time = omp_get_wtime();

    printf("pi: %2.20f\n", pi);
    printf("Time: %lf s\n", end_time - start_time);

    fprintf(fp, "%s,%d,%2.20f,%lf,%d\n", name, N, pi, end_time - start_time, omp_get_num_threads());

    return 0;
}