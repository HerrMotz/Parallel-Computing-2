#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    FILE * fp;

    fp = fopen ("benchmark_motecarlo_par_good.txt", "w+");

    int N = (int) 10e6;
    double pi, inside;
    srand( 1 );

    double start_time = omp_get_wtime();

#pragma omp parallel default(none) shared(pi, inside) firstprivate(N) num_threads(8)
    {
        printf("thread: %d, num: %d\n", omp_get_thread_num(), omp_get_num_threads());
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

    fprintf(fp, "pi: %2.20f\n", pi);
    fprintf(fp, "Time: %lf s\n", end_time - start_time);

    fclose(fp);

    return 0;
}