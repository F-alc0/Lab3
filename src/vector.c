#include "vector.h"
#include <stdlib.h>
#include <string.h>

Vector* vector_create(size_t element_size) {
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    if (!vec) return NULL;
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->element_size = element_size;
    return vec;
}

void vector_destroy(Vector *vec) {
    if (!vec) return;
    free(vec->data);
    free(vec);
}

size_t vector_size(const Vector *vec) {
    return vec ? vec->size : 0;
}