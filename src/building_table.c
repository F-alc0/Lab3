#include "building_table.h"
#include "building.h"

#include <string.h>
#include <windows.h>

static void print_padded(FILE *out, const char *text, unsigned int width) {
    if (!out) return;
    if (!text) text = "";

    const unsigned char *p = (const unsigned char *)text;
    unsigned int printed = 0;

    while (*p && printed < width) {
        if ((*p & 0x80) == 0x00) {
            fputc(*p++, out);
        } else if ((*p & 0xE0) == 0xC0) {
            fputc(*p++, out);
            fputc(*p++, out);
        } else if ((*p & 0xF0) == 0xE0) {
            fputc(*p++, out);
            fputc(*p++, out);
            fputc(*p++, out);
        } else if ((*p & 0xF8) == 0xF0) {
            fputc(*p++, out);
            fputc(*p++, out);
            fputc(*p++, out);
            fputc(*p++, out);
        } else {
            fputc(*p++, out);
        }
        printed++;
    }

    while (printed++ < width) {
        fputc(' ', out);
    }
}

void print_buildings_table(const Vector *vec, FILE *out) {
    if (!vec || !out) return;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const unsigned int dev   = 20;
    const unsigned int dist  = 18;
    const unsigned int type  = 10;
    const unsigned int year  = 6;
    const unsigned int floor = 7;
    const unsigned int flats = 8;
    const unsigned int elev  = 6;
    const unsigned int chute = 6;
    const unsigned int area  = 10;

    print_padded(out, "Застройщик", dev);
    print_padded(out, "Район", dist);
    print_padded(out, "Тип", type);
    print_padded(out, "Год", year);
    print_padded(out, "Этажи", floor);
    print_padded(out, "Кв.", flats);
    print_padded(out, "Лифт", elev);
    print_padded(out, "Мус.", chute);
    fprintf(out, "%-*s\n", (int)area, "Площадь");

    unsigned int total =
        dev + dist + type + year + floor + flats + elev + chute + area;
    for (unsigned int i = 0; i < total; i++) fputc('-', out);
    fputc('\n', out);

    for (size_t i = 0; i < vec->size; i++) {
        const Building *b = vector_at((Vector *)vec, i);

        const char *type_str = "Неизв.";
        if (b->type == PANEL) type_str = "Панель";
        else if (b->type == BRICK) type_str = "Кирпич";
        else if (b->type == MONOLITH) type_str = "Монолит";

        print_padded(out, b->developer, dev);
        print_padded(out, b->district, dist);
        print_padded(out, type_str, type);
        fprintf(out, "%-*d", (int)year, b->year);
        fprintf(out, "%-*u", (int)floor, b->floors);
        fprintf(out, "%-*d", (int)flats, b->apartments);
        print_padded(out, b->has_elevator ? "ДА" : "НЕТ", elev);
        print_padded(out, b->has_chute ? "ДА" : "НЕТ", chute);
        fprintf(out, "%-*0.1f\n", (int)area, b->avg_area);
    }
}
