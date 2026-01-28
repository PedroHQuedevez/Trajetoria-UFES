#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

static const int VECTOR_INIT_SIZE = 10;
static const int VECTOR_GROWTH_RATE = 2;

typedef struct Vector
{
    data_type *data;
    int size;
    int allocated;
} Vector;

int return_allocated(Vector *v)
{
    return v->allocated;
}

Vector *vector_construct()
{
    Vector *v = (Vector *)calloc(1, sizeof(Vector));

    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));

    return v;
}

int vector_size(Vector *v)
{
    return v->size;
}

data_type vector_get(Vector *v, int i)
{
    if (i >= vector_size(v))
    {
        printf("Error: vector_get: invalid index %d for vector with size %d.\n", i, vector_size(v));
        exit(0);
    }

    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val)
{
    if (i >= vector_size(v))
    {
        printf("Error: vector_set: invalid index %d for vector with size %d.\n", i, vector_size(v));
        exit(0);
    }

    v->data[i] = val;
}

void vector_push_back(Vector *v, data_type val)
{
    if (v->size >= v->allocated)
    {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

int vector_find(Vector *v, data_type val)
{
    int i = 0;
    while (i < vector_size(v))
    {
        if (vector_get(v, i) == val)
            return i;
        i++;
    }

    return -1;
}

data_type vector_remove(Vector *v, int i)
{
    if (i >= v->size || i < 0)
    {
        printf("Error: vector_remove: invalid index %d for vector with size %d.\n", i, v->size);
        exit(0);
    }

    data_type val = v->data[i];

    if (i == v->size - 1)
    {
        v->size--;
        return val;
    }

    for (int j = i; j < v->size - 1; j++)
        v->data[j] = v->data[j + 1];

    v->size--;

    return val;
}

data_type vector_pop_front(Vector *v)
{
    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v)
{
    return vector_remove(v, v->size - 1);
}

void vector_insert(Vector *v, int i, data_type val)
{
    if (i < 0 || i > v->size)
    {
        printf("Error: vector_insert: invalid index %d for vector with size %d.\n", i, v->size);
        exit(0);
    }

    if (v->size == v->allocated)
    {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    for (int j = v->size; j > i; j--)
        v->data[j] = v->data[j - 1];

    v->data[i] = val;
    v->size++;
}

void vector_swap(Vector *v, int i, int j)
{
    if (i < 0 || i >= v->size || j < 0 || j >= v->size)
    {
        printf("Error: vector_swap: invalid indices %d and %d for vector with size %d.\n", i, j, v->size);
        exit(0);
    }

    data_type temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
}

void vector_destroy(Vector *v)
{
    free(v->data);
    free(v);
}

void vector_clear(Vector *v)
{
    v->size = 0;
}

void vector_qsort(Vector *v, int (cmp)(const void *, const void *))
{
    qsort(v->data, v->size, sizeof(void *), cmp);
}