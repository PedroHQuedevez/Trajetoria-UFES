#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "../Arvore/bst.h"

#define initial_size 10

typedef struct stack
{
    bst_node **vector;
    int size;
    int allocated;
} stack;

int return_size(stack *s)
{
    return s->allocated;
}

stack *stack_create()
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->vector = (bst_node **)malloc(initial_size * sizeof(bst_node *));
    s->size = initial_size;
    s->allocated = 0;
    return s;
}

void stack_push(stack *s, bst_node *node)
{
    if (s->allocated == s->size)
    {
        s->size *= 2;
        s->vector = (bst_node **)realloc(s->vector, s->size * sizeof(bst_node *));
    }
    s->vector[s->allocated] = node;
    s->allocated++;
}

bst_node *stack_pop(stack *s)
{
    if (s->allocated == 0)
    {
        printf("Stack is empty\n");
        return 0;
    }
    s->allocated--;
    return s->vector[s->allocated];
}

void stack_destroy(stack *s)
{
    free(s->vector);
    free(s);
}
