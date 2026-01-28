#ifndef _HEAP_H
#define _HEAP_H

#include "vector.h"
#include "vertice.h"

typedef struct Heap
{
    Vector *vertices;
} Heap;

Heap *heap_construct();
int heap_size(Heap *h);
int heap_find(Heap *h, Vertice *v);
void heapify_down(Heap *h, int i);
void heapify_up(Heap *h, int i);
void heap_push(Heap *h, Vertice *v);
Vertice *heap_pop(Heap *h);
void heap_destroy(Heap *h);

#endif