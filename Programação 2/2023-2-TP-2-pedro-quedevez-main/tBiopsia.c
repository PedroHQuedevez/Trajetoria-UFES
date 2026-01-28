#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBiopsia.h"
#include "tPaciente.h"

struct Biopsia
{
    char nomePaciente[101];
    char cpfPaciente[15];
    char nomeMedico[101];
    char CRM[13];
    char data[11];
    tPaciente *paciente;
};

tBiopsia *CriaBiopsia(char *nomePaciente, char *cpfPaciente, char *nomeMedico, char *CRM, char *data, tPaciente *paciente)
{
    tBiopsia *e = (tBiopsia *)calloc(1, sizeof(tBiopsia));

    strcpy(e->nomePaciente, nomePaciente);
    strcpy(e->cpfPaciente, cpfPaciente);

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

    e->paciente = paciente;

    return e;
}

void DesalocaBiopsia(void *dado)
{
    if (dado != NULL)
    {
        free(dado);
    }
}

void ImprimeNaTelaBiopsia(void *dado)
{
    tBiopsia *b = (tBiopsia *)dado;
    printf("PACIENTE: %s\n", b->nomePaciente);
    printf("CPF: %s\n", b->cpfPaciente);

    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    // tListaLesoes *lista = RetornaListaLesoesPaciente(b->paciente);

    AuxiliaArquivoBiopsiaTela(b->paciente);

    if (b->nomeMedico == NULL)
    {
        printf(" ()\n");
    }
    else
    {
        printf("%s (%s)\n", b->nomeMedico, b->CRM);
    }
    printf("%s\n", b->data);
}

void ImprimeEmArquivoBiopsia(void *dado, char *path)
{
    char arquivo[1001];
    sprintf(arquivo, "%s/biopsia.txt", path);
    FILE *file = fopen(arquivo, "r");

    tBiopsia *b = (tBiopsia *)dado;

    if (file == NULL)
    {
        file = fopen(arquivo, "w");
        fprintf(file, "PACIENTE: %s\n", b->nomePaciente);
        fprintf(file, "CPF: %s\n", b->cpfPaciente);
        fprintf(file, "\n");
        fprintf(file, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
        // tListaLesoes *lista = RetornaListaLesoesPaciente(b->paciente);

        AuxiliaArquivoBiopsiaArquivo(b->paciente, file);

        if (b->nomeMedico[0] == '\0')
        {
            fprintf(file, "\n");
            fprintf(file, " ()\n");
        }
        else
        {
            fprintf(file, "\n");
            fprintf(file, "%s (%s)\n", b->nomeMedico, b->CRM);
        }
        fprintf(file, "%s\n", b->data);
    }
    else
    {
        fclose(file);
        file = fopen(arquivo, "a");
        fprintf(file, "PACIENTE: %s\n", b->nomePaciente);
        fprintf(file, "CPF: %s\n", b->cpfPaciente);
        fprintf(file, "\n");
        fprintf(file, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
        // tListaLesoes *lista = RetornaListaLesoesPaciente(b->paciente);

        AuxiliaArquivoBiopsiaArquivo(b->paciente, file);

        if (b->nomeMedico[0] == '\0')
        {
            fprintf(file, "\n");
            fprintf(file, " ()\n");
        }
        else
        {
            fprintf(file, "\n");
            fprintf(file, "%s (%s)\n", b->nomeMedico, b->CRM);
        }
        fprintf(file, "%s\n", b->data);
    }

    fprintf(file, "\n");
    fclose(file);
}