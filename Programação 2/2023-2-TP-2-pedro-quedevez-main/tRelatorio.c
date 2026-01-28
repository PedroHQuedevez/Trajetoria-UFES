#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tRelatorio.h"

struct Relatorio
{
    int numeroTotalAtendidos;
    int idadeMedia;
    int fem;
    int masc;
    int out;
    int tamanhoMedioLesoes;
    int numeroTotalLesoes;
    int numeroTotalCirurgias;
    int numeroTotalCrioterapia;
};

tRelatorio *CriaRelatorio(int numeroTotalAtendidos, int idadeMedia, int fem, int masc,
                          int out, int tamanhoMedioLesoes, int numeroTotalLesoes,
                          int numeroTotalCirurgias, int numeroTotalCrioterapia)
{
    tRelatorio *r = (tRelatorio *)calloc(1, sizeof(tRelatorio));

    r->numeroTotalAtendidos = numeroTotalAtendidos;
    r->idadeMedia = idadeMedia;
    r->fem = fem;
    r->masc = masc;
    r->out = out;
    r->tamanhoMedioLesoes = tamanhoMedioLesoes;
    r->numeroTotalLesoes = numeroTotalLesoes;
    r->numeroTotalCirurgias = numeroTotalCirurgias;
    r->numeroTotalCrioterapia = numeroTotalCrioterapia;

    return r;
}

void DesalocaRelatorio(void *dado)
{
    if (dado != NULL)
    {
        free(dado);
    }
}

void ImprimeNaTelaRelatorio(void *dado)
{
    tRelatorio *r = (tRelatorio *)dado;

    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %i\n", r->numeroTotalAtendidos);
    printf("IDADE MEDIA: %i\n", r->idadeMedia);
    printf("DISTRIBUICAO POR GENERO:\n");
    printf("- FEMININO: %i\n", r->fem);
    printf("- MASCULINO: %i\n", r->masc);
    printf("- OUTROS: %i\n", r->out);
    printf("TAMANHO MEDIO DAS LESOES: %i\n", r->tamanhoMedioLesoes);
    printf("NUMERO TOTAL DE LESOES: %i\n", r->numeroTotalLesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %i\n", r->numeroTotalCirurgias);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %i\n", r->numeroTotalCrioterapia);
}

void ImprimeEmArquivoRelatorio(void *dado, char *path)
{
    tRelatorio *r = (tRelatorio *)dado;

    char arquivo[1001];
    sprintf(arquivo, "%s/relatorio_geral.txt", path);
    FILE *file = fopen(arquivo, "r");

    if (file == NULL)
    {
        file = fopen(arquivo, "w");
        fprintf(file, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %i\n", r->numeroTotalAtendidos);
        fprintf(file, "IDADE MEDIA: %i\n", r->idadeMedia);
        fprintf(file, "DISTRIBUICAO POR GENERO:\n");
        fprintf(file, "- FEMININO: %i\n", r->fem);
        fprintf(file, "- MASCULINO: %i\n", r->masc);
        fprintf(file, "- OUTROS: %i\n", r->out);
        fprintf(file, "TAMANHO MEDIO DAS LESOES: %i\n", r->tamanhoMedioLesoes);
        fprintf(file, "NUMERO TOTAL DE LESOES: %i\n", r->numeroTotalLesoes);
        fprintf(file, "NUMERO TOTAL DE CIRURGIAS: %i\n", r->numeroTotalCirurgias);
        fprintf(file, "NUMERO TOTAL DE CRIOTERAPIA: %i\n", r->numeroTotalCrioterapia);
    }
    else
    {
        fclose(file);
        file = fopen(arquivo, "a");
        fprintf(file, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %i\n", r->numeroTotalAtendidos);
        fprintf(file, "IDADE MEDIA: %i\n", r->idadeMedia);
        fprintf(file, "DISTRIBUICAO POR GENERO:\n");
        fprintf(file, "- FEMININO: %i\n", r->fem);
        fprintf(file, "- MASCULINO: %i\n", r->masc);
        fprintf(file, "- OUTROS: %i\n", r->out);
        fprintf(file, "TAMANHO MEDIO DAS LESOES: %i\n", r->tamanhoMedioLesoes);
        fprintf(file, "NUMERO TOTAL DE LESOES: %i\n", r->numeroTotalLesoes);
        fprintf(file, "NUMERO TOTAL DE CIRURGIAS: %i\n", r->numeroTotalCirurgias);
        fprintf(file, "NUMERO TOTAL DE CRIOTERAPIA: %i\n", r->numeroTotalCrioterapia);
    }

    fprintf(file, "\n");
    fclose(file);
}