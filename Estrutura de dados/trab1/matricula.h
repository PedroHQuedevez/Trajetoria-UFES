#ifndef _MATRICULA_H
#define _MATRICULA_H

#include "forward_list.h"
#include "estudante.h"
#include <stdio.h>
typedef struct matricula matricula;

struct matricula
{
    estudante *estudante;
    float nota_final;
    float presenca;
    int aprovacao;
};

matricula *matricula_create();
void node_matricula_printf(node *n);
void matricula_create_and_add(forward_list *disciplinas, forward_list *estudantes, FILE *arquivo);
void node_matricula_destroy(node *n);
void matricula_unique(forward_list *matriculas);
int node_fctcmp_matricula(node *n, void *item);

#endif