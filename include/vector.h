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
void* vector_at(const Vector *vec, size_t index);
void* vector_begin(const Vector *vec);
void* vector_end(const Vector *vec);
void* vector_next(const Vector *vec, void *current);
void* vector_prev(const Vector *vec, void *current);
void vector_push_back(Vector *vec, const void *element);
void vector_push_front(Vector *vec, const void *element);
void vector_insert(Vector *vec, size_t index, const void *element);
void vector_pop_back(Vector *vec);
void vector_pop_front(Vector *vec);
void vector_erase(Vector *vec, size_t index);
void vector_swap(Vector *vec, size_t i, size_t j);
void vector_clear(Vector *vec);
void vector_from_array(Vector *vec, const void *array, size_t count);
void vector_to_array(const Vector *vec, void *array);

#endif