#ifndef _TLESOES_H
#define _TLESOES_H

typedef struct Listalesoes tListaLesoes;
typedef struct Lesao tLesao;

#include "tPaciente.h"

tListaLesoes *CriaListaLesoes();
void CadastrarLesaoArquivo(tListaLesoes *lista, FILE *file, tListaLesoes *listalesaogerais);
void CadastraLesaoTeclado(tPaciente *paciente, tListaLesoes *lesoesgerais, int quantLesoesConsulta);
int VerificaExisteCasoCirurgico(tListaLesoes *lista);
void AuxiliaArquivoBiopsiaTela(tPaciente *paciente);
void AuxiliaArquivoBiopsiaArquivo(tPaciente *paciente, FILE *file);
void EscreveListaLesaoBinario(tListaLesoes *lista, FILE *file);
int CalculaTamMedioLesoes(tListaLesoes *listaLesoesgerais);
int CalculaTotalLesoes(tListaLesoes *listaLesoesgerais);
int CalculaTotalCirurgias(tListaLesoes *listaLesoesgerais);
int CalculaTotalCrioterapia(tListaLesoes *listaLesoesgerais);
void DestroiListaLesoes(tListaLesoes *lista);
void DestroiListaLesoesGerais(tListaLesoes *lista);
void printaListaLesoes(tListaLesoes *lista);
void ImprimeListaLesaoArquivoTexto (tListaLesoes *lista, FILE *file, int quantImprimir);
#endif