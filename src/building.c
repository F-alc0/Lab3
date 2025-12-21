#include "building.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_building_help(void) {
    puts("Структура данных: Многоквартирный дом");
    puts("Поля:");
    puts("  - Застройщик (строка)");
    puts("  - Микрорайон (строка)");
    puts("  - Тип дома (PANEL/BRICK/MONOLITH)");
    puts("  - Год постройки");
    puts("  - Наличие лифта (0/1)");
    puts("  - Наличие мусоропровода (0/1)");
    puts("  - Количество квартир");
    puts("  - Количество этажей");
    puts("  - Средняя площадь квартиры");
}

void print_building_csv(const Building *bld, FILE *out) {
    const char *type_str = "UNKNOWN";

    switch (bld->type) {
        case PANEL:    type_str = "PANEL"; break;
        case BRICK:    type_str = "BRICK"; break;
        case MONOLITH: type_str = "MONOLITH"; break;
    }
    fprintf(out, "%s,%s,%s,%d,%d,%d,%d,%d,%.2f\n",
            bld->developer,
            bld->district,
            type_str,
            bld->year,
            bld->has_elevator,
            bld->has_chute,
            bld->apartments,
            bld->floors,
            bld->avg_area);
}

int read_building_csv(Building *bld, FILE *in) {
    char type_str[32];
    char line[512];

    if (!fgets(line, sizeof(line), in))
        return 0;

    line[strcspn(line, "\n")] = '\0';

    int ret = sscanf(line,
        "%99[^,],%99[^,],%31[^,],%hd,%hhu,%hhu,%hd,%hhu,%lf",
        bld->developer,
        bld->district,
        type_str,
        &bld->year,
        &bld->has_elevator,
        &bld->has_chute,
        &bld->apartments,
        &bld->floors,
        &bld->avg_area
    );

    if (ret != 9)
        return 0;

    if (strcmp(type_str, "PANEL") == 0)
        bld->type = PANEL;
    else if (strcmp(type_str, "BRICK") == 0)
        bld->type = BRICK;
    else if (strcmp(type_str, "MONOLITH") == 0)
        bld->type = MONOLITH;
    else
        return 0;

    return 1;
}
void print_building_table_header(FILE *out) {
    fprintf(out,
        "+----------------------+-----------------+-----------------+------+----------+--------------+---------------+--------------+-----------------+\n"
        "| Застройщик           | Микрорайон      | Тип дома        | Год  | Лифт     | Мусоропровод | Всего квартир | Всего этажей | Средняя площадь |\n"
        "+----------------------+-----------------+-----------------+------+----------+--------------+---------------+--------------+-----------------+\n"
    );
}

void print_building_table_row(const Building *bld, FILE *out) {
    const char *type_str = "Неизвестно";

    switch (bld->type) {
        case PANEL:    type_str = "Панельный"; break;
        case BRICK:    type_str = "Кирпичный"; break;
        case MONOLITH: type_str = "Монолитный"; break;
    }

    fprintf(out,
        "| %-20s | %-15s | %-15s | %4d | %-8s | %-12s | %-13d | %-12d | %-15.2f |\n",
        bld->developer,
        bld->district,
        type_str,
        bld->year,
        bld->has_elevator ? "ДА" : "НЕТ",
        bld->has_chute ? "ДА" : "НЕТ",
        bld->apartments,
        bld->floors,
        bld->avg_area
    );
}

void print_building_table_footer(FILE *out) {
    fprintf(out,
        "+----------------------+-----------------+-----------------+------+----------+--------------+---------------+--------------+-----------------+\n"
    );
}

void generate_random_building(Building *bld) {
    if (!bld) return;

    strcpy_s(
        bld->developer,
        sizeof(bld->developer),
        BUILDING_DEVELOPERS[rand() % BUILDING_DEVELOPERS_COUNT]
    );

    strcpy_s(
        bld->district,
        sizeof(bld->district),
        BUILDING_DISTRICTS[rand() % BUILDING_DISTRICTS_COUNT]
    );

    bld->type = (BuildingType)(rand() % 3);

    bld->year = 1950 + rand() % 50;
    bld->has_elevator = rand() % 2;
    bld->has_chute = rand() % 2;
    bld->apartments = 20 + rand() % 300;
    bld->floors = 2 + rand() % 30;
    bld->avg_area = 30.0 + (rand() % 100) / 2.0;
}

int compare_by_developer_asc(const void *a, const void *b) {
    return strcmp(
        ((const Building *)a)->developer,
        ((const Building *)b)->developer
    );
}

int compare_by_district_asc(const void *a, const void *b) {
    return strcmp(
        ((const Building *)a)->district,
        ((const Building *)b)->district
    );
}

int compare_by_year_asc(const void *a, const void *b) {
    const Building *ba = a;
    const Building *bb = b;
    return (ba->year > bb->year) - (ba->year < bb->year);
}

int compare_by_apartments_asc(const void *a, const void *b) {
    const Building *ba = a;
    const Building *bb = b;
    return (ba->apartments > bb->apartments) - (ba->apartments < bb->apartments);
}

int compare_by_floors_asc(const void *a, const void *b) {
    const Building *ba = a;
    const Building *bb = b;
    return (ba->floors > bb->floors) - (ba->floors < bb->floors);
}

int compare_by_avg_area_asc(const void *a, const void *b) {
    const Building *ba = a;
    const Building *bb = b;
    return (ba->avg_area > bb->avg_area) - (ba->avg_area < bb->avg_area);
}

int compare_by_has_elevator_asc(const void *a, const void *b) {
    const Building *ba = a;
    const Building *bb = b;
    return (ba->has_elevator > bb->has_elevator) -
           (ba->has_elevator < bb->has_elevator);
}

int compare_by_has_chute_asc(const void *a, const void *b) {
    const Building *ba = a;
    const Building *bb = b;
    return (ba->has_chute > bb->has_chute) -
           (ba->has_chute < bb->has_chute);
}

int compare_by_developer_desc(const void *a, const void *b) {
    return -compare_by_developer_asc(a, b);
}

int compare_by_district_desc(const void *a, const void *b) {
    return -compare_by_district_asc(a, b);
}

int compare_by_year_desc(const void *a, const void *b) {
    return -compare_by_year_asc(a, b);
}

int compare_by_apartments_desc(const void *a, const void *b) {
    return -compare_by_apartments_asc(a, b);
}

int compare_by_floors_desc(const void *a, const void *b) {
    return -compare_by_floors_asc(a, b);
}

int compare_by_avg_area_desc(const void *a, const void *b) {
    return -compare_by_avg_area_asc(a, b);
}

int compare_by_has_elevator_desc(const void *a, const void *b) {
    return -compare_by_has_elevator_asc(a, b);
}

int compare_by_has_chute_desc(const void *a, const void *b) {
    return -compare_by_has_chute_asc(a, b);
}