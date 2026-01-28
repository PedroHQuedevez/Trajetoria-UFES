#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct stack stack;

stack *stack_create();
void stack_push(int i, stack *s);
int stack_pop(stack *s);
void stack_destroy(stack *s);
bool stack_empty(stack *s);
int return_size(stack *s);

#endif