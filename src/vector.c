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

void* vector_at(const Vector *vec, size_t index) {
    if (!vec || index >= vec->size) return NULL;
    return (char*)vec->data + index * vec->element_size;
}

void* vector_begin(const Vector *vec) {
    return vec ? vec->data : NULL;
}

void* vector_end(const Vector *vec) {
    if (!vec || vec->size == 0) return NULL;
    return (char*)vec->data + vec->size * vec->element_size;
}

void* vector_next(const Vector *vec, void *current) {
    if (!vec || !current) return NULL;
    char *next = (char*)current + vec->element_size;
    if (next >= (char*)vec->data + vec->size * vec->element_size) {
        return NULL;
    }
    return next;
}

void* vector_prev(const Vector *vec, void *current) {
    if (!vec || !current || current == vec->data) return NULL;
    char *prev = (char*)current - vec->element_size;
    if (prev < (char*)vec->data) {
        return NULL;
    }
    return prev;
}