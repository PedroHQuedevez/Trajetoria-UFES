#include "stdlib.h"
#include "heap.h"
#include "vector.h"

static const int HEAP_INIT_SIZE = 10;

typedef struct
{
    void *data;
    double priority;
} HeapNode;

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

void heap_push(Heap *heap, void *data, double priority)
{
    vector_push_back(heap->nodes, heapnode_construct(data, priority));
    heap->size++;
}

bool heap_empty(Heap *heap)
{
    if (heap->size == 0)
    {
        return true;
    }
    else if (heap->size > 1)
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

void heap_destroy(Heap *heap, void (*destroy_fn)(data_type))
{
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
    int parent_idx = (heap->size - 1) / 2;
    if (parent_idx >= 0)
    {
        HeapNode *current = (HeapNode *)vector_get(heap->nodes->data, idx);
        HeapNode *parent = (HeapNode *)vector_get(heap->nodes->data, parent_idx);

        if (current->priority > parent->priority)
        {
            swap_nodes(heap, idx, parent_idx);
            heapify_up(heap, parent_idx);
        }
    }
}

void heapify_down(Heap *heap, int current_idx)
{
    int future_idx = current_idx;
    int left_child_idx = 2 * (current_idx + 1);
    int right_child_idx = 2 * (current_idx + 2);

    HeapNode *current_node = vector_get(heap->nodes->data, current_idx);
    HeapNode *future_node = current_node;
    if (left_child_idx < heap->size)
    {
        HeapNode *left_child = vector_get(heap->nodes->data, left_child_idx);
        if (left_child->priority > current_node->priority)
        {
            future_idx = left_child_idx;
            future_node = left_child;
        }
    }
    if (right_child_idx < heap->size)
    {
        HeapNode *right_child = vector_get(heap->nodes->data, right_child_idx);
        if ((right_child->priority > current_node->priority) && (right_child->priority > future_node->priority))
        {
            future_idx = right_child_idx;
            future_node = right_child;
        }
    }

    if (current_idx != future_idx)
    {
        swap_nodes(heap, current_idx, future_idx);
        heapify_down(heap, future_idx);
    }
}

void *heap_pop(Heap *heap)
{
    void *node_removed = vector_pop_front(heap->nodes);
    heapify_down(heap, (heap->size - 1));
    return node_removed;
}

void *return_data(HeapNode *node)
{
    return node->data;
}