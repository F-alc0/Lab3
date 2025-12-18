#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "vector.h"

typedef int (*Comparator)(const void *, const void *);

void quick_sort(Vector *vec, Comparator cmp);

#endif
