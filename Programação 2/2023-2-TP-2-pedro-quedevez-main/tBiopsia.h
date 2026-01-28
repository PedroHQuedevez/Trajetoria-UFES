#ifndef _TBIOPSIA_H
#define _TBIOPSIA_H

#include "tPaciente.h"

typedef struct Biopsia tBiopsia;

tBiopsia *CriaBiopsia(char *nomePaciente, char *cpfPaciente, char *nomeMedico, char *CRM, char *data, tPaciente *paciente);

void DesalocaBiopsia(void *dado);

void ImprimeNaTelaBiopsia(void *dado);

void ImprimeEmArquivoBiopsia(void *dado, char *path);

#endif