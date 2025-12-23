#include "quick_sort.h"

static void quick_sort_impl(Vector *vec, Comparator cmp, int left, int right) {
    if (left >= right) return;

    int i = left;
    int j = right;
    void *pivot = vector_at(vec, (left + right) / 2);

    while (i <= j) {
        while (cmp(vector_at(vec, i), pivot) < 0) i++;
        while (cmp(vector_at(vec, j), pivot) > 0) j--;

        if (i <= j) {
            vector_swap(vec, i, j);
            i++;
            j--;
        }
    }

    if (left < j) quick_sort_impl(vec, cmp, left, j);
    if (i < right) quick_sort_impl(vec, cmp, i, right);
}

void quick_sort(Vector *vec, Comparator cmp) {
    if (!vec || vec->size < 2 || !cmp) return;
    quick_sort_impl(vec, cmp, 0, (int)vec->size - 1);
}