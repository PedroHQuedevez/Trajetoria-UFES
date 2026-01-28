#ifndef _TNODE_H
#define _TNODE_H

#include "vector.h"

typedef struct NodeList
{
    Vector *nodes;
    int size;
} NodeList;

typedef struct Node
{
    int numero_node;
    Vector *vizinhos;
    int size_vizinhos;
} Node;

typedef struct Conexao
{
    int parent;
    int numero_node;
    float custo;
} Conexao;

NodeList *node_list_construct();
void read_list(NodeList *list, char *path);
void list_destroy(NodeList *list);
void print_list(NodeList *list);
Node *node_list_get(NodeList *list, int idx);
int list_size(NodeList *list);
Conexao *conexao_construct(int parent, int numero_node, float custo);
void Conexao_destroy(Conexao *node);
float obtem_custo_conexao(void *item);
void atualiza_custo_total_conexao(float custo_total, Conexao *conexao);
Conexao *obtem_conexao_vetor_vizinhos(Vector *vizinhos, int idx);
#endif