#ifndef _PACIENTE_H
#define _PACIENTE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct paciente tpaciente;


tpaciente *cria_paciente ();

void free_paciente (tpaciente *paciente);

void ler_paciente (tpaciente *paciente);

void print_paciente (tpaciente *paciente,FILE *path);

void atribui_dados_paciente (tpaciente *paciente);

int encontra_paciente (char *sus, tpaciente *paciente);

void atribui_lesoes_paciente (tpaciente *paciente, int qnt_les_cadastradas, char *nome_lesao);

void print_busca_paciente (tpaciente *paciente, char *argv2);

void atribui_paciente (tpaciente *paciente, char *nome, char *sus, char *data, char *telefone, char *endereco,char *genero);

void gera_log (tpaciente *paciente, char *argv1, int qnt_atendimentos);

void media_idade (tpaciente **pacientes, int qnt_pac_cadas,FILE *path);

void distribuicao_genero (tpaciente **pacientes, int qnt_pac_cadas,FILE *path);

void media_total_lesoes (tpaciente **pacientes, int qnt_pac_cadas, int qnt_lesoes_cadas,FILE *path);

void total_cirur_crio (tpaciente **pacientes, int qnt_pac_cadastrado,int total_lesao_cadastrada,FILE *path);

void totais_tipos_lesoes (tpaciente **pacientes, int qnt_pac_cadastrado,FILE *path);

void gera_relatorio (tpaciente **pacientes, int qnt_pac_cadastrados,int qnt_les_cadastradas,char *argv1);

void gera_resumo (tpaciente **pacientes, int qnt_pac_cadastrados,int qnt_les_cadastradas,int qnt_cirurgias, int qnt_crioterapias,char *argv1);

int calc_qnt_cirur_lista (tpaciente **pacientes,int qnt_pac_cad);

int calc_qnt_crio_lista (tpaciente **pacientes,int qnt_pac_cad);

void totais_regioes (tpaciente **pacientes, int qnt_pac_cadastrado,FILE *path);

#endif