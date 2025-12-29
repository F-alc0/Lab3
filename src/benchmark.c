#include "benchmark.h"
#include "building.h"
#include "vector.h"
#include "comb_sort.h"
#include "quick_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
 Методика:
 - один эксперимент = одна сортировка
 - σ считается по экспериментам
 - увеличиваем число повторений, пока
   3σ / <t> <= REL_ERROR
*/

#define MIN_REPEATS 30
#define MAX_REPEATS 200
#define REL_ERROR 0.05

static double measure_once(
    SortFunction sort_func,
    Building *data,
    int n,
    int (*cmp)(const void *, const void *)
) {
    Vector *v = vector_create(sizeof(Building));
    vector_from_array(v, data, n);

    clock_t start = clock();
    sort_func(v, cmp);
    clock_t end = clock();

    vector_destroy(v);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

static void benchmark_one(
    SortFunction sort_func,
    Building *data,
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
            times[i] = measure_once(sort_func, data, n, cmp);
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
        1000, 2000, 5000, 10000, 20000, 50000, 100000
    };

    const int count = sizeof(sizes) / sizeof(sizes[0]);
    srand((unsigned int)time(NULL));

    printf("N,comb_t,comb_dt,quick_t,quick_dt,repeats\n");

    for (int i = 0; i < count; i++) {
        int N = sizes[i];

        Building *data = malloc(sizeof(Building) * N);
        if (!data) return;

        for (int j = 0; j < N; j++)
            generate_random_building(&data[j]);

        double comb_t, comb_sigma;
        double quick_t, quick_sigma;
        int repeats;

        benchmark_one(
            comb_sort, data, N,
            compare_by_year_asc,
            &comb_t, &comb_sigma, &repeats
        );

        benchmark_one(
            quick_sort, data, N,
            compare_by_year_asc,
            &quick_t, &quick_sigma, &repeats
        );

        printf(
            "%d,%.8f,%.8f,%.8f,%.8f,%d\n",
            N,
            comb_t, 3 * comb_sigma,
            quick_t, 3 * quick_sigma,
            repeats
        );

        free(data);
    }
}
