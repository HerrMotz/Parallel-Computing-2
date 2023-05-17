#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    FILE * fp;

    fp = fopen ("benchmark.txt", "w+");
    int N = (int) 10e6;
    char name[] = "montecarlo_false_sharing";

    double pi = 0;
    size_t inside = 0;
    srand( 1 );

    double start_time = omp_get_wtime();

#pragma omp parallel default(none) shared(pi, inside) firstprivate(N)
    {
        double x, y, l;
        size_t* local_inside = malloc(128);
        *local_inside = 0;

        for(int i = 0; i < N / omp_get_num_threads(); ++i) {
            x = (double) rand() / RAND_MAX;
            y = (double) rand() / RAND_MAX;
            l = sqrt(x * x + y * y);
            if( l <= 1 ) {
                (*local_inside)++;
            }
        }

        printf("%d\n", *local_inside);

#pragma omp atomic
        inside = inside + (*local_inside);

        free(local_inside);
    };
    printf("inside %zu, pi %lf\n", inside, pi);
    pi = (double) inside / N * 4;

    double end_time = omp_get_wtime();

    printf("pi: %2.20f\n", pi);
    printf("Time: %lf s\n", end_time - start_time);

    fprintf(fp, "%s,%d,%2.20f,%lf,%d\n", name, N, pi, end_time - start_time, omp_get_num_threads());

    fclose(fp);

    return 0;
}