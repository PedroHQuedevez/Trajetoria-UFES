#include <stdlib.h>
#include <stdio.h>
#include "histograma.h"

struct histograma
{
    int *quantidades;
    float tam_bins;
    int numero_bins;
};

void cria_histograma(char *path_entrada, char *path_saida, char *nome_imagem, banco_imagens *banco, int inc_inter, int fim_inter, int qnt_intervalos)
{
    FILE *arq;
    int pixels = retorna_tam_img(banco);
    float array[pixels];
    char caminho_img[250];

    sprintf(caminho_img, "%s/%s.csv", path_entrada, nome_imagem);
    arq = fopen(caminho_img, "r");

    for (int j = 0; j < pixels; j++)
    {
        fscanf(arq, "%f,", &array[j]);
        // fscanf(file,",");
    }
    fclose(arq);

    // float indice_bins;
    histograma *h = (histograma *)malloc(sizeof(histograma));
    int total_contados = 0;
    h->numero_bins = qnt_intervalos;
    if (h->numero_bins != 0)
    {

        int total = 0;
        h->quantidades = (int *)calloc(h->numero_bins, sizeof(int));
        h->tam_bins = (fim_inter - inc_inter) / h->numero_bins;
        int bin_tam_inicial = inc_inter;
        for (int i = 0; i < pixels; i++)
        {
            if (array[i] >= inc_inter && array[i] <= fim_inter)
            {
                for (int j = 0; j < (h->numero_bins); j++)
                {
                    if (array[i] < (bin_tam_inicial + ((j + 1) * h->tam_bins)))
                    {
                        h->quantidades[j]++;
                        array[i] = 1000; // pra não entrar nos outros;
                        total++;
                        total_contados++;
                    }
                }
            }
        }
        // h->quantidades[h->numero_bins - 1] = pixels - total - total_contados;

        char path_arquivo[250];
        sprintf(path_arquivo, "%s/hist_%i_%s.csv", path_saida, h->numero_bins, nome_imagem);
        arq = fopen(path_arquivo, "w");
        for (int i = 0; i < h->numero_bins; i++)
        {
            fprintf(arq, "BIN %i, %i\n", (i + 1), h->quantidades[i]);
        }
        fclose(arq);

        free(h->quantidades);
        free(h);
    }
}