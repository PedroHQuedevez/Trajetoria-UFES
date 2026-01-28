#include <stdlib.h>
#include <stdio.h>
#include "arvore_binaria.h"

typedef struct No No;
typedef struct No {
    Vertice *vertice;
    No *left;
    No *right;
} No;

typedef struct ArvoreBinaria
{
    No *root;
} ArvoreBinaria;

No *no_construct(Vertice *v)
{
    // printf("no_construct start\n"); // debug
    No *n = (No *)calloc(1, sizeof(No));
    n->vertice = v;
    n->left = NULL;
    n->right = NULL;
    // printf("no_construct end\n"); // debug
    return n;
}

void no_destroy(No *n)
{
    free(n);
}

void no_destroy_recursivo(No *n)
{
    if (n == NULL) return;
    // printf("no_destroy_recursivo start\n"); // debug

    // recursivamente destroi os outros nós da árvore
    no_destroy_recursivo(n->left);
    no_destroy_recursivo(n->right);
    free(n);
    // printf("no_destroy_recursivo end\n"); // debug
}

void node_print(No *n) // debug
{
    if (n == NULL) return;

    printf("(");
    node_print(n->left);
    // printf("%p || l: %p r: %p || %p ", n, n->left, n->right, n->vertice); // debug
    printf(" %.2f ", vertice_get_distancia_origem(n->vertice));
    // printf("|| l: %.2f r: %.2f\n", n->left == NULL ? -1 : vertice_get_distancia_origem(n->left->vertice), n->right == NULL ? -1 : vertice_get_distancia_origem(n->right->vertice));
    node_print(n->right);
    printf(")");
}

ArvoreBinaria *arvore_binaria_construct()
{
    // printf("arvore_binaria_construct start\n"); // debug
    ArvoreBinaria *ab = (ArvoreBinaria *)calloc(1, sizeof(ArvoreBinaria));
    ab->root = NULL;
    return ab;
    // printf("arvore_binaria_construct end\n"); // debug
}

int arvore_binaria_vazia(ArvoreBinaria *ab)
{
    return ab->root == NULL;
}

void arvore_binaria_push(ArvoreBinaria *ab, Vertice *v)
{
    // printf("arvore_binaria_push start\n"); // debug
    No *novo = no_construct(v);
    
    if (ab->root == NULL) ab->root = novo;
    else
    {
        No *atual = ab->root;
        while (1)
        {
            if (vertice_get_distancia_origem(v) <= vertice_get_distancia_origem(atual->vertice))
            {
                if (atual->left != NULL) atual = atual->left;
                else
                {
                    atual->left = novo;
                    break;
                }
            }
            else
            {
                if (atual->right != NULL) atual = atual->right;
                else
                {
                    atual->right = novo;
                    break;
                }
            }
        }
    }
    //printf("ab: "); // debug
    //node_print(ab->root); // debug
    //printf("\n"); // debug
    // printf("arvore_binaria_push end\n"); // debug
}

void arvore_binaria_remove(ArvoreBinaria *ab, Vertice *v)
{
    // printf("arvore_binaria_remove start\n"); // debug
    // itera até achar o nó correspondente ao vértice
    No *atual = ab->root, *pai = NULL;
    int pai_left = 0;
    while (1)
    {
        if (atual == NULL) return; // o vertice nao foi encontrado na arvore

        if (atual->vertice == v) break; // compara vertices por ponteiro

        pai = atual;
        if (vertice_get_distancia_origem(v) <= vertice_get_distancia_origem(atual->vertice))
        {
            atual = atual->left;
            pai_left = 1;
        }
        else
        {
            atual = atual->right;
            pai_left = 0;
        }
    }

    // corrige a árvore caso o nó tenha filhos
    // caso tenha filhos à esquerda e à direita
    if (atual->left != NULL)
    {
        // coloca o filho à esquerda do nó a ser removido como filho do pai do nó a ser removido
        // ou como root da árvore caso o nó a ser removido já seja o root
        if (pai == NULL) ab->root = atual->left;
        else if (pai_left) pai->left = atual->left;
        else pai->right = atual->left;

        if (atual->right != NULL)
        {
            // encontra nó mais à direita dentre os filhos à esquerda do nó a ser removido
            // itera até achar o nó mínimo
            No *novo_pai = atual->left; // nó que vai ser o novo pai da subárvore à direita do nó a ser removido
            while (novo_pai->right != NULL) novo_pai = novo_pai->right;
            novo_pai->right = atual->right;
        }
    }
    else if (atual->right != NULL)
    {
        // coloca o filho à direita do nó a ser removido como filho do pai do nó a ser removido
        // ou como root da árvore caso o nó a ser removido já seja o root
        if (pai == NULL) ab->root = atual->right;
        else if (pai_left) pai->left = atual->right;
        else pai->right = atual->right;
    }
    else
    {
        if (pai == NULL) ab->root = NULL;
        else if (pai_left) pai->left = NULL;
        else pai->right = NULL;
    }

    // destroi o nó
    no_destroy(atual);

    //printf("ab: "); // debug
    //node_print(ab->root); // debug
    // printf("\n"); // debug

    // printf("arvore_binaria_remove end\n"); // debug
}

Vertice *arvore_binaria_pop_min(ArvoreBinaria *ab)
{
    if (ab->root == NULL)
    {
        printf("Error: arvore_binaria_pop_min: arvore_binaria has size 0.\n");
        exit(0);
    }

    // printf("arvore_binaria_pop_min start\n"); // debug
    // itera até achar o nó mínimo
    No *atual = ab->root, *pai = NULL;
    while (atual->left != NULL)
    {
        // printf("%.2f %.2f\n", atual->vertice->distancia_origem, atual->left->vertice->distancia_origem); // debug
        pai = atual;
        atual = atual->left;
    }
    // printf("atual: %.2f\n", atual->vertice->distancia_origem); // debug

    // corrige a árvore caso o nó mais à esquerda tenha um filho à direita
    if (atual->right != NULL)
    {
        // printf("atual->right != NULL\n"); // debug
        if (pai == NULL) ab->root = atual->right;
        else pai->left = atual->right;
    }
    else
    {
        if (pai == NULL) ab->root = NULL;
        else pai->left = NULL;
    }

    // salva o vértice, destroi o nó e retorna o vértice
    Vertice *v = atual->vertice;
    no_destroy(atual);

    //printf("ab: "); // debug
    //node_print(ab->root); // debug
    //printf("\n"); // debug

    // printf("arvore_binaria_pop_min end\n"); // debug
    return v;
}

void arvore_binaria_destroy(ArvoreBinaria *ab)
{
    no_destroy_recursivo(ab->root);
    free(ab);
}