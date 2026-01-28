#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "../Arvore/bst.h"

#define initial_size 10

typedef struct queue
{
    bst_node **vector;
    int size;
    int allocated;
} queue;

queue *queue_create()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->vector = (bst_node **)malloc(initial_size * sizeof(bst_node *));
    q->size = initial_size;
    q->allocated = 0;
    return q;
}

int queue_size(queue *q)
{
    return q->allocated;
}

void queue_push(queue *q, bst_node *node)
{
    if (q->allocated == q->size)
    {
        q->size *= 2;
        q->vector = (bst_node **)realloc(q->vector, q->size * sizeof(bst_node *));
    }
    q->vector[q->allocated] = node;
    q->allocated++;
}

bst_node *queue_pop(queue *q)
{
    if (q->allocated == 0)
    {
        printf("Queue is empty\n");
        return 0;
    }
    bst_node *node_pop = q->vector[0];
    for (int i = 0; i < q->allocated - 1; i++)
    {
        q->vector[i] = q->vector[i + 1];
    }
    q->allocated--;
    return node_pop;
}

void queue_destroy(queue *q)
{
    free(q->vector);
    free(q);
}