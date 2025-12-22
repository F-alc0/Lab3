#include "building_table.h"
#include "building.h"
#include "vector.h"

#include <stdio.h>
#include <windows.h>

#define COL_DEVELOPER   22
#define COL_DISTRICT    20
#define COL_TYPE        14
#define COL_YEAR         6
#define COL_FLOORS       8
#define COL_APARTMENTS  22
#define COL_ELEVATOR     6
#define COL_CHUTE       14
#define COL_AREA        10

static void print_padded(FILE *out, const char *text, unsigned int width) {
    if (!out) return;
    if (!text) text = "";

    const unsigned char *p = (const unsigned char *)text;
    unsigned int printed = 0;

    while (*p && printed < width) {
        if ((*p & 0x80) == 0x00) {
            fputc(*p++, out);
        } else if ((*p & 0xE0) == 0xC0) {
            fputc(*p++, out); fputc(*p++, out);
        } else if ((*p & 0xF0) == 0xE0) {
            fputc(*p++, out); fputc(*p++, out); fputc(*p++, out);
        } else if ((*p & 0xF8) == 0xF0) {
            fputc(*p++, out); fputc(*p++, out);
            fputc(*p++, out); fputc(*p++, out);
        } else {
            fputc(*p++, out);
        }
        printed++;
    }

    while (printed++ < width)
        fputc(' ', out);
}

void print_building_table_header(FILE *out) {
    if (!out) return;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    print_padded(out, "Застройщик", COL_DEVELOPER);
    print_padded(out, "Район", COL_DISTRICT);
    print_padded(out, "Тип", COL_TYPE);
    print_padded(out, "Год", COL_YEAR);
    print_padded(out, "Этажи", COL_FLOORS);
    print_padded(out, "Количество квартир", COL_APARTMENTS);
    print_padded(out, "Лифт", COL_ELEVATOR);
    print_padded(out, "Мусоропровод", COL_CHUTE);
    fprintf(out, "%-*s\n", COL_AREA, "Площадь");

    int total =
        COL_DEVELOPER + COL_DISTRICT + COL_TYPE + COL_YEAR +
        COL_FLOORS + COL_APARTMENTS + COL_ELEVATOR +
        COL_CHUTE + COL_AREA;

    for (int i = 0; i < total; i++) fputc('-', out);
    fputc('\n', out);
}

void print_building_table_row(const Building *b, FILE *out) {
    if (!b || !out) return;

    const char *type_str = "Неизв.";
    if (b->type == PANEL) type_str = "Панельный";
    else if (b->type == BRICK) type_str = "Кирпичный";
    else if (b->type == MONOLITH) type_str = "Монолитный";

    print_padded(out, b->developer, COL_DEVELOPER);
    print_padded(out, b->district, COL_DISTRICT);
    print_padded(out, type_str, COL_TYPE);
    fprintf(out, "%-*d", COL_YEAR, b->year);
    fprintf(out, "%-*u", COL_FLOORS, b->floors);
    fprintf(out, "%-*d", COL_APARTMENTS, b->apartments);
    print_padded(out, b->has_elevator ? "ДА" : "НЕТ", COL_ELEVATOR);
    print_padded(out, b->has_chute ? "ДА" : "НЕТ", COL_CHUTE);
    fprintf(out, "%-*0.1f\n", COL_AREA, b->avg_area);
}

void print_building_table_footer(FILE *out) {
    if (!out) return;

    int total =
        COL_DEVELOPER + COL_DISTRICT + COL_TYPE + COL_YEAR +
        COL_FLOORS + COL_APARTMENTS + COL_ELEVATOR +
        COL_CHUTE + COL_AREA;

    for (int i = 0; i < total; i++) fputc('-', out);
    fputc('\n', out);
}
