#ifndef _ESTUDANTE_H
#define _ESTUDANTE_H
#include <stdio.h>
typedef struct estudante estudante;

struct estudante
{
    char *nome;
    int matricula;
    char *email;
};

estudante *estudante_create(FILE *arquivo);
void node_estudant_printf(node *n);
int node_fctcmp_estudante(node *n, void *item);
void node_estudante_destroy(node *n);

#endif