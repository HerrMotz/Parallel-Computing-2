#include <stdio.h>
#include <omp.h>
static int a=0;
int main() {
    int b=0;
    omp_set_num_threads(10);
    #pragma omp parallel default(none) shared(a, b)
    {
        int c=0;
        static int d=0;
        a++;
        b++;
        c++;
        d++;
        printf("Thread, (a,b,c,d) = %d, (%d,%d,%d,%d)\n",
               omp_get_thread_num(), a, b, c, d);
    }

    printf("Thread, (a,b) = %d, (%d,%d)\n",
           omp_get_thread_num(), a, b);

    return 0;
}