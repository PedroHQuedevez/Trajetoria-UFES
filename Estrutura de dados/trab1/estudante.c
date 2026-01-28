#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forward_list.h"
#include "estudante.h"
#include <stdio.h>
estudante *estudante_create(FILE *arquivo)
{
    char nome[100];
    char email[100];
    estudante *e = (estudante *)calloc(1, sizeof(estudante));

    fscanf(arquivo, "\r\n%100[^;];%d;%100[^\n]\r\n", nome, &e->matricula, email);

    e->nome = (char *)malloc((sizeof(char) * strlen(nome)) + 1);
    strcpy(e->nome, nome);

    e->email = (char *)malloc(sizeof(char) * strlen(email) + 1);
    strcpy(e->email, email);

    // printf("\n%s;%d;%s\n", e->nome, e->matricula, e->email);

    return e;
}

void node_estudant_printf(node *n)
{
    estudante *e = (estudante *)n->data;
    printf("%s;%d;%s\n", e->nome, e->matricula, e->email);
}

int node_fctcmp_estudante(node *n, void *item)
{
    estudante *e = (estudante *)n->data;
    int *matricula = (int *)item;
    if (e->matricula == *matricula)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void node_estudante_destroy(node *n)
{
    estudante *e = (estudante *)n->data;
    free(e->email);
    free(e->nome);
    free(e);
}