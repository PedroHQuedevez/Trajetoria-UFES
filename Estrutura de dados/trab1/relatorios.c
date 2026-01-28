#include "relatorios.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printf_realatorio_1(node *n)
{
    matricula *m = (matricula *)n->data;

    printf("%s\n", m->estudante->nome);
}

void matricula_fct_comp(node *n, void *item)
{
}

void relatorio_1(forward_list *estudantes, forward_list *disciplinas)
{
    char codigo_disciplina[100];
    printf("digite o código da disciplina:\n");
    scanf("\n%s", codigo_disciplina);

    node *n = list_get(disciplinas, node_fctcmp_discplina, codigo_disciplina);
    disciplina *disciplina_procurada = (disciplina *)n->data;

    forward_list *lista_alunos = list_copy(disciplina_procurada->matriculas);
    // realmente criar uma lista nova aqui
    matricula_unique(lista_alunos);

    list_printf(lista_alunos, printf_realatorio_1);
    list_destroy(lista_alunos, node_free_NULL);
}

//-----------------------------------------------------------------------------------------------------------

void printf_realatorio_2(node *n)
{
    disciplina *d = (disciplina *)n->data;
    printf("%s ", d->nome);
}

void relatorio_2(forward_list *disciplinas)
{
    char codigo_disciplina[100];
    printf("digite o código da disciplina:\n");
    scanf("\n%s", codigo_disciplina);
    node *node_atual;
    node_atual = (node *)list_get(disciplinas, node_fctcmp_discplina, codigo_disciplina);
    disciplina *d = (disciplina *)node_atual->data;
    list_printf(d->pre_requisitos, printf_realatorio_2);
    printf("\n");
}

//-----------------------------------------------------------------------------------------------------------

forward_list *pre_requisitos_totais(forward_list *pre_requisitos, forward_list *fl_print)
{
    node *pre_req = pre_requisitos->head;

    // if (pre_req->data == NULL)
    // {
    //     printf("não tem pre requisitos");
    // }
    while (pre_req != NULL)
    {
        disciplina *pre_data = (disciplina *)pre_req->data;
        node *node_add = node_construct();
        node_add->data = pre_data;
        list_push_front(fl_print, node_add);
        // if (pre_data->pre_requisitos->head == NULL)
        // {
        //     printf("pre_data->pre_requisitos->head deu null\n");
        // }
        forward_list *pre_req_do_pre_req_requezado = pre_data->pre_requisitos;
        if (pre_req_do_pre_req_requezado->head != NULL)
        {
            pre_requisitos_totais(pre_req_do_pre_req_requezado, fl_print);
        }
        pre_req = pre_req->next;
    }
    return fl_print;
}

void printf_realatorio_3(forward_list *fl)
{

    forward_list *fl_print = list_construct();
    fl_print = pre_requisitos_totais(fl, fl_print);
    list_printf(fl_print, printf_realatorio_2); // talvez esteja invertido;
    list_destroy(fl_print, node_free_NULL);
}

void relatorio_3(forward_list *disciplinas)
{
    char codigo_disciplina[100];
    printf("digite o código da disciplina:\n");
    scanf("\n%s", codigo_disciplina);
    node *node_atual;
    node_atual = (node *)list_get(disciplinas, node_fctcmp_discplina, codigo_disciplina);
    disciplina *atual = (disciplina *)node_atual->data;
    printf_realatorio_3(atual->pre_requisitos);
}

//-----------------------------------------------------------------------------------------------------------

int get_relatorio_4(node *n, void *item)
{
    matricula *m = (matricula *)n->data;
    int *n_matricula = (int *)item;
    // printf("%i %i\n", m->estudante->matricula, *n_matricula);
    if (m->estudante->matricula == *n_matricula)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printf_relatorio_4(node *n)
{
    disciplina *d = (disciplina *)n->data;
    printf("%s ", d->nome);
}

void relatorio_4(forward_list *disciplinas)
{
    int matricula_aluno;
    printf("digite o número da matricula:\n");
    scanf("\n%d", &matricula_aluno);

    forward_list *fl_disciplinas_matriculado = list_construct();

    node *iterador_node = disciplinas->head;

    while (iterador_node != NULL)
    {
        disciplina *disciplina_aux = (disciplina *)iterador_node->data;
        node *node_aux = list_get(disciplina_aux->matriculas, get_relatorio_4, &matricula_aluno);

        if (node_aux != NULL)
        {
            node *node_add = node_construct(); // para não mudar o ponteiro do node em lista diferente;
            node_add->data = disciplina_aux;
            list_push_front(fl_disciplinas_matriculado, node_add); // será o node da disciplina aqui caso o aluno procurado esteja matriculado nela;
        }
        iterador_node = iterador_node->next;
    }

    list_printf(fl_disciplinas_matriculado, printf_relatorio_4);
    list_destroy(fl_disciplinas_matriculado, node_free_NULL);
}

//-----------------------------------------------------------------------------------------------------------

typedef struct
{
    disciplina *disciplina;
    int reprovacoes;
} data_relatorio_5;

int fct_comp_ordena_relatorio_5(node *n1, void *item)
{
    node *n2 = (node *)item;
    data_relatorio_5 *d1 = (data_relatorio_5 *)n1->data;
    data_relatorio_5 *d2 = (data_relatorio_5 *)n2->data;

    if (d1 != NULL && d2 != NULL)
    {
        if (d1->reprovacoes < d2->reprovacoes)
        {
            return 1;
        }
        else if (d1->reprovacoes > d2->reprovacoes)
        {

            return 0;
        }
    }
    return -1;
}

void printf_relatorio_5(node *n) // digitar "entrada.txt" quando executar o main e testar com uma dupla de printf por vez; esse erro também ocorre em outros relatórios quando printo algo das *disciplinas geralmente;
{
    data_relatorio_5 *d = (data_relatorio_5 *)n->data;

    printf("%s %s %d\n", d->disciplina->professor, d->disciplina->nome, d->reprovacoes);
}

void relatorio_5(forward_list *disciplinas)
{
    forward_list *lista_reprovacoes = list_construct();

    node *iterador_disciplinas = disciplinas->head;

    while (iterador_disciplinas != NULL)
    {
        int reprovacoes = 0;
        disciplina *disciplina_aux = (disciplina *)iterador_disciplinas->data;
        forward_list *matriculas_aux = disciplina_aux->matriculas;
        node *iterator_matriculas = matriculas_aux->head;

        while (iterator_matriculas != NULL)
        {
            matricula *matricula_aux = (matricula *)iterator_matriculas->data;
            if (matricula_aux->aprovacao == 0 || matricula_aux->nota_final < 5 || matricula_aux->presenca < 0.75)
            {
                reprovacoes++;
            }
            iterator_matriculas = iterator_matriculas->next;
        }

        node *node_add = node_construct();
        data_relatorio_5 *data = (data_relatorio_5 *)malloc(sizeof(data_relatorio_5)); // da pra fazer sem malloc?
        data->disciplina = disciplina_aux;
        data->reprovacoes = reprovacoes;
        node_add->data = data;
        list_push_front(lista_reprovacoes, node_add);
        iterador_disciplinas = iterador_disciplinas->next;
    }

    ordena_lista(lista_reprovacoes, fct_comp_ordena_relatorio_5);
    list_printf(lista_reprovacoes, printf_relatorio_5);
    list_destroy(lista_reprovacoes, node_free_data_externa);
}

//-----------------------------------------------------------------------------------------------------------

int fct_comp_ordena_relatorio_6(node *n1, void *item)
{
    node *n2 = (node *)item;
    disciplina *d1 = (disciplina *)n1->data;
    disciplina *d2 = (disciplina *)n2->data;

    if (d1 != NULL && d2 != NULL)
    {
        if (strcmp(d1->nome, d2->nome) > 0)
        {
            return 1;
        }
        else if (strcmp(d1->nome, d2->nome) < 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

void relatorio_6(forward_list *disciplinas)
{
    int matricula_aluno;
    printf("digite o número da matricula:\n");
    scanf("\n%d", &matricula_aluno);

    forward_list *fl_disciplinas_aprovado = list_construct();

    node *iterador_node = disciplinas->head;

    while (iterador_node != NULL)
    {
        disciplina *disciplina_aux = (disciplina *)iterador_node->data;
        node *node_aux = list_get(disciplina_aux->matriculas, get_relatorio_4, &matricula_aluno); // quero o node da matricula do estudante como retorno;
        if (node_aux != NULL)
        {
            // node_matricula_printf(node_aux);
            matricula *mat_aux = (matricula *)node_aux->data;

            if (((mat_aux->aprovacao == 1) || ((mat_aux->nota_final >= 5) && (mat_aux->presenca >= 0.75))))
            {
                node *node_add = node_construct(); // para não mudar o ponteiro do node em lista diferente;
                node_add->data = disciplina_aux;
                list_push_front(fl_disciplinas_aprovado, node_add); // será o node da disciplina aqui caso o aluno procurado esteja matriculado nela;
            }
        }

        iterador_node = iterador_node->next;
    }

    ordena_lista(fl_disciplinas_aprovado, fct_comp_ordena_relatorio_6);
    list_printf(fl_disciplinas_aprovado, printf_relatorio_4);
    list_destroy(fl_disciplinas_aprovado, node_free_NULL);
}

//-----------------------------------------------------------------------------------------------------------

void relatorio_7(forward_list *disciplinas)
{

    // forward_list *inconsistencias = list_construct(); demorei perceber que ficava mais fácil sem criar uma lista :) fui no embalo;

    node *iterador_node_disc = disciplinas->head;

    while (iterador_node_disc != NULL)
    {
        disciplina *disciplina_aux = iterador_node_disc->data;
        node *iterador_node_mat = disciplina_aux->matriculas->head;
        while (iterador_node_mat != NULL)
        {
            matricula *mat_aux = (matricula *)iterador_node_mat->data;
            if (((mat_aux->aprovacao == 0) && ((mat_aux->nota_final >= 5) && (mat_aux->presenca >= 0.75))))
            {
                node *node_add = node_construct();
                node_add->data = mat_aux;
                printf("%s;%i;", disciplina_aux->codigo, mat_aux->estudante->matricula);
                node_matricula_printf(node_add);
                free(node_add);
                // list_push_front(inconsistencias, node_add);
            }
            else if (((mat_aux->aprovacao == 1) && ((mat_aux->nota_final < 5) || (mat_aux->presenca < 0.75))))
            {
                node *node_add = node_construct();
                node_add->data = mat_aux;
                printf("%s;%i;", disciplina_aux->codigo, mat_aux->estudante->matricula);
                node_matricula_printf(node_add);
                free(node_add);
                // list_push_front(inconsistencias, node_add);
            }
            iterador_node_mat = iterador_node_mat->next;
        }
        iterador_node_disc = iterador_node_disc->next;
    }

    // list_printf(inconsistencias, node_matricula_printf);
    // list_destroy(inconsistencias, node_free_NULL);
}

//-----------------------------------------------------------------------------------------------------------

int contador_relatorio_8(node *n, int cont)
{
    if (n == NULL)
    {
        cont++;
    }
    return cont;
}

int contador_relatorio_9(node *n, int cont)
{
    if (n != NULL)
    {
        matricula *matricula_analisada = (matricula *)n->data;
        if (matricula_analisada->aprovacao == 0 || matricula_analisada->nota_final < 5 || matricula_analisada->presenca < 0.75)
        {
            cont++;
        }
    }
    return cont;
}

void relatorio_8_9(forward_list *disciplinas, fct_cont_relatorio_8_9 fct)
{
    node *iterador_disciplina = disciplinas->head;
    int numero_ocorrencias = 0;

    while (iterador_disciplina != NULL)
    { // prepara a disciplina e a lista de pré requisitos para serem analisados;
        disciplina *disciplina_aux = (disciplina *)iterador_disciplina->data;
        forward_list *pre_req_total_list = list_construct();
        pre_req_total_list = pre_requisitos_totais(disciplina_aux->pre_requisitos, pre_req_total_list);
        node *iterator_matricula = disciplina_aux->matriculas->head;

        while (iterator_matricula != NULL)
        { // vai passar a matricula de cada aluno que está cursou a disciplina para o próximo while;
            matricula *aluno_sendo_procurado = (matricula *)iterator_matricula->data;
            node *iterator_pre_requisito = pre_req_total_list->head;

            while (iterator_pre_requisito != NULL)
            { // está procurando a matricula do aluno dentro da lista de matriculas dentro de cada pré requisito da disciplina_aux;
                disciplina *disciplina_meu_deus_quanto_passo = (disciplina *)iterator_pre_requisito->data;
                forward_list *matriculas_dos_pre_requisitos = disciplina_meu_deus_quanto_passo->matriculas;
                node *node_get = list_get(matriculas_dos_pre_requisitos, node_fctcmp_matricula, &aluno_sendo_procurado->estudante->matricula);
                numero_ocorrencias = fct(node_get, numero_ocorrencias);
                iterator_pre_requisito = iterator_pre_requisito->next;
            }

            iterator_matricula = iterator_matricula->next;
        }

        iterador_disciplina = iterador_disciplina->next;
        list_destroy(pre_req_total_list, node_free_NULL);
    }

    printf("%i\n", numero_ocorrencias);
}

// void relatorio_8(forward_list *disciplinas)
// {
//     node *iterador_disciplina = disciplinas->head;
//     int numero_ocorrencias = 0;

//     while (iterador_disciplina != NULL)
//     { // prepara a disciplina e a lista de pré requisitos para serem analisados;
//         disciplina *disciplina_aux = (disciplina *)iterador_disciplina->data;
//         forward_list *pre_req_total_list = list_construct();
//         pre_req_total_list = pre_requisitos_totais(disciplina_aux->pre_requisitos, pre_req_total_list);
//         node *iterator_matricula = disciplina_aux->matriculas->head;

//         while (iterator_matricula != NULL)
//         { // vai passar a matricula de cada aluno que está cursou a disciplina para o próximo while;
//             matricula *aluno_sendo_procurado = (matricula *)iterator_matricula->data;
//             node *iterator_pre_requisito = pre_req_total_list->head;

//             while (iterator_pre_requisito != NULL)
//             { // está procurando a matricula do aluno dentro da lista de matriculas dentro de cada pré requisito da disciplina_aux;
//                 disciplina *disciplina_meu_deus_quanto_passo = (disciplina *)iterator_pre_requisito->data;
//                 forward_list *matriculas_dos_pre_requisitos = disciplina_meu_deus_quanto_passo->matriculas;
//                 node *node_get = list_get(matriculas_dos_pre_requisitos, node_fctcmp_matricula, &aluno_sendo_procurado->estudante->matricula);
//                 if (node_get == NULL)
//                 {
//                     numero_ocorrencias++;
//                     // printf("%i %s\n", aluno_sendo_procurado->estudante->matricula, disciplina_meu_deus_quanto_passo->nome);
//                 }
//                 iterator_pre_requisito = iterator_pre_requisito->next;
//             }

//             iterator_matricula = iterator_matricula->next;
//         }

//         iterador_disciplina = iterador_disciplina->next;
//         list_destroy(pre_req_total_list, node_free_NULL);
//     }

//     printf("%i\n", numero_ocorrencias);
// }

// //-----------------------------------------------------------------------------------------------------------

// //-----------------------------------------------------------------------------------------------------------

// void relatorio_9(forward_list *disciplinas)
// {
//     node *iterador_disciplina = disciplinas->head;
//     int numero_ocorrencias = 0;

//     while (iterador_disciplina != NULL)
//     { // prepara a disciplina e a lista de pré requisitos para serem analisados;
//         disciplina *disciplina_aux = (disciplina *)iterador_disciplina->data;
//         forward_list *pre_req_total_list = list_construct();
//         pre_req_total_list = pre_requisitos_totais(disciplina_aux->pre_requisitos, pre_req_total_list);
//         node *iterator_matricula = disciplina_aux->matriculas->head;

//         while (iterator_matricula != NULL)
//         { // vai passar a matricula de cada aluno que está cursou a disciplina para o próximo while;
//             matricula *aluno_sendo_procurado = (matricula *)iterator_matricula->data;
//             node *iterator_pre_requisito = pre_req_total_list->head;

//             while (iterator_pre_requisito != NULL)
//             { // está procurando a matricula do aluno dentro da lista de matriculas dentro de cada pré requisito da disciplina_aux;
//                 disciplina *disciplina_meu_deus_quanto_passo = (disciplina *)iterator_pre_requisito->data;
//                 forward_list *matriculas_dos_pre_requisitos = disciplina_meu_deus_quanto_passo->matriculas;
//                 node *node_get = list_get(matriculas_dos_pre_requisitos, node_fctcmp_matricula, &aluno_sendo_procurado->estudante->matricula);
//                 if (node_get != NULL)
//                 {
//                     matricula *matricula_analisada = (matricula *)node_get->data;
//                     if (matricula_analisada->aprovacao == 0 || matricula_analisada->nota_final < 5 || matricula_analisada->presenca < 0.75)
//                     {

//                         numero_ocorrencias++;
//                         // printf("%i %s\n", matricula_analisada->estudante->matricula, disciplina_meu_deus_quanto_passo->nome);
//                     }
//                 }
//                 iterator_pre_requisito = iterator_pre_requisito->next;
//             }

//             iterator_matricula = iterator_matricula->next;
//         }

//         iterador_disciplina = iterador_disciplina->next;
//         list_destroy(pre_req_total_list, node_free_NULL);
//     }

//     printf("%i\n", numero_ocorrencias);
// }

//-----------------------------------------------------------------------------------------------------------

int fct_comp_ordena_relatorio_10(node *n1, void *item)
{
    node *n2 = (node *)item;
    estudante *e1 = (estudante *)n1->data;
    estudante *e2 = (estudante *)n2->data;

    if (e1 != NULL && e2 != NULL)
    {
        return strcmp(e1->nome, e2->nome);
    }
    return -1;
}

void relatorio_10(forward_list *estudantes, forward_list *disciplinas)
{
    ordena_lista(estudantes, fct_comp_ordena_relatorio_10);
    node *estudante_iterator = estudantes->head;

    while (estudante_iterator != NULL)
    {
        estudante *estudante_aux = (estudante *)estudante_iterator->data;
        int n_disc_aprovado = 0;
        int n_disc_cursadas = 0;
        float nota_media = 0;

        node *disciplina_iterator = disciplinas->head;
        while (disciplina_iterator != NULL)
        {
            disciplina *disciplina_aux = (disciplina *)disciplina_iterator->data;
            node *matricula_iterator = disciplina_aux->matriculas->head;
            while (matricula_iterator != NULL)
            {
                matricula *matricula_aux = (matricula *)matricula_iterator->data;
                if (strcmp(matricula_aux->estudante->nome, estudante_aux->nome) == 0)
                {
                    n_disc_cursadas++;
                    nota_media = nota_media + matricula_aux->nota_final;
                    if (matricula_aux->aprovacao == 1)
                    {
                        n_disc_aprovado++;
                    }
                }
                matricula_iterator = matricula_iterator->next;
            }
            disciplina_iterator = disciplina_iterator->next;
        }

        printf("%s %d %d %d %.2f\n", estudante_aux->nome, estudante_aux->matricula, n_disc_cursadas, n_disc_aprovado, nota_media / n_disc_cursadas);
        estudante_iterator = estudante_iterator->next;
    }
}

//-----------------------------------------------------------------------------------------------------------

typedef struct
{
    disciplina *disciplina;
    int num_matriculas;
    int num_aprovacoes;
    float nota_media;
    float percentual_aprovacao;
} data_relatorio_11;

int fct_comp_ordena_relatorio_11(node *n1, void *item)
{

    node *n2 = (node *)item;
    data_relatorio_11 *d1 = (data_relatorio_11 *)n1->data;
    data_relatorio_11 *d2 = (data_relatorio_11 *)n2->data;

    if (d1 != NULL && d2 != NULL)
    {
        if (d1->percentual_aprovacao < d2->percentual_aprovacao)
        {
            return 1;
        }
        else if (d1->percentual_aprovacao > d2->percentual_aprovacao)
        {

            return 0;
        }
    }
    return -1;
}

void printf_relatorio_11(node *n)
{
    if (n != NULL && n->data != NULL)
    {
        data_relatorio_11 *d = (data_relatorio_11 *)n->data;

        printf("%s %s %s %d %.2f\n", d->disciplina->codigo, d->disciplina->nome, d->disciplina->professor, d->num_aprovacoes, d->nota_media);
    }
}

void relatorio_11(forward_list *disciplinas) // organizar antes ou criar cópia e organizar.
{
    node *iterador_disciplina = disciplinas->head;
    forward_list *lista_print = list_construct();

    while (iterador_disciplina != NULL && iterador_disciplina->data != NULL)
    {
        float nota_media = 0;
        int numero_aprovacoes = 0;

        node *node_add = node_construct();
        data_relatorio_11 *data = (data_relatorio_11 *)calloc(1, sizeof(data_relatorio_11));
        disciplina *disciplina_aux = (disciplina *)iterador_disciplina->data;
        data->disciplina = disciplina_aux;
        data->num_aprovacoes = 0;
        // printf("%s %s %s ", disciplina_aux->codigo, disciplina_aux->nome, disciplina_aux->professor);
        node *iterator_matricula = disciplina_aux->matriculas->head;

        while (iterator_matricula != NULL)
        {
            matricula *matricula_aux = (matricula *)iterator_matricula->data;
            if (matricula_aux->aprovacao == 1)
            {
                numero_aprovacoes++;
                // printf("*%d\n", numero_aprovacoes);
            }
            nota_media = nota_media + matricula_aux->nota_final;
            iterator_matricula = iterator_matricula->next;
        }
        if (disciplina_aux->matriculas->size != 0)
        {
            data->nota_media = nota_media / disciplina_aux->matriculas->size;
        }

        data->num_aprovacoes = numero_aprovacoes;
        // printf("**%d\n", data->num_aprovacoes); // bug tbm;
        if (disciplina_aux->matriculas->size != 0)
        {
            data->percentual_aprovacao = numero_aprovacoes / disciplina_aux->matriculas->size;
        }
        node_add->data = data;
        list_push_front(lista_print, node_add);
        // printf("%d %.2f\n", numero_aprovacoes, nota_media / disciplina_aux->matriculas->size);
        // printf("\n");
        iterador_disciplina = iterador_disciplina->next;
    }

    ordena_lista(lista_print, fct_comp_ordena_relatorio_11);
    list_printf(lista_print, printf_relatorio_11);
    list_destroy(lista_print, node_free_data_externa);
}

//-----------------------------------------------------------------------------------------------------------

void relatorio_12(forward_list *disciplinas, forward_list *estudantes)
{
    char codigo_disciplina[100];
    printf("digite o código da disciplina:\n");
    scanf("\n%s", codigo_disciplina);

    node *disc_destroy = list_get(disciplinas, node_fctcmp_discplina, codigo_disciplina);

    node *iterador_disciplina = disciplinas->head;

    while (iterador_disciplina != NULL)
    {
        disciplina *disciplina_aux = (disciplina *)iterador_disciplina->data;

        if (disciplina_aux->pre_requisitos != NULL)
        {
            node *disc_destroy_2 = list_get(disciplina_aux->pre_requisitos, node_fctcmp_discplina, codigo_disciplina);
            list_remove(disciplina_aux->pre_requisitos, codigo_disciplina, node_fctcmp_discplina);
            if (disc_destroy_2 != NULL)
            {
                free(disc_destroy_2);
            }
        }

        iterador_disciplina = iterador_disciplina->next;
    }

    printf("\n");
    list_printf(estudantes, node_estudant_printf);
    printf("\n");

    list_remove(disciplinas, codigo_disciplina, node_fctcmp_discplina);
    list_printf(disciplinas, node_disciplina_printf);
    printf("\n");
    node *iterador_node = disciplinas->head;

    while (iterador_node != NULL)
    {
        disciplina *disciplina_aux = (disciplina *)iterador_node->data;
        // forward_list *pre_list = (forward_list *)disciplina_aux->pre_requisitos;
        node *pre_aux = disciplina_aux->pre_requisitos->head;
        if (pre_aux != NULL)
        {
            disciplina *disc_pre_aux = (disciplina *)pre_aux->data;
            printf("%s;%s\n", disciplina_aux->codigo, disc_pre_aux->codigo);
            pre_aux = pre_aux->next;
        }
        iterador_node = iterador_node->next;
    }

    printf("\n");

    iterador_node = disciplinas->head;

    while (iterador_node != NULL)
    {
        disciplina *disciplina_aux = (disciplina *)iterador_node->data;
        node *iterador_matricula = disciplina_aux->matriculas->head;

        while (iterador_matricula != NULL)
        {
            matricula *matricula_aux = (matricula *)iterador_matricula->data;
            printf("%s;%d;%.2f;%.2f;%d\n", disciplina_aux->codigo, matricula_aux->estudante->matricula, matricula_aux->nota_final, matricula_aux->presenca, matricula_aux->aprovacao);
            iterador_matricula = iterador_matricula->next;
        }

        iterador_node = iterador_node->next;
    }

    node_disciplina_destroy(disc_destroy);
    free(disc_destroy);
}