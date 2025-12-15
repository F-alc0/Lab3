#include "cli.h"
#include "building.h"
#include "vector.h"
#include "comb_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Config parse_args(int argc, char *argv[]) {
    Config cfg = {MODE_NONE, 0, NULL, NULL, SORT_ASC, KEY_DEVELOPER};
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_help();
            exit(0);
        }
        else if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            if (i + 1 < argc) {
                cfg.mode = MODE_GENERATE;
                cfg.N = atoi(argv[i + 1]);
                i++;
            }
        }
        else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            cfg.mode = MODE_SORT;
        }
        else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-p") == 0) {
            cfg.mode = MODE_PRINT;
        }
        else if (strcmp(argv[i], "--in") == 0 || strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                cfg.input_file = argv[i + 1];
                i++;
            }
        }
        else if (strcmp(argv[i], "--out") == 0 || strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                cfg.output_file = argv[i + 1];
                i++;
            }
        }
        else if (strcmp(argv[i], "--type") == 0 || strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "desc") == 0 || strcmp(argv[i + 1], "D") == 0) {
                    cfg.sort_type = SORT_DESC;
                } else if (strcmp(argv[i + 1], "asc") == 0 || strcmp(argv[i + 1], "A") == 0) {
                    cfg.sort_type = SORT_ASC;
                }
                i++;
            }
        }
        else if (strcmp(argv[i], "--key") == 0 || strcmp(argv[i], "-k") == 0) {
            if (i + 1 < argc) {
                const char *key = argv[i + 1];
                if (strcmp(key, "developer") == 0) cfg.sort_key = KEY_DEVELOPER;
                else if (strcmp(key, "district") == 0) cfg.sort_key = KEY_DISTRICT;
                else if (strcmp(key, "year") == 0) cfg.sort_key = KEY_YEAR;
                else if (strcmp(key, "apartments") == 0) cfg.sort_key = KEY_APARTMENTS;
                else if (strcmp(key, "floors") == 0) cfg.sort_key = KEY_FLOORS;
                else if (strcmp(key, "avg_area") == 0) cfg.sort_key = KEY_AVG_AREA;
                else if (strcmp(key, "elevator") == 0) cfg.sort_key = KEY_HAS_ELEVATOR;
                else if (strcmp(key, "chute") == 0) cfg.sort_key = KEY_HAS_CHUTE;
                i++;
            }
        }
    }
    return cfg;
}

void print_help() {
    puts("Лабораторная работа 3 (вариант 5)");
    puts("Структура данных: Многоквартирный дом");
    puts("Алгоритм сортировки: Расческой");
    puts("Контейнер: Вектор");
    puts("");
    puts("Использование:");
    puts("  lab3.exe --generate N [-o файл]    Генерация N записей о домах");
    puts("  lab3.exe --sort [-i файл] [-o файл] [-t A|D] [-k поле]  Сортировка данных");
    puts("  lab3.exe --print [-i файл] [-o файл]  Вывод данных в виде таблицы");
    puts("");
    puts("Флаги:");
    puts("  -g, --generate N   Количество записей для генерации");
    puts("  -s, --sort         Режим сортировки");
    puts("  -p, --print        Режим вывода таблицы");
    puts("  -i, --in=файл      Входной файл (по умолчанию: stdin)");
    puts("  -o, --out=файл     Выходной файл (по умолчанию: stdout)");
    puts("  -t, --type=тип     Тип сортировки (A - возрастание, D - убывание)");
    puts("  -k, --key=поле     По какому полю сортировать (developer, district, year, apartments, floors, avg_area, elevator, chute)");
    puts("  -h, --help         Показать эту справку");
    puts("");
    print_building_help();
}

void run_generate(int N, const char *output_file) {
    if (N <= 0) {
        fprintf(stderr, "Ошибка: количество записей должно быть больше нуля\n");
        return;
    }
    FILE *out = stdout;
    if (output_file) {
        out = fopen(output_file, "w");
        if (!out) {
            perror("Ошибка открытия файла для записи");
            return;
        }
    }
    srand(time(NULL));
    Building bld;
    for (int i = 0; i < N; i++) {
        generate_random_building(&bld);
        print_building_csv(&bld, out);
    }
    if (output_file) {
        fclose(out);
        printf("Сгенерировано %d записей. Данные сохранены в файл %s\n", N, output_file);
    } else {
        printf("Сгенерировано %d записей\n", N);
    }
}