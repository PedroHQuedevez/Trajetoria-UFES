#include <stdio.h>
#include <stdlib.h>
#include "tnode.h"
#include "heap.h"
#include "vector.h"

Vector *inicia_vetor_visitados(int size)
{
    Vector *visitados = vector_construct();

    for (int i = 0; i < size; i++)
    {
        int *valor_inicial = (int *)malloc(sizeof(int));
        *valor_inicial = 0;
        vector_push_back(visitados, valor_inicial);
    }
    // printf("***%i\n", visitados->size);
    return visitados;
}

Heap *inicia_vetor_nao_visitados(NodeList *list)
{
    Heap *nao_visitados = heap_construct();
    return nao_visitados;
}

Vector *inicia_antecessores(NodeList *list)
{
    Vector *antecessores = vector_construct();

    for (int i = 0; i < list->size; i++)
    {
        int *valor_inicial = (int *)malloc(sizeof(int));
        *valor_inicial = -1;
        vector_push_back(antecessores, valor_inicial);
    }
    return antecessores;
}

int existe_no_nao_visitado(Vector *booleanos)
{
    for (int i = 0; i < booleanos->size; i++)
    {
        int *valor = (int *)vector_get(booleanos, (i));

        if (*valor != 1)
        {
            return 1;
        }
    }
    return 0;
}

void adiciona_vizinhos_heap_nao_visitados(Heap *nao_visitados, Node *node_atual)
{
    for (int i = 0; i < node_atual->vizinhos->size; i++)
    {
        Conexao *conexao = (Conexao *)node_atual->vizinhos->data[i];

        heap_push(nao_visitados, conexao, conexao->custo);
    }
}

void adciona_conexao_heap_nao_visitados(Heap *nao_visitados, Conexao *conexao)
{
    heap_push(nao_visitados, conexao, conexao->custo);
}

void atualiza_vetor_visitados(Vector *visitados, int idx)
{

    int *val = (int *)vector_get(visitados, (idx));
    *val = 1;
}

void atualiza_vetor_antecessores(Vector *antecessores, Conexao *conexao_atual)
{
    int *aux = vector_get(antecessores, conexao_atual->numero_node);
    *aux = conexao_atual->parent;
}

int verifica_no_ja_visitado(Vector *visitados, int idx)
{

    int *val = vector_get(visitados, (idx));
    return *val;
}

void destroy_null(void *vazio)
{
}

void printa_invertido(Vector *antecessores, int val)
{
    if (val < antecessores->size && val >= 0)
    {
        int *v = (int *)vector_get(antecessores, val);
        if (*v != -1)
        {
            printa_invertido(antecessores, *v);
            printf(" -> ");
        }
        printf("%i", val);
    }
}

void dijkstra(NodeList *list)
{
    Vector *visitados = inicia_vetor_visitados(list_size(list));
    Heap *nao_visitados = inicia_vetor_nao_visitados(list);
    Vector *antecessores = inicia_antecessores(list);
    float custos[list_size(list)];
    Conexao *node_origem = conexao_construct(-1, 0, 0);

    atualiza_vetor_visitados(visitados, 0);
    atualiza_vetor_antecessores(antecessores, node_origem);
    adiciona_vizinhos_heap_nao_visitados(nao_visitados, node_list_get(list, 0));

    while ((existe_no_nao_visitado(visitados) == 1) && (heap_size(nao_visitados) != 0))
    {
        Conexao *conexao_min = (Conexao *)heap_pop(nao_visitados);
        int *comp = visitados->data[conexao_min->numero_node];
        if (*comp == 0)
        {
            custos[conexao_min->numero_node] = conexao_min->custo;
            Node *node_atual = node_list_get(list, conexao_min->numero_node);
            atualiza_vetor_visitados(visitados, conexao_min->numero_node);
            atualiza_vetor_antecessores(antecessores, conexao_min);

            for (int i = 0; i < node_atual->size_vizinhos; i++)
            {
                Conexao *vizinho = node_atual->vizinhos->data[i];
                if (verifica_no_ja_visitado(visitados, vizinho->numero_node) == 0)
                {
                    Conexao *conexao_vizinha = obtem_conexao_vetor_vizinhos(node_atual->vizinhos, i);
                    conexao_vizinha->custo = conexao_vizinha->custo + custos[conexao_vizinha->parent];
                    adciona_conexao_heap_nao_visitados(nao_visitados, conexao_vizinha);
                }
            }
        }
    }

    for (int i = 1; i < list->size; i++)
    {
        printa_invertido(antecessores, i);
        printf(": %.2f\n", custos[i]);
        // printf("0 -> %i", i);
        // int *val = (int *)vector_get(antecessores, i);
        // while (*val != -1 && *val != 0)
        // {
        //     printf(" -> %i", *val);
        //     val = (int *)vector_get(antecessores, *val);
        // }
        // printf(" %.2f\n", custos[i]);
    }

    for (int i = 0; i < list->size; i++)
    {
        free(antecessores->data[i]);
        free(visitados->data[i]);
    }
    vector_destroy(antecessores);
    vector_destroy(visitados);
    free(node_origem);
    heap_destroy(nao_visitados, destroy_null);
}
