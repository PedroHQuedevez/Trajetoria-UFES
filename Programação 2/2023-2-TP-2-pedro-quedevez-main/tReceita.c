#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tReceita.h"

struct tReceita
{
    char nomePaciente[101];
    eTipoUso tipoUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char instrucoes[MAX_TAM_INSTRUCOES];
    int qntd;
    char nomeMedico[101];
    char CRM[13];
    char dataStr[11];
};

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr)
{
    tReceita *r = (tReceita *)calloc(1, sizeof(tReceita));
    strcpy(r->nomePaciente, nomePaciente);
    if (dataStr != NULL)
    {
        strcpy(r->dataStr, dataStr);
    }
    strcpy(r->instrucoes, instrucoes);
    strcpy(r->nomeMedicamento, nomeMedicamento);
    if (nomeMedico != NULL)
    {
        strcpy(r->nomeMedico, nomeMedico);
    }
    if (CRM != NULL)
    {
        strcpy(r->CRM, CRM);
    }
    r->qntd = qntd;
    strcpy(r->tipoMedicamento, tipoMedicamento);
    r->tipoUso = tipoUso;
    return r;
}

void desalocaReceita(void *dado)
{
    if (dado != NULL)
    {
        free(dado);
    }
}

void imprimeNaTelaReceita(void *dado)
{
    tReceita *receita = (tReceita *)dado;
    printf("RECEITUARIO\n");
    printf("NOME: %s\n", receita->nomePaciente);
    printf("\n");
    if (receita->tipoUso == 0)
    {
        printf("USO ORAL\n");
    }
    else
    {
        printf("USO TOPICO\n");
    }
    printf("\n");
    printf("%s\n", receita->nomeMedicamento);
    printf("%i %s\n", receita->qntd, receita->tipoMedicamento);
    printf("\n");
    printf("%s\n", receita->instrucoes);
    printf("\n");
    printf("%s (%s)\n", receita->nomeMedico, receita->CRM);
    printf("%s\n", receita->dataStr);
}

void imprimeEmArquivoReceita(void *dado, char *path)
{
    tReceita *receita = (tReceita *)dado;

    char arquivo[1001];
    sprintf(arquivo, "%s/receita.txt", path);
    FILE *file = fopen(arquivo, "r");

    if (file == NULL)
    {
        file = fopen(arquivo, "w");
        fprintf(file, "RECEITUARIO\n");
        fprintf(file, "NOME: %s\n", receita->nomePaciente);
        fprintf(file, "\n");
        if (receita->tipoUso == 0)
        {
            fprintf(file, "USO ORAL\n");
        }
        else
        {
            fprintf(file, "USO TOPICO\n");
        }
        fprintf(file, "\n");
        fprintf(file, "%s\n", receita->nomeMedicamento);
        fprintf(file, "%i %s\n", receita->qntd, receita->tipoMedicamento);
        fprintf(file, "\n");
        fprintf(file, "%s\n", receita->instrucoes);
        fprintf(file, "\n");
        if (receita->nomeMedico != NULL && receita->CRM != NULL)
        {
            fprintf(file, "%s (%s)\n", receita->nomeMedico, receita->CRM);
        }
        else if (receita->nomeMedico == NULL && receita->CRM == NULL)
        {
            fprintf(file, " ()\n");
        }

        fprintf(file, "%s\n", receita->dataStr);
        fprintf(file, "\n");
    }
    else
    {
        fclose(file);
        file = fopen(arquivo, "a");
        fprintf(file, "RECEITUARIO\n");
        fprintf(file, "NOME: %s\n", receita->nomePaciente);
        fprintf(file, "\n");
        if (receita->tipoUso == 0)
        {
            fprintf(file, "USO ORAL\n");
        }
        else
        {
            fprintf(file, "USO TOPICO\n");
        }
        fprintf(file, "\n");
        fprintf(file, "%s\n", receita->nomeMedicamento);
        fprintf(file, "%i %s\n", receita->qntd, receita->tipoMedicamento);
        fprintf(file, "\n");
        fprintf(file, "%s\n", receita->instrucoes);
        fprintf(file, "\n");
        if (1)
        {
            fprintf(file, "%s (%s)\n", receita->nomeMedico, receita->CRM);
        }
        else
        {
            fprintf(file, " ()\n");
        }
        fprintf(file, "%s\n", receita->dataStr);
    }

    fprintf(file, "\n");
    fclose(file);
}