#ifndef COMB_SORT_H
#define COMB_SORT_H

#include "vector.h"

typedef int (*Comparator)(const void *, const void *);

void comb_sort(Vector *vec, Comparator cmp);

#endif