#ifndef _TSECRETARIO_H
#define _TSECRETARIO_H

typedef struct Secretario tSecretario;
typedef struct ListaSecretarios tListaSecretarios;
typedef struct SecretarioInicio  tSecretarioInicio;

tListaSecretarios *CriaListaSecretarios();
void CadastrarSecretarioTeclado(tListaSecretarios *lista);
int CadastrarSecretarioArquivo(tListaSecretarios *lista, FILE *file);
tSecretario *RealizaLoginS(tListaSecretarios *lista, char *login, char *senha);
int VerificaNivelAcesso(tSecretario *s);
void PrintaSecretario(tSecretario *Secretario);
void DestroiListaSecretario(tListaSecretarios *l);
void EscreveBinarioSecretarios(tListaSecretarios *lista, FILE *file);
void PrimeiroCadastro(tListaSecretarios *lista);
void ImprimeListaSecretariosArquivoTexto (tListaSecretarios *lista, char *path);
int CadastrarSecretarioInicioArquivo(tListaSecretarios *lista, FILE *file);
#endif