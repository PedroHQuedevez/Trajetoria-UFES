#ifndef _CLINICA_H
#define _CLINICA_H

typedef struct clinica tclinica;

void cria_pastas ();

tclinica* construir_clinica ();

void free_clinica (tclinica *clinica, int qnt_pac_cadastrados);

void ler_clinica (tclinica *clinica, char *argv2);

int return_int (int inteiro);


#endif