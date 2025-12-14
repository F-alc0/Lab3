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


#endif