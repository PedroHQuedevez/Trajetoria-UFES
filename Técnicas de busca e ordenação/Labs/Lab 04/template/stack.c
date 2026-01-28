#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

#define initial_size 10

typedef struct stack
{
    int *vector;
    int size;
    int allocated;
} stack;

bool stack_empty(stack *s)
{
    if (s->allocated == 0)
    {
        return true;
    }
    return false;
}

int return_size(stack *s)
{
    return s->allocated;
}

stack *stack_create()
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->vector = (int *)malloc(initial_size * sizeof(int));
    s->size = initial_size;
    s->allocated = 0;
    return s;
}

void stack_push(int i, stack *s)
{
    if (s->allocated == s->size)
    {
        s->size *= 2;
        s->vector = (int *)realloc(s->vector, s->size * sizeof(int));
    }
    s->vector[s->allocated] = i;
    s->allocated++;
}

int stack_pop(stack *s)
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
