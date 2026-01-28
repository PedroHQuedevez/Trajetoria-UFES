#include <stdbool.h>

// typedef unsigned char bool;
typedef struct Heap Heap;

Heap *heap_construct();                                       // O(1)
void heap_push(Heap *heap, void *data, double priority);      // O(log N)
bool heap_empty(Heap *heap);                                  // O(1)
void *heap_max(Heap *heap);                                   // O(1)
double heap_max_priority(Heap *heap);                         // O(1)
void *heap_pop(Heap *heap);                                   // O(log N)
void heap_destroy(Heap *heap, void (*destroy_fn)(data_type)); // O(1)
void heap_sort(void *array, int array_size, int item_size, double (*key_fn)(void *));