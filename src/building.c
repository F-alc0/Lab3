#include "building.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char *BUILDING_DEVELOPERS[] = {
    "Rockstar Estates",
    "TerraGroup Villas",
    "Lucas Constructions",
    "CD Project Heights",
    "City 17",
    "Larian Builders",
    "Stoic Housing",
    "Bethesda Just Works",
    "EAchitect"
};

const unsigned int BUILDING_DEVELOPERS_COUNT =
    sizeof(BUILDING_DEVELOPERS) / sizeof(BUILDING_DEVELOPERS[0]);

const char *BUILDING_DISTRICTS[] = {
    "Верхний Ярнам",
    "Глубины Асина",
    "Кейнхёрст",
    "Олачиль",
    "Анор Лондо",
    "Иритилл",
    "Трущобы",
    "Болетария",
    "Озёрная Лиурния"
};

const unsigned int BUILDING_DISTRICTS_COUNT =
    sizeof(BUILDING_DISTRICTS) / sizeof(BUILDING_DISTRICTS[0]);

void generate_random_building(Building *bld) {
    if (!bld) return;

    strncpy(
        bld->developer,
        BUILDING_DEVELOPERS[rand() % BUILDING_DEVELOPERS_COUNT],
        sizeof(bld->developer) - 1
    );
    bld->developer[sizeof(bld->developer) - 1] = '\0';

    strncpy(
        bld->district,
        BUILDING_DISTRICTS[rand() % BUILDING_DISTRICTS_COUNT],
        sizeof(bld->district) - 1
    );
    bld->district[sizeof(bld->district) - 1] = '\0';

    bld->type = (BuildingType)(rand() % 3);
    bld->year = 1970 + rand() % 55;
    bld->has_elevator = rand() % 2;
    bld->has_chute = rand() % 2;
    bld->apartments = 20 + rand() % 300;
    bld->floors = 2 + rand() % 25;
    bld->avg_area = 30.0 + (rand() % 100) / 2.0;
}

void print_building_csv(const Building *bld, FILE *out) {
    if (!bld || !out) return;

    fprintf(out,
        "%s;%s;%d;%d;%d;%d;%d;%d;%.2f\n",
        bld->developer,
        bld->district,
        bld->type,
        bld->year,
        bld->has_elevator,
        bld->has_chute,
        bld->apartments,
        bld->floors,
        bld->avg_area
    );
}

int read_building_csv(Building *bld, FILE *in) {
    if (!bld || !in) return 0;

    int type_tmp;

    int read = fscanf(
        in,
        " %99[^;];%99[^;];%d;%hd;%hhu;%hhu;%hd;%hhu;%lf",
        bld->developer,
        bld->district,
        &type_tmp,
        &bld->year,
        &bld->has_elevator,
        &bld->has_chute,
        &bld->apartments,
        &bld->floors,
        &bld->avg_area
    );

    if (read != 9)
        return 0;

    bld->type = (BuildingType)type_tmp;
    return 1;
}

void print_building_help(void) {
    printf("Поля записи Building:\n");
    printf("  developer      — застройщик\n");
    printf("  district       — район\n");
    printf("  type           — тип здания (0=Панель, 1=Кирпич, 2=Монолит)\n");
    printf("  year           — год постройки\n");
    printf("  has_elevator   — наличие лифта (0/1)\n");
    printf("  has_chute      — наличие мусоропровода (0/1)\n");
    printf("  apartments     — количество квартир\n");
    printf("  floors         — количество этажей\n");
    printf("  avg_area       — средняя площадь квартиры\n");
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
    return ((const Building *)a)->year -
           ((const Building *)b)->year;
}

int compare_by_apartments_asc(const void *a, const void *b) {
    return ((const Building *)a)->apartments -
           ((const Building *)b)->apartments;
}

int compare_by_floors_asc(const void *a, const void *b) {
    return ((const Building *)a)->floors -
           ((const Building *)b)->floors;
}

int compare_by_avg_area_asc(const void *a, const void *b) {
    double diff =
        ((const Building *)a)->avg_area -
        ((const Building *)b)->avg_area;
    return (diff > 0) - (diff < 0);
}

int compare_by_has_elevator_asc(const void *a, const void *b) {
    return ((const Building *)a)->has_elevator -
           ((const Building *)b)->has_elevator;
}

int compare_by_has_chute_asc(const void *a, const void *b) {
    return ((const Building *)a)->has_chute -
           ((const Building *)b)->has_chute;
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
