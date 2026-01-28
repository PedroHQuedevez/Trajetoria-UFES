#ifndef VERTICE_H
#define VERTICE_H

#include "vector.h"
#include "aresta.h"

typedef struct {
    int id;
    int id_pai;
    float distancia_origem;
    Vector *arestas;
} Vertice;

Vertice *vertice_construct(int id);
int vertice_get_id(Vertice *v);
int vertice_get_id_pai(Vertice *v);
void vertice_set_id_pai(Vertice *v, int id_pai);
float vertice_get_distancia_origem(Vertice *v);
void vertice_set_distancia_origem(Vertice *v, float distancia_origem);
Vector *vertice_get_arestas(Vertice *v);
void vertice_add_aresta(Vertice *v, Aresta *a);
void vertice_destroy(Vertice *v);
int cmp_vertice(const void *a, const void *b);

#endif
