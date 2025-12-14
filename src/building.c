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