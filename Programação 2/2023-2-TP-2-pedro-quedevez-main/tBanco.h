#ifndef _TBANCO_H
#define _TBANCO_H

#include "tMedico.h"
#include "tPaciente.h"
#include "tSecretario.h"
#include "tLesoes.h"

int LeBancoDadosSecretarios(tListaSecretarios *lista, FILE *fileSecretario);
int LeBancoDadosMedicos(tListaMedicos *lista, FILE *file);
int LeBancoDadosPacientes(tListaPacientes *lista, FILE *filePaciente, FILE *filelesoes, FILE *consultas, tListaLesoes *listalesaogerais);
FILE *iniciaArquivoBin(char *arquivoCaminho, FILE *file);
#endif