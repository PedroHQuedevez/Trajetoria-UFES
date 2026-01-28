#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

struct node
{
    void *data;
    node *next;
};

struct forward_list
{
    node *head;
    int size;
};

void *retorna_node_data(node *n)
{
    return n->data;
}

forward_list *list_construct()
{
    forward_list *fl = (forward_list *)calloc(1, sizeof(forward_list));
    fl->head = NULL;
    fl->size = 0;
    return fl;
}

node *node_construct()
{
    node *n = (node *)calloc(1, sizeof(node));
    return n;
}

node *node_constructt(void *data, node *next)
{
    node *n = (node *)calloc(1, sizeof(node));
    n->data = data;
    n->next = next;
    return n;
}

void node_free_NULL(node *n)
{
}

void node_free_data_externa(node *n)
{
    free(n->data);
}

void list_push_front(forward_list *fl, node *node)
{

    if (fl->head == NULL)
    {
        fl->head = node;
        fl->size++;
    }
    else
    {
        node->next = fl->head;
        fl->head = node;
        fl->size++;
    }
}

void list_printf(forward_list *fl, node_print node_print_type)
{
    if (fl->head != NULL)
    {
        node *node_aux = fl->head;
        while (node_aux != NULL)
        {
            node_print_type(node_aux);
            node_aux = node_aux->next;
        }
    }
}

node *list_get(forward_list *fl, node_comp node_fctcomp, void *item)
{
    if (fl != NULL)
    {
        node *node_aux = fl->head;

        while (node_aux != NULL)
        {
            if (node_fctcomp(node_aux, item) == 0)
            {
                return node_aux;
            }
            else
            {
                node_aux = node_aux->next;
            }
        }
    }
    // printf("NÃO ACHOU\n");
    return NULL;
}

void list_destroy(forward_list *fl, node_destroy node_destroy)
{
    node *node_del = fl->head;
    node *node_aux = fl->head;

    while (node_del != NULL)
    {
        node_aux = node_aux->next;
        node_destroy(node_del);
        free(node_del);
        node_del = node_aux;
    }

    free(fl);
}

forward_list *list_copy(forward_list *fl)
{
    forward_list *copy = list_construct();
    node *node_aux = fl->head;
    while (node_aux != NULL)
    {
        node *new_node = node_construct();
        new_node->data = node_aux->data;
        list_push_front(copy, new_node);
        node_aux = node_aux->next;
    }
    return copy;
}

// usar cópias da lista geralmente
void forward_list_unique(forward_list *fl, node_comp node_comp, node *node_atual)
{
    node *node_aux = node_atual->next;
    node *node_aux_prev = node_atual;
    while (node_aux != NULL)
    {
        if (node_comp(node_atual, node_aux) == 1)
        {
            node_aux_prev->next = node_aux->next;
            free(node_aux);
            node_aux = node_aux->next;
        }
        else
        {
            node_aux_prev = node_aux;
            node_aux = node_aux->next;
        }
    }
}

void troca_nodes_data(node *n1, node *n2)
{

    void *node_aux = NULL;
    node_aux = n1->data;
    n1->data = n2->data;
    n2->data = node_aux;
}

void ordena_lista(forward_list *fl, node_comp node_fctcomp)
{
    node *node_atual = fl->head;

    for (int i = 0; i < (fl->size - 1); i++)
    {
        node *node_next = node_atual->next;

        for (int j = 0; j < (fl->size - 1 - i); j++)
        {
            if (node_atual != NULL && node_next != NULL)
            {
                if (node_fctcomp(node_atual, node_next) == 1)
                {
                    troca_nodes_data(node_atual, node_next);
                }
            }
            node_next = node_next->next;
        }

        node_atual = node_atual->next;
    }
}

void list_remove(forward_list *l, void *item, node_comp node_fctcomp)
{
    node *node_aux = l->head;
    node *node_prev = NULL;

    while (node_aux != NULL)
    {
        if ((node_fctcomp(node_aux, item) == 1) && node_prev == NULL)
        {
            l->head = node_aux->next;
            node *n = node_aux->next;
            node_free_NULL(node_aux);
            node_aux = n;
        }
        else if ((node_fctcomp(node_aux, item) == 1))
        {
            node_prev->next = node_aux->next;
            node *n = node_aux->next;
            node_free_NULL(node_aux);
            node_aux = n;
        }
        else
        {
            node_prev = node_aux;
            node_aux = node_aux->next;
        }
    }
}
