#ifndef _TPACIENTE_H
#define _TPACIENTE_H

typedef struct Paciente tPaciente;
typedef struct ListaPacientes tListaPacientes;

#include "tLesoes.h"
#include "tConsulta.h"

tListaPacientes *CriaListaPacientes();
void CadastrarPacienteTeclado(tListaPacientes *lista);
int CadastrarPacienteArquivo(tListaPacientes *lista, FILE *filePacientes, FILE *fileLesoes, FILE *fileConsultas, tListaLesoes *listalesaogerais);
void PrintaPaciente(tPaciente *paciente);
char *RetornaNomePaciente(tPaciente *p);
char *RetornaCpfPaciente(tPaciente *p);
tConsulta *RetornaConsultaPaciente(tPaciente *p);
void ImprimeNomeDataPaciente(tPaciente *p);
int RetornaSizeListaPacientes(tListaPacientes *lista);
int VerificaCpfExiste(tListaPacientes *listaPacientes, char *cpf);
tPaciente *RetornaPacienteidx(tListaPacientes *lista, int pacienteidx);
void VinculaConsultaPaciente(tPaciente *paciente, tConsulta *consulta);
char *RetornaCpfPacienteLista(tListaPacientes *lista, int i);
tListaLesoes *RetornaListaLesoesPaciente(tPaciente *p);
void DestroiListaPaciente(tListaPacientes *l);
int ComparaNomeBusca(tListaPacientes *lista, char *nomeProcurado, int idx);
tListaConsultas *RetornaListaConsultasPaciente(tPaciente *p);
void EscreveBinarioPacientes(tListaPacientes *lista, FILE *filePacientes, FILE *fileLesoes, FILE *fileConsultas);
void IncrementaQuantidadeLesaoPaciente(tPaciente *p);
void IncrementaQuantidadeConsultaPaciente(tPaciente *p);
void SetaPacienteAtendido(tPaciente *p);
int CalculaTotalAtendidos(tListaPacientes *listaPacientes);
int CalculaTotalFem(tListaPacientes *listaPacientes);
int CalculaTotalMasc(tListaPacientes *listaPacientes);
int CalculaTotalOut(tListaPacientes *listaPacientes);
int calcularIdade(char *dataAtual, char *dataNascimento);
int CalculaIdadeMediaPacientes(tListaPacientes *listaPacientes);
void RemoveZerosEsquerda(char *data);
void ImprimeListaPacienteArquivoTexto(tListaPacientes *lista, char *path);
#endif