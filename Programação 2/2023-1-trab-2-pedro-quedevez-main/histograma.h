#ifndef _HISTOGRAMA_H
#define _HISTOGRAMA_H
#include "centroides.h"
typedef struct histograma histograma;

void cria_histograma(char *path_entrada, char *path_saida, char *nome_imagem, banco_imagens *banco, int inc_inter, int fim_inter, int intervalos);

#endif