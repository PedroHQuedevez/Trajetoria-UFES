#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "centroides.h"
#include "grupo.h"
#include "histograma.h"
#include "reconstrucao.h"

void print_menu()
{
    printf("\n######################### MENU INICIAL ###########################\n");
    printf("Escolha uma opcao:\n");
    printf("- Executar algoritmo de agrupamento (A ou a)\n");
    printf("- Determinar o grupo de uma imagem (G ou g)\n");
    printf("- Obter o histograma de uma imagem (H ou h)\n");
    printf("- Reconstruir uma imagem (R ou r)\n");
    printf("- Finalizar programa (F ou f)\n");
    printf("###############################################################\n");
}

void menu(char *path_entrada, char *path_saida)
{
    char comando;

    banco_imagens *banco = criar_banco_imagens(path_entrada);
    banco = ler_banco(banco, path_entrada);
    grupo_centroides *grupo;
    int aux_existe_centroid = 0;

    while (1)
    {
        print_menu();
        comando = 'o';
        scanf("\n%c", &comando);
        if (comando == 'o')
        {
            break;
        }
        if (comando == 'A' || comando == 'a')
        {

            if (aux_existe_centroid == 1)
            {
                centroid_group_clear(grupo);
            }
            else
            {
                grupo = grupo_construct();
            }
            aux_existe_centroid = 1;
            grupo = le_centroides(path_entrada, banco, grupo);
            cria_arquivo_centroides(grupo, banco, path_saida);
            scanf("\n%c", &comando); // pegar o m;
        }

        if (comando == 'G' || comando == 'g')
        {

            char nome_imagem[50];
            scanf("\n%s", nome_imagem);
            while (strcmp(nome_imagem, "m") != 0 && strcmp(nome_imagem, "M") != 0)
            {
                cria_arquivo_grupo_imagem(path_entrada, path_saida, nome_imagem, grupo, banco);
                scanf("\n%s", nome_imagem);
            }
        }

        if (comando == 'H' || comando == 'h')
        {
            char nome_imagem[50];
            int inc_inter, fim_inter, n_inter;
            scanf("\n%s", nome_imagem);
            scanf("\n%i", &n_inter);
            scanf("\n%i %i", &inc_inter, &fim_inter);
            while (strcmp(nome_imagem, "m") != 0 && strcmp(nome_imagem, "M") != 0)
            {

                cria_histograma(path_entrada, path_saida, nome_imagem, banco, inc_inter, fim_inter, n_inter);

                scanf("\n%s", nome_imagem);
            }
        }

        if (comando == 'R' || comando == 'r')
        {
            char nome_imagem[50];
            scanf("\n%s", nome_imagem);

            while (strcmp(nome_imagem, "m") != 0 && strcmp(nome_imagem, "M") != 0)
            {
                int dimensao1, dimensao2;
                scanf("\n%i x %i", &dimensao1, &dimensao2);
                gera_arquivo_reconstrucao(path_entrada, path_saida, nome_imagem, dimensao1, dimensao2, banco);

                scanf("\n%s", nome_imagem);
            }
        }

        if (comando == 'F' || comando == 'f')
        {
            if (aux_existe_centroid == 1)
            {
                centroid_group_destroy(grupo);
            }
            break;
        }
    }

    destroy_banco(banco);
}