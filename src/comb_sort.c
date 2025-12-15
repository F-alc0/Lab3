#include "comb_sort.h"
#include <math.h>

void comb_sort(Vector *vec, Comparator cmp) {
    if (!vec || vec->size <= 1 || !cmp) return;
    size_t gap = vec->size;
    const double shrink = 1.3;
    int swapped = 1;
    while (gap > 1 || swapped) {
        gap = (size_t)(gap / shrink);
        if (gap < 1) gap = 1;
        swapped = 0;
        for (size_t i = 0; i + gap < vec->size; i++) {
            void *a = vector_at(vec, i);
            void *b = vector_at(vec, i + gap);
            if (cmp(a, b) > 0) {
                vector_swap(vec, i, i + gap);
                swapped = 1;
            }
        }
    }
}