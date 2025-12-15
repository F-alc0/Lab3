#include "building.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_building_help() {
    puts("Структура данных: Многоквартирный дом");
    puts("Поля:");
    puts("  - Застройщик (строка)");
    puts("  - Микрорайон (строка)");
    puts("  - Тип дома (PANEL/BRICK/MONOLITH)");
    puts("  - Год постройки (четырехзначное число)");
    puts("  - Наличие лифта (0/1)");
    puts("  - Наличие мусоропровода (0/1)");
    puts("  - Количество квартир (целое число)");
    puts("  - Количество этажей (целое число)");
    puts("  - Средняя площадь квартиры (вещественное число)");
}

void print_building_csv(const Building *bld, FILE *out) {
    const char *type_str;
    switch (bld->type) {
        case PANEL: type_str = "PANEL"; break;
        case BRICK: type_str = "BRICK"; break;
        case MONOLITH: type_str = "MONOLITH"; break;
        default: type_str = "UNKNOWN";
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
    char type_str[20];
    char line[512];
    if (!fgets(line, sizeof(line), in)) {
        return 0;
    }
    line[strcspn(line, "\n")] = '\0';
    int ret = sscanf(line, "%99[^,],%99[^,],%19[^,],%d,%d,%d,%d,%d,%lf",
                     bld->developer,
                     bld->district,
                     type_str,
                     &bld->year,
                     &bld->has_elevator,
                     &bld->has_chute,
                     &bld->apartments,
                     &bld->floors,
                     &bld->avg_area);
    if (ret != 9) {
        return 0;
    }
    if (strcmp(type_str, "PANEL") == 0) {
        bld->type = PANEL;
    } else if (strcmp(type_str, "BRICK") == 0) {
        bld->type = BRICK;
    } else if (strcmp(type_str, "MONOLITH") == 0) {
        bld->type = MONOLITH;
    } else {
        return 0;
    }
    return 1;
}
void print_building_table_header(FILE *out) {
    fprintf(out, "+----------------------+-----------------+-----------------+------+----------+-------------+-------------+--------+----------------+\n");
    fprintf(out, "| Застройщик           | Микрорайон      | Тип дома        | Год  | Лифт     | Мусоропровод| Квартир     | Этажей | Средняя площадь|\n");
    fprintf(out, "+----------------------+-----------------+-----------------+------+----------+-------------+-------------+--------+----------------+\n");
}

void print_building_table_row(const Building *bld, FILE *out) {
    const char *type_str;
    switch (bld->type) {
        case PANEL: type_str = "Панельный"; break;
        case BRICK: type_str = "Кирпичный"; break;
        case MONOLITH: type_str = "Монолитный"; break;
        default: type_str = "Неизвестно";
    }
    const char *elevator = bld->has_elevator ? "ДА" : "НЕТ";
    const char *chute = bld->has_chute ? "ДА" : "НЕТ";
    fprintf(out, "| %-20s | %-15s | %-15s | %4d | %-8s | %-11s | %11d | %6d | %14.2f |\n",
            bld->developer,
            bld->district,
            type_str,
            bld->year,
            elevator,
            chute,
            bld->apartments,
            bld->floors,
            bld->avg_area);
}

void print_building_table_footer(FILE *out) {
    fprintf(out, "+----------------------+-----------------+-----------------+------+----------+-------------+-------------+--------+----------------+\n");
}

void generate_random_building(Building *bld) {
    const char *developers[] = {
        "Rockstar Estates", "TerraGroup Villas", "Lucas Constructions",
        "CD Project Heights", "City 17", "Larian Builders",
        "Stoic Housing", "Bethesda (Just) Works", "EAchitect"
    };
    const char *districts[] = {
        "Верхний Ярнам", "Район №9", "Кейнхёрст",
        "Олачиль", "Анор Лондо", "Иритилл",
        "Трущобы", "Сайсил", "Аркс"
    };
    BuildingType types[] = {PANEL, BRICK, MONOLITH};
    strcpy(bld->developer, developers[rand() % 9]);
    strcpy(bld->district, districts[rand() % 9]);
    bld->type = types[rand() % 3];
    bld->year = 1970 + rand() % 50;
    bld->has_elevator = rand() % 2;
    bld->has_chute = rand() % 2;
    bld->apartments = 20 + rand() % 300;
    bld->floors = 2 + rand() % 30;
    bld->avg_area = 30.0 + (rand() % 100) / 2.0;
}

int compare_by_developer_asc(const void *a, const void *b) {
    const Building *b1 = (const Building *)a;
    const Building *b2 = (const Building *)b;
    return strcmp(b1->developer, b2->developer);
}

int compare_by_floors_asc(const void *a, const void *b) {
    const Building *b1 = (const Building *)a;
    const Building *b2 = (const Building *)b;
    return (b1->floors > b2->floors) - (b1->floors < b2->floors);
}

int compare_by_avg_area_asc(const void *a, const void *b) {
    const Building *b1 = (const Building *)a;
    const Building *b2 = (const Building *)b;
    return (b1->avg_area > b2->avg_area) - (b1->avg_area < b2->avg_area);
}

int compare_by_has_elevator_asc(const void *a, const void *b) {
    const Building *b1 = (const Building *)a;
    const Building *b2 = (const Building *)b;
    return (b1->has_elevator > b2->has_elevator) - (b1->has_elevator < b2->has_elevator);
}

int compare_by_has_chute_asc(const void *a, const void *b) {
    const Building *b1 = (const Building *)a;
    const Building *b2 = (const Building *)b;
    return (b1->has_chute > b2->has_chute) - (b1->has_chute < b2->has_chute);
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