#include <stdio.h>
#include <stdlib.h>

#include "tBanco.h"

FILE *iniciaArquivoBin(char *arquivoCaminho, FILE *file)
{
    if (file == NULL)
    {
        file = fopen(arquivoCaminho, "wb");
    }
    return file;
}

int LeBancoDadosSecretarios(tListaSecretarios *lista, FILE *fileSecretario)
{

    if (fileSecretario != NULL)
    {
        while (1)
        {
            if (CadastrarSecretarioArquivo(lista, fileSecretario) == 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

int LeBancoDadosMedicos(tListaMedicos *lista, FILE *fileMedicos)
{

    if (fileMedicos != NULL)
    {
        while (1)
        {
            if (CadastrarMedicoArquivo(lista, fileMedicos) == 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

int LeBancoDadosPacientes(tListaPacientes *listaPacientes, FILE *filePacientes, FILE *fileLesoes, FILE *fileConsultas, tListaLesoes *listalesaogerais)
{

    if (filePacientes != NULL)
    {
        while (1)
        {
            if (CadastrarPacienteArquivo(listaPacientes, filePacientes, fileLesoes, fileConsultas, listalesaogerais) == 0)
            {

                return 1;
            }
        }
    }

    return 0;
}