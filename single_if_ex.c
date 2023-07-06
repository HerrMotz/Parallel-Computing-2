#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//static int a=0;

//void test(int val) {
//#pragma omp parallel if (val)
//    if (omp_in_parallel()) {
//        #pragma omp single
//        printf("val = %d, parallelized with %d threads\n", val, omp_get_num_threads());
//    } else {
//        printf("val = %d, serialized\n", val);
//    }
//}
//
//int main() {
//    omp_set_num_threads(2);
//
//    test(0);
//    test(2);
//
//    return 0;
//}

int main() {

    int a[] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    int s = 0;
    printf("outer s is %d\n", s);

#pragma omp parallel for shared(s)
    for (int i = 0; i < 10; i++){
        printf("loop: s is %d\n", s);
        s += a[i];
    }

    printf("s is %d", s);
    return 0;
}