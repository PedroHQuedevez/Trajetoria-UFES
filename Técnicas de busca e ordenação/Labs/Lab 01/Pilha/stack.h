#ifndef STACK_H
#define STACK_H

#include "../Arvore/bst.h"

typedef struct stack stack;

int return_size(stack *s);
stack *stack_create();
void stack_push(stack *s, bst_node *node);
bst_node *stack_pop(stack *s);
void stack_destroy(stack *s);

#endif