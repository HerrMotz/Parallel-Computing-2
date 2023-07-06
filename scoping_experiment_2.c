#include <stdio.h>
#include <omp.h>

int main() {
    int i = -1;

    #pragma omp parallel firstprivate(i)
    {
        printf("thread %d: id = %d\n", omp_get_thread_num(), i);
        i = omp_get_thread_num();
    }
    printf("i = %d\n", i);
    return 0;
}