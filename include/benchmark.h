#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "vector.h"

typedef void (*SortFunction)(
    Vector *vec,
    int (*cmp)(const void *, const void *)
);

typedef struct {
    int N;
    double comb_time;
    double quick_time;
} BenchmarkResult;

double benchmark_sort(
    SortFunction sort_func,
    Vector *vec,
    int (*cmp)(const void *, const void *)
);

void run_benchmark(void);

#endif
