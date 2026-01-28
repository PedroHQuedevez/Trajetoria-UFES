#ifndef _RELATORIOS_H
#define _RELATORIOS_H

#include "forward_list.h"
#include "matricula.h"
#include "estudante.h"
#include "disciplina.h"

typedef int (*fct_cont_relatorio_8_9)(node *n, int cont);

void printf_realatorio_1(node *n);
void relatorio_1(forward_list *estudantes, forward_list *disciplinas);
void relatorio_2(forward_list *disciplinas);
void relatorio_3(forward_list *disciplinas);
void relatorio_4(forward_list *disciplinas);
void relatorio_5(forward_list *disciplinas);
void relatorio_6(forward_list *disciplinas);
void relatorio_7(forward_list *disciplinas);
void relatorio_8_9(forward_list *disciplinas, fct_cont_relatorio_8_9 fct);
int contador_relatorio_8(node *n, int cont);
int contador_relatorio_9(node *n, int cont);
// void relatorio_8(forward_list *disciplinas);
// void relatorio_9(forward_list *disciplinas);
void relatorio_10(forward_list *estudantes, forward_list *disciplinas);
void relatorio_11(forward_list *disciplinas);
void relatorio_12(forward_list *disciplinas, forward_list *estudantes);
#endif