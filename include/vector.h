#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;

Vector* vector_create(size_t element_size);
void vector_destroy(Vector *vec);
size_t vector_size(const Vector *vec);

#endif