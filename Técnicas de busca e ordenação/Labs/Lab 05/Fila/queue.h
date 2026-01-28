#ifndef QUEUE_H
#define QUEUE_H

#include "../Arvore/bst.h"

typedef struct queue queue;

queue *queue_create();
int queue_size(queue *q);
void queue_push(queue *q, bst_node *node);
bst_node *queue_pop(queue *q);
void queue_destroy(queue *q);

#endif