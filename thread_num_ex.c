#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



void report(double n) {
    printf("\ntime %f seconds\n", n);
}

void loop() {
    for (int i = 0; i < 100; i++)
        printf(" ");
}

int main() {
    double start = omp_get_wtime();
    loop();
    double end = omp_get_wtime();
    report(end-start);

    omp_set_num_threads(3);
#pragma omp parallel default(none) private(start, end)
    {
        start = omp_get_wtime();
        loop();
        end = omp_get_wtime();
        report(end-start);
    }
    end = omp_get_wtime();
    report(end-start);
    return 0;
}