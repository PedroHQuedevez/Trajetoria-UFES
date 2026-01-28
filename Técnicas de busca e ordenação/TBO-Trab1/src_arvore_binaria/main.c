#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aresta.h"
#include "dijkstra.h"
#include "arvore_binaria.h"
#include "vertice.h"
#include "vector.h"

int main(int argc, char *argv[])
{
    clock_t inicio = clock();
    if (argc < 3)
    {
        printf("Error: precisa de um arquivo de entrada e um arquivo de saída.\n");
        exit(0);
    }

    FILE *arquivo_entrada = fopen(argv[1], "r");
    if (arquivo_entrada == NULL)
    {
        printf("Error: file not found.\n");
        exit(0);
    }

    FILE *arquivo_saida = fopen(argv[2], "w");
    if (arquivo_saida == NULL)
    {
        printf("Error: não foi possível criar o arquivo de saída.\n");
        fclose(arquivo_entrada);
        exit(0);
    }

    int origem;
    fscanf(arquivo_entrada, "node_%d\n", &origem);

    // Criando estrutura dinâmica
    ArvoreBinaria *arvore = arvore_binaria_construct();
    Vector *vertices = vector_construct();

    // Variáveis auxiliares
    Vertice *vertice;
    Aresta *aresta;
    int no_origem, no_destino;
    char peso_str[100];
    float peso;
    char caractere;

    // Leitura do arquivo e construção da árvore binária e do vetor de vértices
    while (fscanf(arquivo_entrada, "node_%d", &no_origem) == 1)
    {
        vertice = vertice_construct(no_origem);
        if (no_origem == origem)
        {
            vertice_set_id_pai(vertice, 0);
            vertice_set_distancia_origem(vertice, 0.0);
        }

        arvore_binaria_push(arvore, vertice);
        vector_push_back(vertices, vertice);

        no_destino = 0;
        while (1)
        {
            if (fscanf(arquivo_entrada, "%c", &caractere) != 1) break;
            if (caractere == '\n') break;

            if (no_destino == no_origem) no_destino++;

            fscanf(arquivo_entrada, " %99[^,\n]", peso_str);
            peso = atof(peso_str);

            if (peso > 0)
            {
                aresta = aresta_construct(no_origem, no_destino, peso);
                vertice_add_aresta(vertice, aresta);
            }

            no_destino++;
        }
    }

    fclose(arquivo_entrada);

    dijkstra(arvore, vertices, origem);
    Vector *ordenado = vector_construct();
    for (int i = vector_size(vertices)-1; i >= 0; i--) 
    {
        vector_push_back(ordenado, (Vertice *)vector_get(vertices, i));
    }
    vector_qsort(ordenado, cmp_vertice);
    // Gerando a saída
    Vertice *v;
    int id_pai;
    float distancia;

    for (int i = 0; i < vector_size(vertices); i++)
    {
        v = (Vertice *)vector_get(ordenado, i);
        distancia = vertice_get_distancia_origem(v);

        fprintf(arquivo_saida, "SHORTEST PATH TO node_%d: node_%d ", vertice_get_id(v), vertice_get_id(v));

        do
        {
            id_pai = vertice_get_id_pai(v);
            fprintf(arquivo_saida, "<- node_%d ", id_pai);
            v = (Vertice *)vector_get(vertices, id_pai);
        } 
        while (id_pai != 0);

        fprintf(arquivo_saida, "(Distance: %.2f)\n", distancia);
    }

    arvore_binaria_destroy(arvore);
    for (int i = 0; i < vector_size(vertices); i++) {
        vertice_destroy((Vertice *)vector_get(vertices, i));
    }
    vector_destroy(vertices);
    vector_destroy(ordenado);
    fclose(arquivo_saida);

    clock_t fim = clock();

    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo de execução do algoritmo: %.6f segundos\n", tempo_execucao);
    
    return 0;
}