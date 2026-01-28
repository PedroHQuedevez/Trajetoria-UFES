#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tEncaminhamento.h"

struct Encaminhamento
{
    char nomePaciente[101];
    char cpfPaciente[15];
    char especialidade[50];
    char motivo[300];
    char nomeMedico[101];
    char CRM[13];
    char data[11];
};

tEncaminhamento *CriaEncaminhamento(char *nomePaciente, char *cpfPaciente, char *especialidade,
                                    char *motivo, char *nomeMedico, char *CRM, char *data)
{
    tEncaminhamento *e = (tEncaminhamento *)calloc(1, sizeof(tEncaminhamento));

    strcpy(e->nomePaciente, nomePaciente);
    strcpy(e->cpfPaciente, cpfPaciente);
    strcpy(e->especialidade, especialidade);
    strcpy(e->motivo, motivo);
    if (nomeMedico != NULL)
    {
        strcpy(e->nomeMedico, nomeMedico);
    }
    if (CRM != NULL)
    {
        strcpy(e->CRM, CRM);
    }

    if (data != NULL)
    {
        strcpy(e->data, data);
    }

    return e;
}

void DesalocaEncaminhamento(void *dado)
{
    if (dado != NULL)
    {
        free(dado);
    }
}

void ImprimeNaTelaEncaminhamento(void *dado)
{
    tEncaminhamento *e = (tEncaminhamento *)dado;
    printf("PACIENTE: %s\n", e->nomePaciente);
    printf("CPF: %s\n", e->cpfPaciente);
    printf("ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    printf("MOTIVO: %s\n", e->motivo);
    if (e->nomeMedico == NULL)
    {
        printf(" ()\n");
    }
    else
    {
        printf("%s (%s)\n", e->nomeMedico, e->CRM);
    }
    printf("%s\n", e->data);
}

void ImprimeEmArquivoEncaminhamento(void *dado, char *path)
{
    tEncaminhamento *e = (tEncaminhamento *)dado;

    char arquivo[1001];
    sprintf(arquivo, "%s/encaminhamento.txt", path);
    FILE *file = fopen(arquivo, "r");

    if (file == NULL)
    {
        file = fopen(arquivo, "w");
        fprintf(file, "PACIENTE: %s\n", e->nomePaciente);
        fprintf(file, "CPF: %s\n", e->cpfPaciente);
        fprintf(file, "\n");
        fprintf(file, "ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
        fprintf(file, "MOTIVO: %s\n", e->motivo);
        fprintf(file, "\n");
        if (e->nomeMedico[0] == '\0')
        {
            fprintf(file, " ()\n");
        }
        else
        {
            fprintf(file, "%s (%s)\n", e->nomeMedico, e->CRM);
        }
        fprintf(file, "%s\n", e->data);
    }
    else
    {
        fclose(file);
        file = fopen(arquivo, "a");
        fprintf(file, "PACIENTE: %s\n", e->nomePaciente);
        fprintf(file, "CPF: %s\n", e->cpfPaciente);
        fprintf(file, "\n");
        fprintf(file, "ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
        fprintf(file, "MOTIVO: %s\n", e->motivo);
        fprintf(file, "\n");
        if (e->nomeMedico[0] == '\0')
        {
            fprintf(file, " ()\n");
        }
        else
        {
            fprintf(file, "%s (%s)\n", e->nomeMedico, e->CRM);
        }
        fprintf(file, "%s\n", e->data);
    }

    fclose(file);
}