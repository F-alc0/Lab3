#ifndef CLI_H
#define CLI_H

#include <stdio.h>

typedef enum {
    MODE_NONE,
    MODE_GENERATE,
    MODE_SORT,
    MODE_PRINT
} Mode;

typedef enum {
    SORT_ASC,
    SORT_DESC
} SortType;

#endif