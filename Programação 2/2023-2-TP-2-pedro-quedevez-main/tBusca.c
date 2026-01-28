#ifndef _TBUSCA_H_
#define _TBUSCA_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tBusca.h"

struct Busca
{
    int tamanho;
    int numero;
    char nome[101];
    char cpf[15];
};

tBusca *CriaBusca(tListaPacientes *lista, char *nome, char *path)
{
    tBusca *busca = (tBusca *)calloc(1, sizeof(tBusca));
    int count = 0;
    for (int i = 0; i < RetornaSizeListaPacientes(lista); i++)
    {
        if (ComparaNomeBusca(lista, nome, i) == 1)
        {
            count++;
            tPaciente *paciente = RetornaPacienteidx(lista, i);
            busca = (tBusca *)realloc(busca, sizeof(tBusca) * count);
            busca[busca->tamanho].numero = count;
            strcpy(busca[busca->tamanho].nome, RetornaNomePaciente(paciente));
            strcpy(busca[busca->tamanho].cpf, RetornaCpfPaciente(paciente));
            busca->tamanho++;
        }
    }
    return busca;
}

// void verificaBuscaVazia(tBusca *busca)
// {
//     if (strcmp(busca->nome, NULL) == 0)
//     {
//         return 1;
//     }
//     return 0;
// }

void DesalocaBusca(void *dado)
{
    if (dado != NULL)
    {
        free(dado);
    }
}

void ImprimeNaTelaBusca(void *dado)
{
    tBusca *busca = (tBusca *)dado;

    for (int i = 0; i < busca->tamanho; i++)
    {
        printf("%i - %s (%s)\n", busca[i].numero, busca[i].nome, busca[i].cpf);
    }
}

void ImprimeEmArquivoBusca(void *dado, char *path)
{
    tBusca *busca = (tBusca *)dado;

    char arquivo[1001];
    sprintf(arquivo, "%s/lista_busca.txt", path);
    FILE *file = fopen(arquivo, "r");

    if (file == NULL)
    {
        file = fopen(arquivo, "w");
        for (int i = 0; i < busca->tamanho; i++)
        {
            fprintf(file, "%i - %s (%s)\n", busca[i].numero, busca[i].nome, busca[i].cpf);
        }
        fprintf(file, "\n");
    }
    else
    {
        fclose(file);
        file = fopen(arquivo, "a");
        for (int i = 0; i < busca->tamanho; i++)
        {
            fprintf(file, "%i - %s (%s)\n", busca[i].numero, busca[i].nome, busca[i].cpf);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

#endif