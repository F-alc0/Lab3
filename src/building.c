#include "building.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char *BUILDING_DEVELOPERS[] = {
    "Rockstar Estates", "TerraGroup Villas", "Lucas Constructions",
    "CD Project Heights", "City 17", "Larian Builders",
    "Stoic Housing", "Bethesda Just Works", "EAchitect"
};

const unsigned int BUILDING_DEVELOPERS_COUNT =
    sizeof(BUILDING_DEVELOPERS) / sizeof(BUILDING_DEVELOPERS[0]);

const char *BUILDING_DISTRICTS[] = {
    "Верхний Ярнам", "Район №9", "Кейнхёрст",
    "Олачиль", "Анор Лондо", "Иритилл",
    "Трущобы", "Сайсил", "Аркс"
};

const unsigned int BUILDING_DISTRICTS_COUNT =
    sizeof(BUILDING_DISTRICTS) / sizeof(BUILDING_DISTRICTS[0]);

void generate_random_building(Building *bld) {
    strcpy(bld->developer,
           BUILDING_DEVELOPERS[rand() % BUILDING_DEVELOPERS_COUNT]);
    strcpy(bld->district,
           BUILDING_DISTRICTS[rand() % BUILDING_DISTRICTS_COUNT]);

    bld->type = rand() % 3;
    bld->year = 1970 + rand() % 55;
    bld->has_elevator = rand() % 2;
    bld->has_chute = rand() % 2;
    bld->apartments = 20 + rand() % 300;
    bld->floors = 2 + rand() % 25;
    bld->avg_area = 30.0 + (rand() % 100) / 2.0;
}
