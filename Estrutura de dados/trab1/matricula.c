#include "matricula.h"
#include "estudante.h"
#include "disciplina.h"
#include "forward_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
void node_matricula_printf(node *n)
{
    matricula *m = (matricula *)n->data;
    printf("%.2f;%.2f;%i\n", m->nota_final, m->presenca, m->aprovacao);
}

void matricula_create_and_add(forward_list *disciplinas, forward_list *estudantes, FILE *arquivo)
{

    matricula *m = (matricula *)calloc(1, sizeof(matricula));
    char disciplina_atual[100];
    int n_matricula;
    fscanf(arquivo, "\r\n%100[^;];%d;%f;%f;%d\r\n", disciplina_atual, &n_matricula, &m->nota_final, &m->presenca, &m->aprovacao);
    // printf(" %i,%.2f,%.2f\n", m->aprovacao, m->nota_final, m->presenca);

    node *node_disc, *node_estudante;
    node_disc = (node *)list_get(disciplinas, node_fctcmp_discplina, disciplina_atual);
    node_estudante = (node *)list_get(estudantes, node_fctcmp_estudante, &n_matricula);

    disciplina *d;
    estudante *e;
    d = (disciplina *)node_disc->data;

    e = (estudante *)node_estudante->data;

    m->estudante = e;

    node *node_matricula = node_construct();
    node_matricula->data = m;
    node_matricula->next = NULL;

    // node_disciplina_printf(node_disc);
    // node_estudant_printf(node_estudante);
    // node_matricula_printf(node_matricula);
    // printf("\n");

    list_push_front(d->matriculas, node_matricula);
}

void node_matricula_destroy(node *n)
{
    matricula *m = (matricula *)n->data;
    free(m);
}

void matricula_unique(forward_list *matriculas)
{
    node *node_comp = matriculas->head;

    while (node_comp != NULL)
    {
        node *node_prev = node_comp;
        node *node_next = node_comp->next;

        while (node_next != NULL)
        {
            matricula *matricula_comp = (matricula *)node_comp->data;
            matricula *matricula_next = (matricula *)node_next->data;

            if (matricula_comp->estudante->matricula == matricula_next->estudante->matricula)
            {
                node_prev->next = node_next->next;
                node *node_del = node_next;
                node_next = node_next->next;
                free(node_del);
            }
            else
            {
                node_prev = node_next;
                node_next = node_next->next;
            }
        }
        node_comp = node_comp->next;
    }
}

int node_fctcmp_matricula(node *n, void *item)
{
    matricula *m = (matricula *)n->data;
    int *matricula = (int *)item;
    if (m->estudante->matricula == *matricula)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}