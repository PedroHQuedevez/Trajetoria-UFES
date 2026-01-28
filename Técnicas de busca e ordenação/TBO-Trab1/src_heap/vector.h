#ifndef _VECTOR_H
#define _VECTOR_H

typedef void *data_type;
typedef struct Vector Vector;

int return_allocated(Vector *v);
Vector *vector_construct();
int vector_size(Vector *v);
data_type vector_get(Vector *v, int i);
void vector_set(Vector *v, int i, data_type val);
void vector_push_back(Vector *v, data_type val);
int vector_find(Vector *v, data_type val);
data_type vector_remove(Vector *v, int i);
data_type vector_pop_front(Vector *v);
data_type vector_pop_back(Vector *v);
void vector_insert(Vector *v, int i, data_type val);
void vector_swap(Vector *v, int i, int j);
void vector_destroy(Vector *v);
void vector_clear(Vector *v);
void vector_qsort(Vector *v, int (cmp)(const void *, const void *));

#endif
