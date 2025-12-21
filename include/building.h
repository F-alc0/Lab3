#ifndef BUILDING_H
#define BUILDING_H

#include <stdio.h>

static const char *BUILDING_DEVELOPERS[] = {
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

static const size_t BUILDING_DEVELOPERS_COUNT =
    sizeof(BUILDING_DEVELOPERS) / sizeof(BUILDING_DEVELOPERS[0]);

static const char *BUILDING_DISTRICTS[] = {
    "Верхний Ярнам",
    "Район №9",
    "Кейнхёрст",
    "Олачиль",
    "Анор Лондо",
    "Иритилл",
    "Трущобы",
    "Сайсил",
    "Аркс"
};

static const size_t BUILDING_DISTRICTS_COUNT =
    sizeof(BUILDING_DISTRICTS) / sizeof(BUILDING_DISTRICTS[0]);

typedef enum {
    PANEL,
    BRICK,
    MONOLITH
} BuildingType;

typedef struct {
    char developer[100];
    char district[100];
    BuildingType type;
    short year;
    unsigned char has_elevator;
    unsigned char has_chute;
    short apartments;
    unsigned char floors;
    double avg_area;
} Building;

void print_building_help(void);
void print_building_csv(const Building *bld, FILE *out);
int read_building_csv(Building *bld, FILE *in);
void print_building_table_header(FILE *out);
void print_building_table_row(const Building *bld, FILE *out);
void print_building_table_footer(FILE *out);
void generate_random_building(Building *bld);

int compare_by_developer_asc(const void *a, const void *b);
int compare_by_district_asc(const void *a, const void *b);
int compare_by_year_asc(const void *a, const void *b);
int compare_by_apartments_asc(const void *a, const void *b);
int compare_by_floors_asc(const void *a, const void *b);
int compare_by_avg_area_asc(const void *a, const void *b);
int compare_by_has_elevator_asc(const void *a, const void *b);
int compare_by_has_chute_asc(const void *a, const void *b);

int compare_by_developer_desc(const void *a, const void *b);
int compare_by_district_desc(const void *a, const void *b);
int compare_by_year_desc(const void *a, const void *b);
int compare_by_apartments_desc(const void *a, const void *b);
int compare_by_floors_desc(const void *a, const void *b);
int compare_by_avg_area_desc(const void *a, const void *b);
int compare_by_has_elevator_desc(const void *a, const void *b);
int compare_by_has_chute_desc(const void *a, const void *b);

#endif
