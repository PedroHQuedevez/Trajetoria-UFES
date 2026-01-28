#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "vector.h"

static const int HEAP_INIT_SIZE = 10;

struct HeapNode
{
    void *data;
    double priority;
};

struct Heap
{
    Vector *nodes;
    int size;
    int capacity;
};

Heap *heap_construct()
{
    Heap *heap = (Heap *)calloc(1, sizeof(Heap));
    heap->nodes = vector_construct();
    heap->capacity = HEAP_INIT_SIZE;
    heap->size = 0;
    return heap;
}

HeapNode *heapnode_construct(void *data, double priority)
{
    HeapNode *node = (HeapNode *)calloc(1, sizeof(HeapNode));
    node->data = data;
    node->priority = priority;
    return node;
}

bool heap_empty(Heap *heap)
{
    if (heap->size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void *heap_max(Heap *heap) // retornar o node todo ou o void *data?
{
    HeapNode *node_get = vector_get(heap->nodes, 0);
    return node_get->data;
}

double heap_max_priority(Heap *heap)
{
    HeapNode *node_get = (HeapNode *)vector_get(heap->nodes, 0);
    return node_get->priority;
}

void heapnode_destroy(void *node, void (*destroy_fn)(data_type))
{
    HeapNode *node_destroy = (HeapNode *)node;
    destroy_fn(node_destroy->data);
    free(node_destroy);
}

void heap_destroy(Heap *heap, void (*destroy_fn)(data_type))
{
    for (int i = 0; i < heap->size; i++)
    {
        // HeapNode *node_aux = (HeapNode *)vector_get(heap->nodes, i);
        // destroy_fn(node_aux->data);
        // free(node_aux);
        heapnode_destroy(vector_get(heap->nodes, i), destroy_fn);
    }
    vector_destroy(heap->nodes);
    free(heap);
}

void heap_sort(void *array, int array_size, int item_size, double (*key_fn)(void *))
{
}

void swap_nodes(Heap *heap, int i, int j)
{
    vector_swap(heap->nodes, i, j);
}

void heapify_up(Heap *heap, int idx)
{
    int parent_idx = (idx - 1) / 2;
    if (parent_idx >= 0)
    {
        HeapNode *current = (HeapNode *)vector_get(heap->nodes, idx);
        HeapNode *parent = (HeapNode *)vector_get(heap->nodes, parent_idx);

        if (current->priority < parent->priority)
        {
            swap_nodes(heap, idx, parent_idx);
            heapify_up(heap, parent_idx);
        }
    }
}

void heapify_down(Heap *heap, int current_idx)
{
    if (current_idx < heap->size)
    {
        int max_idx = current_idx;
        int left_child_idx = (2 * current_idx) + 1;
        int right_child_idx = (2 * current_idx) + 2;

        HeapNode *current_node = vector_get(heap->nodes, current_idx);
        HeapNode *max_node = current_node;

        if (left_child_idx < heap->size)
        {
            HeapNode *left_child = vector_get(heap->nodes, left_child_idx);
            if (left_child->priority < max_node->priority)
            {
                max_idx = left_child_idx;
                max_node = left_child;
            }
        }

        if (right_child_idx < heap->size)
        {
            HeapNode *right_child = vector_get(heap->nodes, right_child_idx);
            if (right_child->priority < max_node->priority)
            {
                max_idx = right_child_idx;
                max_node = right_child;
            }
        }

        if (current_idx != max_idx)
        {
            swap_nodes(heap, current_idx, max_idx);
            heapify_down(heap, max_idx);
        }
    }
}

void heap_push(Heap *heap, void *data, double priority)
{
    vector_push_back(heap->nodes, heapnode_construct(data, priority));
    heapify_up(heap, heap->size);
    heap->size++;
}

void *heap_pop(Heap *heap)
{
    HeapNode *node_removed = (HeapNode *)vector_get(heap->nodes, 0);
    void *data = node_removed->data;
    // free(node_removed);
    vector_set(heap->nodes, 0, vector_get(heap->nodes, vector_size(heap->nodes) - 1));
    vector_pop_back(heap->nodes);

    heap->size--;
    heapify_down(heap, 0);
    free(node_removed);
    // printf("%.2f ", node_removed->priority);

    return data;
}

void heap_printf(Heap *heap, heap_node_printf node_print)
{
    for (int idx = 1; idx < heap->size; idx++)
    {
        HeapNode *n = (HeapNode *)vector_get(heap->nodes, idx);
        // printf("%.2f ", n->priority);
        node_print(n->data);
    }
}

int heap_size(Heap *heap)
{
    return heap->size;
}