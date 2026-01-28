#ifndef _DADOSPACIENTE_H
#define _DADOSPACIENTE_H
#include <stdio.h>

typedef struct dadospaciente tdadospaciente;

tdadospaciente *cria_dados_paciente ();

void free_dados (tdadospaciente *dados);

void ler_dados (tdadospaciente *dados);

int retorna_flag (tdadospaciente *dados);

void print_dados_paciente (tdadospaciente *dados,FILE *path);

char *retorna_data (tdadospaciente *dados);

#endif