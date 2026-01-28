#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forward_list.h"
#include "disciplina.h"
#include "matricula.h"
#include <stdio.h>
disciplina *disciplina_create(FILE *arquivo)
{
    char nome[100];
    char codigo[100];
    char professor[100];

    disciplina *d = (disciplina *)calloc(1, sizeof(disciplina));

    fscanf(arquivo, "\r\n%100[^;];%100[^;];%100[^\n]\r\n", nome, codigo, professor);

    d->nome = (char *)malloc((sizeof(char) * strlen(nome)) + 1);
    strcpy(d->nome, nome);

    d->codigo = (char *)malloc(sizeof(char) * strlen(codigo) + 1);
    strcpy(d->codigo, codigo);

    d->professor = (char *)malloc(sizeof(char) * strlen(professor) + 1);
    strcpy(d->professor, professor);

    d->pre_requisitos = list_construct();
    d->matriculas = list_construct();

    // printf("\n%s;%s;%s\n", d->nome, d->codigo, d->professor);

    return d;
}

void node_disciplina_printf(node *n)
{
    disciplina *d = (disciplina *)n->data;
    printf("%s;%s;%s\n", d->nome, d->codigo, d->professor);
}

int node_fctcmp_discplina(node *n, void *item)
{
    disciplina *d = (disciplina *)n->data;
    char *codigo = (char *)item;
    if (strcmp(d->codigo, codigo) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void pre_requisito_add(forward_list *disciplinas, FILE *arquivo)
{
    char codigo_disc[100], codigo_pre[100];
    fscanf(arquivo, "\r\n%100[^;];%s\r\n", codigo_disc, codigo_pre);
    // printf("\n%s %s\n", codigo_disc, codigo_pre);
    node *node_atual, *node_pre;
    node_atual = (node *)list_get(disciplinas, node_fctcmp_discplina, codigo_disc);
    node_pre = (node *)list_get(disciplinas, node_fctcmp_discplina, codigo_pre);

    disciplina *d_atual, *d_pre;

    assert(node_atual != NULL && node_pre != NULL);

    d_atual = (disciplina *)node_atual->data;
    d_pre = (disciplina *)node_pre->data;

    assert(d_atual != NULL && d_pre != NULL);

    // printf("%s\n", d_atual->nome);
    // printf("%s\n", d_pre->nome);
    node *new_node = node_construct();
    new_node->data = d_pre;
    list_push_front(d_atual->pre_requisitos, new_node);
}

void node_disciplina_destroy(node *n)
{
    disciplina *d = (disciplina *)n->data;
    free(d->nome);
    free(d->codigo);
    free(d->professor);
    list_destroy(d->pre_requisitos, node_free_NULL);
    list_destroy(d->matriculas, node_matricula_destroy);
    free(d);
}