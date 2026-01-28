#ifndef _TRELATORIO_H
#define _TRELATORIO_H

typedef struct Relatorio tRelatorio;

tRelatorio *CriaRelatorio(int numeroTotalAtendidos, int idadeMedia, int fem, int masc,
                          int out, int tamanhoMedioLesoes, int numeroTotalLesoes,
                          int numeroTotalCirurgias, int numeroTotalCrioterapia);

void DesalocaRelatorio(void *dado);

void ImprimeNaTelaRelatorio(void *dado);

void ImprimeEmArquivoRelatorio(void *dado, char *path);

#endif