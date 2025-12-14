#ifndef BUILDING_H
#define BUILDING_H

#include <stdio.h>

typedef enum {
    PANEL,
    BRICK,
    MONOLITH
} BuildingType;

typedef struct {
    char developer[100];
    char district[100];
    BuildingType type;
    int year;
    int has_elevator;
    int has_chute;
    int apartments;
    int floors;
    double avg_area;
} Building;

void print_building_help();
void print_building_csv(const Building *bld, FILE *out);
int read_building_csv(Building *bld, FILE *in);
void print_building_table_header(FILE *out);
void print_building_table_row(const Building *bld, FILE *out);
void print_building_table_footer(FILE *out);
void generate_random_building(Building *bld);

#endif