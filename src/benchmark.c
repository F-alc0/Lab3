#include "benchmark.h"
#include "building.h"
#include "vector.h"
#include "comb_sort.h"
#include "quick_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double benchmark_sort(
    SortFunction sort_func,
    Vector *vec,
    int (*cmp)(const void *, const void *)
) {
    clock_t start = clock();
    sort_func(vec, cmp);
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

void run_benchmark(void) {
    const int sizes[] = {
        100,
        200,
        500,
        1000,
        2000,
        5000,
        10000,
        20000,
        50000
    };

    const int size_count = sizeof(sizes) / sizeof(sizes[0]);

    const int REPEATS = 20;

    srand((unsigned int)time(NULL));

    printf("N,comb_sort,quick_sort\n");

    for (int i = 0; i < size_count; i++) {
        int N = sizes[i];

        Building *data = malloc(sizeof(Building) * N);
        if (!data) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            return;
        }

        for (int j = 0; j < N; j++) {
            generate_random_building(&data[j]);
        }

        Vector *v_comb = vector_create(sizeof(Building));
        Vector *v_quick = vector_create(sizeof(Building));

        if (!v_comb || !v_quick) {
            fprintf(stderr, "Ошибка создания вектора\n");
            free(data);
            return;
        }

        double comb_time = 0.0;
        double quick_time = 0.0;

        for (int r = 0; r < REPEATS; r++) {
            vector_from_array(v_comb, data, N);
            vector_from_array(v_quick, data, N);

            comb_time += benchmark_sort(
                comb_sort,
                v_comb,
                compare_by_year_asc
            );

            quick_time += benchmark_sort(
                quick_sort,
                v_quick,
                compare_by_year_asc
            );
        }

        comb_time /= REPEATS;
        quick_time /= REPEATS;

        printf("%d,%.6f,%.6f\n", N, comb_time, quick_time);

        vector_destroy(v_comb);
        vector_destroy(v_quick);
        free(data);
    }
}
