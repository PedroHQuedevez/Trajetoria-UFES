#ifndef _TMEDICO_H
#define _TMEDICO_H

typedef struct Medico tMedico;
typedef struct ListaMedicos tListaMedicos;

tListaMedicos *CriaListaMedicos();
int CadastrarMedicoArquivo(tListaMedicos *lista, FILE *file);
void CadastrarMedicoTeclado(tListaMedicos *lista);
char *RetornaNomeMedico(tMedico *m);
char *RetornaCRMMedico(tMedico *m);
void PrintaMedico(tMedico *Medico);
tMedico *RealizaLoginM(tListaMedicos *lista, char *login, char *senha);
void DestroiListaMedico(tListaMedicos *l);
void EscreveBinarioMedicos(tListaMedicos *lista, FILE *file);
void ImprimeListaMedicoArquivoTexto (tListaMedicos *lista, char *path);

#endif