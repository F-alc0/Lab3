#ifndef CLI_H
#define CLI_H

#include <stdio.h>

typedef enum {
    MODE_NONE,
    MODE_GENERATE,
    MODE_SORT,
    MODE_PRINT
} Mode;

typedef enum {
    SORT_ASC,
    SORT_DESC
} SortType;

typedef enum {
    KEY_DEVELOPER,
    KEY_DISTRICT,
    KEY_YEAR,
    KEY_APARTMENTS,
    KEY_FLOORS,
    KEY_AVG_AREA,
    KEY_HAS_ELEVATOR,
    KEY_HAS_CHUTE
} SortKey;

typedef struct {
    Mode mode;
    int N;                 // Для генерации
    char *input_file;      // Для ввода
    char *output_file;     // Для вывода
    SortType sort_type;    // Тип сортировки
    SortKey sort_key;      // По какому полю сортировать
} Config;

Config parse_args(int argc, char *argv[]);
void print_help(void);
void run_generate(int N, const char *output_file);
void run_sort(const char *input_file, const char *output_file, SortType sort_type, SortKey sort_key);
void run_print(const char *input_file, const char *output_file);
#endif