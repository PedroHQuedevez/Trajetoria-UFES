#ifndef _DISCIPLINA_H
#define _DISCIPLINA_H

#include "forward_list.h"
#include "estudante.h"
#include <stdio.h>
typedef struct disciplina disciplina;

struct disciplina
{
    char *nome;
    char *codigo;
    char *professor;
    forward_list *pre_requisitos;
    forward_list *matriculas;
};

disciplina *disciplina_create(FILE *arquivo);
void node_disciplina_printf(node *n);
void pre_requisito_add(forward_list *disciplinas, FILE *arquivo);
int node_fctcmp_discplina(node *n, void *item);
void node_disciplina_destroy(node *n);

#endif