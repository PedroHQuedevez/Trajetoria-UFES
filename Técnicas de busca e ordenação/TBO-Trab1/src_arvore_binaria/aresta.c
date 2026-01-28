#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"

Aresta *aresta_construct(int origem, int destino, float peso)
{
    Aresta *a = (Aresta *)calloc(1, sizeof(Aresta));
    a->origem = origem;
    a->destino = destino;
    a->peso = peso;
    return a;
}

int aresta_get_origem(Aresta *a)
{
    return a->origem;
}

int aresta_get_destino(Aresta *a)
{
    return a->destino;
}

float aresta_get_peso(Aresta *a)
{
    return a->peso;
}

void aresta_destroy(Aresta *a)
{
    free(a);
}