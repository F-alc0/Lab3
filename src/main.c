#include "cli.h"
#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }
    Config cfg = parse_args(argc, argv);
    switch (cfg.mode) {
        case MODE_GENERATE:
            run_generate(cfg.N, cfg.output_file);
            break;
        case MODE_SORT:
            run_sort(cfg.input_file, cfg.output_file, cfg.sort_type, cfg.sort_key);
            break;
        case MODE_PRINT:
            run_print(cfg.input_file, cfg.output_file);
            break;
        case MODE_BENCHMARK:
            run_benchmark();
            break;
        default:
            fprintf(stderr, "Ошибка: не указан режим работы\n");
            print_help();
            return 1;
    }
    return 0;
}