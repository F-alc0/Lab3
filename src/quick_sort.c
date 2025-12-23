#include "quick_sort.h"
#include <string.h>

#define INSERTION_SORT_THRESHOLD 16

static void insertion_sort(Vector *vec, Comparator cmp, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int j = i;
        char temp[256];
        memcpy(temp, vector_at(vec, i), vec->element_size);

        while (j > left && cmp(vector_at(vec, j - 1), temp) > 0) {
            memcpy(vector_at(vec, j), vector_at(vec, j - 1), vec->element_size);
            j--;
        }
        memcpy(vector_at(vec, j), temp, vec->element_size);
    }
}

static int median_of_three(Vector *vec, Comparator cmp, int a, int b, int c) {
    void *A = vector_at(vec, a);
    void *B = vector_at(vec, b);
    void *C = vector_at(vec, c);

    if (cmp(A, B) < 0) {
        if (cmp(B, C) < 0) return b;
        return cmp(A, C) < 0 ? c : a;
    } else {
        if (cmp(A, C) < 0) return a;
        return cmp(B, C) < 0 ? c : b;
    }
}

static void quick_sort_impl(Vector *vec, Comparator cmp, int left, int right) {
    while (right - left > INSERTION_SORT_THRESHOLD) {

        int mid = left + (right - left) / 2;
        int pivot_index = median_of_three(vec, cmp, left, mid, right);
        vector_swap(vec, pivot_index, right);

        void *pivot = vector_at(vec, right);
        int i = left;

        for (int j = left; j < right; j++) {
            if (cmp(vector_at(vec, j), pivot) < 0) {
                vector_swap(vec, i++, j);
            }
        }
        vector_swap(vec, i, right);

        if (i - left < right - i) {
            quick_sort_impl(vec, cmp, left, i - 1);
            left = i + 1;
        } else {
            quick_sort_impl(vec, cmp, i + 1, right);
            right = i - 1;
        }
    }

    insertion_sort(vec, cmp, left, right);
}

void quick_sort(Vector *vec, Comparator cmp) {
    if (!vec || vec->size < 2 || !cmp) return;
    quick_sort_impl(vec, cmp, 0, (int)vec->size - 1);
}
