#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

typedef struct Consulta tConsulta;
typedef struct ListaConsultas tListaConsultas;

#include "tPaciente.h"
#include "tMedico.h"
#include "tSecretario.h"

tConsulta *IniciaConsulta(tListaPacientes *lista, char *path, char *cpf, tPaciente *pacienteSendoAtendido, tListaConsultas *consultasgerais);
char *RetornaDataConsulta(tConsulta *c);
tConsulta *RetornaUltimaConsulta(tListaConsultas *lista);
tListaConsultas *CriaListaConsultas();
void CadastrarConsultaArquivo(tListaConsultas *lista, FILE *file);
void EscreveListaConsultaBinario(tListaConsultas *lista, FILE *file);
void DestroiListaConsultas(tListaConsultas *lista);
void DestroiListaConsultasGerais(tListaConsultas *lista);
void IncrementaQuantLesaoConsulta (tConsulta *consulta);
void ImprimeListaConsultaArquivoTexto (tListaConsultas *lista, FILE *file, int quant);
#endif