#include <stdio.h>
#include "forward_list.h"
#include "estudante.h"
#include "disciplina.h"
#include "matricula.h"
#include "relatorios.h"

int main()
{

    char nome_arquivo[1000];

    printf("nome do arquivo:\n");
    scanf("%s", nome_arquivo);

    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
    {
        printf("ERRO AO ABIR O ARQUIVO\n");
    }
    int num_aux;

    forward_list *estudantes = list_construct();
    forward_list *disciplinas = list_construct();

    fscanf(arquivo, "%d\n", &num_aux);

    for (int i = 0; i < num_aux; i++)
    {
        estudante *e = estudante_create(arquivo);
        node *n = node_construct();
        n->data = e;
        list_push_front(estudantes, n);
    }
    // list_printf(estudantes, node_estudant_printf);

    fscanf(arquivo, "%d\n", &num_aux);

    for (int i = 0; i < num_aux; i++)
    {
        disciplina *d = disciplina_create(arquivo);
        node *n = node_construct();
        n->data = d;
        list_push_front(disciplinas, n);
    }
    // list_printf(disciplinas, node_disciplina_printf);

    fscanf(arquivo, "%d\n", &num_aux);
    for (int i = 0; i < num_aux; i++)
    {
        pre_requisito_add(disciplinas, arquivo);
    }

    fscanf(arquivo, "%d\n", &num_aux);
    for (int i = 0; i < num_aux; i++)
    {
        matricula_create_and_add(disciplinas, estudantes, arquivo);
    }
    fclose(arquivo);

    printf("numero do relatorio:\n");
    int relatorio;
    scanf("%d", &relatorio);

    if (relatorio == 1)
    {
        relatorio_1(estudantes, disciplinas);
    }
    else if (relatorio == 2)
    {
        relatorio_2(disciplinas);
    }
    else if (relatorio == 3)
    {
        relatorio_3(disciplinas);
    }
    else if (relatorio == 4)
    {
        relatorio_4(disciplinas);
    }
    else if (relatorio == 5)
    {
        relatorio_5(disciplinas);
    }
    else if (relatorio == 6)
    {
        relatorio_6(disciplinas);
    }
    else if (relatorio == 7)
    {
        relatorio_7(disciplinas);
    }
    else if (relatorio == 8)
    {
        relatorio_8_9(disciplinas, contador_relatorio_8);
    }
    else if (relatorio == 9)
    {
        relatorio_8_9(disciplinas, contador_relatorio_9);
    }
    else if (relatorio == 10)
    {
        relatorio_10(estudantes, disciplinas);
    }
    else if (relatorio == 11)
    {
        relatorio_11(disciplinas);
    }
    else if (relatorio == 12)
    {
        relatorio_12(disciplinas, estudantes);
    }

    list_destroy(estudantes, node_estudante_destroy);
    list_destroy(disciplinas, node_disciplina_destroy);
    return 0;
}