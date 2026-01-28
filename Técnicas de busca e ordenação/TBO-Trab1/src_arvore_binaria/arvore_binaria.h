#ifndef _ARVORE_BINARIA_H
#define _ARVORE_BINARIA_H

#include "vector.h"
#include "vertice.h"

typedef struct ArvoreBinaria ArvoreBinaria;

ArvoreBinaria *arvore_binaria_construct();
int arvore_binaria_vazia(ArvoreBinaria *ab);
void arvore_binaria_push(ArvoreBinaria *ab, Vertice *v);
void arvore_binaria_remove(ArvoreBinaria *ab, Vertice *v);
Vertice *arvore_binaria_pop_min(ArvoreBinaria *ab);
void arvore_binaria_destroy(ArvoreBinaria *ab);

#endif