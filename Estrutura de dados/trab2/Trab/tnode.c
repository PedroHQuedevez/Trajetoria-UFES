#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "tnode.h"

// struct NodeList
// {
//     Vector *nodes;
//     int size;
// };

// struct Node
// {
//     int numero_node;
//     Vector *vizinhos;
//     int size_vizinhos;
// };

// struct Conexao
// {
//     int numero_node;
//     float custo;
// };

NodeList *node_list_construct()
{
    NodeList *list = (NodeList *)calloc(1, sizeof(NodeList));
    list->nodes = vector_construct();
    return list;
}

Node *node_construct(int numero_node)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    node->numero_node = numero_node;
    node->vizinhos = vector_construct();
    return node;
}

Conexao *conexao_construct(int parent, int numero_node, float custo)
{
    Conexao *conexao = (Conexao *)calloc(1, sizeof(Conexao));
    conexao->parent = parent;
    conexao->numero_node = numero_node;
    conexao->custo = custo;
    return conexao;
}

void node_destroy(Node *node)
{
    vector_destroy(node->vizinhos);
    free(node);
}

void Conexao_destroy(Conexao *node)
{
    free(node);
}

void list_destroy(NodeList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        Node *node_aux = (Node *)list->nodes->data[i];

        for (int j = 0; j < node_aux->vizinhos->size; j++)
        {
            Conexao *Conexao_aux = (Conexao *)node_aux->vizinhos->data[j];
            Conexao_destroy(Conexao_aux);
        }
        node_destroy(node_aux);
    }
    vector_destroy(list->nodes);
    free(list);
}

void read_list(NodeList *list, char *path)
{

    FILE *entrada = fopen(path, "r");

    fscanf(entrada, "%d", &list->size);
    for (int i = 0; i < list->size; i++)
    {
        Node *node = node_construct(i);
        vector_push_back(list->nodes, node);

        // printf("%i\n", list->nodes->size);

        while (1)
        {
            char final_linha = 'a';
            int numero_node_vizinho;
            float custo;

            fscanf(entrada, "%d %f%c", &numero_node_vizinho, &custo, &final_linha);

            Conexao *node_vizinho = conexao_construct(i, numero_node_vizinho, custo);

            vector_push_back(node->vizinhos, node_vizinho);
            node->size_vizinhos++;

            if (final_linha != ' ')
            {
                break;
            }
        }
    }
    fclose(entrada);
}

void print_list(NodeList *list)
{

    for (int i = 0; i < list->nodes->size; i++)
    {
        Node *node_aux = (Node *)list->nodes->data[i];
        printf("%i ", node_aux->numero_node);
        for (int j = 0; j < node_aux->vizinhos->size; j++)
        {
            Conexao *Conexao_aux = (Conexao *)node_aux->vizinhos->data[j];
            printf("%i %.0f ", Conexao_aux->numero_node, Conexao_aux->custo);
        }
        printf("\n");
    }
}

Node *node_list_get(NodeList *list, int idx)
{
    if (idx >= list->size)
    {
        printf("idx inválido lista get \n%i\n", idx);
        exit(1);
    }
    Node *node_aux = (Node *)list->nodes->data[idx];
    return node_aux;
}

int list_size(NodeList *list)
{
    return list->size;
}

Conexao *obtem_conexao_vetor_vizinhos(Vector *vizinhos, int idx)
{

    Conexao *c = (Conexao *)vector_get(vizinhos, idx);

    return c;
}

float obtem_custo_conexao(void *item)
{
    Conexao *conexao = (Conexao *)item;
    return conexao->custo;
}

void atualiza_custo_total_conexao(float custo_total, Conexao *conexao)
{
    conexao->custo = custo_total;
}