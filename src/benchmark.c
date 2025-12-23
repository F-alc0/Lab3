#include "benchmark.h"
#include "building.h"
#include "vector.h"
#include "comb_sort.h"
#include "quick_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PROBE_RUNS 5
#define MIN_REPEATS 1
#define MAX_REPEATS 1000
#define REPEAT_CONST 1e-6


static double measure_once(
    SortFunction sort_func,
    Vector *vec,
    int (*cmp)(const void *, const void *)
) {
    clock_t start = clock();
    sort_func(vec, cmp);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static double probe_time(
    SortFunction sort_func,
    Building *data,
    int n,
    int (*cmp)(const void *, const void *)
) {
    double sum = 0.0;

    for (int i = 0; i < PROBE_RUNS; i++) {
        Vector *v = vector_create(sizeof(Building));
        vector_from_array(v, data, n);

        sum += measure_once(sort_func, v, cmp);
        vector_destroy(v);
    }

    return sum / PROBE_RUNS;
}

static int compute_repeats(double t) {
    if (t <= 0.0) return MAX_REPEATS;

    int k = (int)ceil(REPEAT_CONST / (t * t));

    if (k < MIN_REPEATS) k = MIN_REPEATS;
    if (k > MAX_REPEATS) k = MAX_REPEATS;

    return k;
}


static double benchmark_average(
    SortFunction sort_func,
    Building *data,
    int n,
    int repeats,
    int (*cmp)(const void *, const void *)
) {
    double sum = 0.0;

    for (int i = 0; i < repeats; i++) {
        Vector *v = vector_create(sizeof(Building));
        vector_from_array(v, data, n);

        sum += measure_once(sort_func, v, cmp);
        vector_destroy(v);
    }

    return sum / repeats;
}


void run_benchmark(void) {
    const int sizes[] = {
        5, 10, 20, 50, 100, 200, 500, 1000, 2000,
        5000, 10000, 20000, 50000, 100000, 20000, 50000, 1000000
    };

    const int count = sizeof(sizes) / sizeof(sizes[0]);
    srand((unsigned int)time(NULL));

    printf("N,comb_sort,quick_sort,repeats\n");

    for (int i = 0; i < count; i++) {
        int N = sizes[i];

        Building *data = malloc(sizeof(Building) * N);
        if (!data) return;

        for (int j = 0; j < N; j++)
            generate_random_building(&data[j]);
        double t_probe = probe_time(
            comb_sort, data, N, compare_by_year_asc
        );
        int repeats = compute_repeats(t_probe);
        double comb_time = benchmark_average(
            comb_sort, data, N, repeats, compare_by_year_asc
        );

        double quick_time = benchmark_average(
            quick_sort, data, N, repeats, compare_by_year_asc
        );

        printf("%d,%.6f,%.6f,%d\n",
               N, comb_time, quick_time, repeats);

        free(data);
    }
}
