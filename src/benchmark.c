#include "benchmark.h"
#include "building.h"
#include "vector.h"
#include "comb_sort.h"
#include "quick_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN_REPEATS 20
#define MAX_REPEATS 200
#define INNER_REPEATS 50
#define REL_ERROR 0.05

static double measure_once(
    SortFunction sort_func,
    int n,
    int (*cmp)(const void *, const void *)
) {
    clock_t start = clock();

    for (int k = 0; k < INNER_REPEATS; k++) {
        Building *data = malloc(sizeof(Building) * n);
        for (int i = 0; i < n; i++)
            generate_random_building(&data[i]);

        Vector *v = vector_create(sizeof(Building));
        vector_from_array(v, data, n);

        sort_func(v, cmp);

        vector_destroy(v);
        free(data);
    }

    clock_t end = clock();
    return ((double)(end - start) / CLOCKS_PER_SEC) / INNER_REPEATS;
}

static void benchmark_one(
    SortFunction sort_func,
    int n,
    int (*cmp)(const void *, const void *),
    double *mean,
    double *sigma,
    int *repeats_out
) {
    int repeats = MIN_REPEATS;
    double *times = NULL;

    while (1) {
        times = realloc(times, repeats * sizeof(double));
        double sum = 0.0;

        for (int i = 0; i < repeats; i++) {
            times[i] = measure_once(sort_func, n, cmp);
            sum += times[i];
        }

        *mean = sum / repeats;

        double var = 0.0;
        for (int i = 0; i < repeats; i++) {
            double d = times[i] - *mean;
            var += d * d;
        }
        *sigma = sqrt(var / repeats);

        if (*mean > 0 &&
            3 * (*sigma) / (*mean) <= REL_ERROR)
            break;

        if (repeats >= MAX_REPEATS)
            break;

        repeats *= 2;
        if (repeats > MAX_REPEATS)
            repeats = MAX_REPEATS;
    }

    *repeats_out = repeats;
    free(times);
}

void run_benchmark(void) {
    const int sizes[] = {
        10, 20, 50, 100, 150, 200, 300, 500,
        1000, 2000
    };

    const int count = sizeof(sizes) / sizeof(sizes[0]);
    srand((unsigned int)time(NULL));

    printf("N,comb_t,comb_dt,quick_t,quick_dt,comb_rep,quick_rep\n");

    for (int i = 0; i < count; i++) {
        int N = sizes[i];

        double comb_t, comb_sigma;
        double quick_t, quick_sigma;
        int comb_rep, quick_rep;

        benchmark_one(
            comb_sort,
            N,
            compare_by_year_asc,
            &comb_t,
            &comb_sigma,
            &comb_rep
        );

        benchmark_one(
            quick_sort,
            N,
            compare_by_year_asc,
            &quick_t,
            &quick_sigma,
            &quick_rep
        );

        printf(
            "%d,%.8f,%.8f,%.8f,%.8f,%d,%d\n",
            N,
            comb_t, 3 * comb_sigma,
            quick_t, 3 * quick_sigma,
            comb_rep, quick_rep
        );
    }
}
