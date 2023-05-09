#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    int N = (int) 10e6;
    double pi, inside;
    srand( 1 );

    omp_set_num_threads(4);
    printf("Num threads: %d\n", omp_get_num_threads());

    double start_time = omp_get_wtime();

#pragma omp parallel default(none) shared(pi, inside) firstprivate(N)
{
    double x, y, l;
    int local_inside = 0;
    for(int i = 0; i < N; i+=omp_get_num_threads()) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        l = sqrt(x * x + y * y);
        if( l <= 1 ) {
            local_inside++;
        }
    }
#pragma omp atomic
    inside += local_inside;
};
    pi = (double) inside / N * 4;

    double end_time = omp_get_wtime();

    printf("pi: %2.20f\n", pi);
    printf("Time: %lf s\n", end_time - start_time);

    return 0;
}