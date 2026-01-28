#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "arvore_binaria.h"
#include "vector.h"

void dijkstra(ArvoreBinaria *arvore, Vector *vertices, int origem){
    int numero_de_vertices = vector_size(vertices);

    // Inicializa as distâncias
    for (int i = 0; i < numero_de_vertices; i++) {
        Vertice *v = (Vertice *)vector_get(vertices, i);
        if (v->id == origem) {
            vertice_set_distancia_origem(v, 0);
        } else {
            vertice_set_distancia_origem(v, FLT_MAX);
        }
        arvore_binaria_push(arvore, v);
    }

    // Processa os vértices
    while (!arvore_binaria_vazia(arvore)) {
        Vertice *vertice_atual = arvore_binaria_pop_min(arvore);
        int indice_atual = vertice_atual->id;

        // Relaxamento das arestas
        for (int i = 0; i < vector_size(vertice_atual->arestas); i++) {
            Aresta *a = (Aresta *)vector_get(vertice_atual->arestas, i);
            Vertice *vizinho = (Vertice *)vector_get(vertices, a->destino);
            float nova_distancia = vertice_get_distancia_origem(vertice_atual) + a->peso;

            if (nova_distancia < vertice_get_distancia_origem(vizinho)) {
                vertice_set_distancia_origem(vizinho, nova_distancia);
                vertice_set_id_pai(vizinho, vertice_atual->id);
                
                arvore_binaria_remove(arvore, vizinho);
                arvore_binaria_push(arvore, vizinho);
            }
        }
    }
}
