#ifndef _TBUSCA_H
#define _TBUSCA_H

#include "tPaciente.h"

typedef struct Busca tBusca;

tBusca *CriaBusca(tListaPacientes *lista, char *nomePaciente, char *path);

void DesalocaBusca(void *dado);

void ImprimeNaTelaBusca(void *dado);

void ImprimeEmArquivoBusca(void *dado, char *path);

#endif