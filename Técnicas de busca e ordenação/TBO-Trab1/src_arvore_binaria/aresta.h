#ifndef _ARESTA_H
#define _ARESTA_H

typedef struct Aresta
{
    int origem;
    int destino;
    float peso;
} Aresta;

Aresta *aresta_construct(int origem, int destino, float peso);
int aresta_get_origem(Aresta *a);
int aresta_get_destino(Aresta *a);
float aresta_get_peso(Aresta *a);
void aresta_destroy(Aresta *a);

#endif