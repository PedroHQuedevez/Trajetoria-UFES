#ifndef _LESOES_H
#define _LESOES_H

#include <stdio.h>

typedef struct lesao tlesao;

tlesao **criar_lista_lesao ();

tlesao *criar_lesao ();

void realloc_lesoes(tlesao** lesoes,int qntlesoespaciente);

tlesao* adicionar_lesao_lista (int qntlt,char *nome_lesao);

void free_lesao (tlesao *lesao);

void free_lesao_lista (tlesao **lesoes, int qntlp);

void lerlesao (tlesao *lesao,int qntlesoestotal,char *nome_lesao);

void print_lesao_lista (tlesao** lesoes,int qntlp);

void print_descricao_lesao (tlesao *lesao,FILE *path);

int calc_qnt_cirur (tlesao **lesoes, int qnt_cadastrada);

int calc_qnt_crio (tlesao **lesoes, int qnt_cadastrada);

int soma_tam_lesoes (tlesao **lesoes, int qnt_cadastrada);

int compara_diagnostico (char *tipo_lesao, tlesao **lesoes,int qnt_cadastrad_les);

char *retorna_rotulo (tlesao **lesoes,int indice_lesao);

int soma_desvio_lesao (tlesao **lesoes, int qnt_cadastrada_les,int media);

int compara_regiao (char *regiao, tlesao **lesoes,int qnt_cadastrad_les);

#endif