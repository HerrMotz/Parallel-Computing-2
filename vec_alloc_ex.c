#include <stdio.h>
#include <stdlib.h>

int main() {
    int* v_malloc = malloc(5 * sizeof(int));
    int* v_calloc = calloc(5, sizeof(int));

    printf("v_calloc=[");
    for (size_t i = 0; i < 5; ++i) {
        printf("%d ", v_calloc[i]);
    }
    printf("]\nv_malloc=[");

    for (size_t i = 0; i < 5; ++i) {
        printf("%d ", v_malloc[i]);
    }
    printf("]\n");
    free(v_malloc);
    free(v_calloc);

    return 0;
}