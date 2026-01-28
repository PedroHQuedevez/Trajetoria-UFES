#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"

Vertice *vertice_construct(int id)
{
    Vertice *v = (Vertice *)calloc(1, sizeof(Vertice));
    v->id = id;
    v->id_pai = -1;
    v->distancia_origem = FLT_MAX;
    v->arestas = vector_construct();
    return v;
}

int vertice_get_id(Vertice *v)
{
    return v->id;
}

int vertice_get_id_pai(Vertice *v)
{
    return v->id_pai;
}

void vertice_set_id_pai(Vertice *v, int id_pai)
{
    v->id_pai = id_pai;
}

float vertice_get_distancia_origem(Vertice *v)
{
    return v->distancia_origem;
}

void vertice_set_distancia_origem(Vertice *v, float distancia_origem)
{
    v->distancia_origem = distancia_origem;
}

Vector *vertice_get_arestas(Vertice *v)
{
    return v->arestas;
}

void vertice_add_aresta(Vertice *v, Aresta *a)
{
    vector_push_back(v->arestas, a);
}

void vertice_destroy(Vertice *v)
{
    // destroi todas as arestas
    for (int i = 0; i < vector_size(v->arestas); i++) {
        aresta_destroy(vector_get(v->arestas, i));
    }

    // destroi o vetor de arestas
    vector_destroy(v->arestas);

    free(v);
}

int cmp_vertice(const void *a, const void *b)
{
    Vertice *va = (Vertice *)*(void **)a;
    Vertice *vb = (Vertice *)*(void **)b;

    if (va->distancia_origem < vb->distancia_origem) return -1;
    return 1;
}