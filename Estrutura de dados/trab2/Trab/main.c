
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "heap.h"
#include "tnode.h"
#include "dijkstra.h"

int main(int argc, char *argv[])
{
    NodeList *list = node_list_construct();
    read_list(list, argv[1]);
    dijkstra(list);
    // print_list(list);
    list_destroy(list);
    return 0;
}

// testando o heap;

// typedef struct HeapNodeData
// {
//     int ponto;
// } HeapNodeData;

// void node_data_printf(void *nodedata)
// {
//     HeapNodeData *data = (HeapNodeData *)nodedata;
//     printf("%d ", data->ponto);
// }

// void node_data_free(void *nodedata)
// {
//     HeapNodeData *data = (HeapNodeData *)nodedata;
//     free(data);
// }

// int main()
// {
//     Heap *heap = heap_construct();
//     for (int i = 0; i < 15; i++)
//     {
//         char comando[10];
//         scanf("%s ", comando);

//         if (strcmp(comando, "PUSH") == 0)
//         {
//             int priority;
//             scanf("%i\n", &priority);
//             // printf("%i\n", priority);
//             HeapNodeData *data = (HeapNodeData *)malloc(sizeof(HeapNodeData));
//             data->ponto = i;

//             heap_push(heap, data, priority);
//         }
//         else if (strcmp(comando, "POP") == 0)
//         {
//             HeapNode *node_data_removed = heap_pop(heap);

//             // node_destroy(node_data_removed, node_data_free);
//         }
//     }

//     heap_printf(heap, node_data_printf);
//     printf("\n");
//     // heap_destroy(heap, node_data_free);
//     return 0;
// }