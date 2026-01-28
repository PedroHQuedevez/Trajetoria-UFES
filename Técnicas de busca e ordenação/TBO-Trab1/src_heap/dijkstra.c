#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

void dijkstra(Vector *vertices, int source)
{
    // constroi o heap de não-visitados e insere o vértice inicial
    Heap *nao_visitados = heap_construct();
    heap_push(nao_visitados, (Vertice *)vector_get(vertices, source));

    // variáveis buffer
    Vertice *origem, *destino;
    float peso;
    Vector *arestas;
    Aresta *a;
    int idx;

    while (heap_size(nao_visitados) > 0)
    {
        origem = heap_pop(nao_visitados);
        arestas = vertice_get_arestas(origem);

        for (int i = 0; i < vector_size(arestas); i++) {
            a = (Aresta *)vector_get(arestas, i);
            destino = (Vertice *)vector_get(vertices, aresta_get_destino(a));
            peso = aresta_get_peso(a);

            if (vertice_get_distancia_origem(origem) + peso < vertice_get_distancia_origem(destino))
            {
                vertice_set_id_pai(destino, vertice_get_id(origem));
                vertice_set_distancia_origem(destino, vertice_get_distancia_origem(origem) + peso);

                idx = heap_find(nao_visitados, destino);
                if (idx >= 0) heapify_up(nao_visitados, idx);
                else heap_push(nao_visitados, destino);
            }
        }
    }
    heap_destroy(nao_visitados);
}