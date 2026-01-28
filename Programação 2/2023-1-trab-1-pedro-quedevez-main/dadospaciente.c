#include "dadospaciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

struct dadospaciente {
    char data_atendimento[11];
    char diabetes[4]; //mudar para strings de tamanho conhecido
    char fumante[4];
    char alergias[4];
    char nomes_remedios[100];
    char cancer[4];
    char tipopele[5];
    int flag_atendimento_feito;
};

void upper_baguid (char *bagui) {
    char aux;
    int i=0;
    while (bagui[i] != '\0') {
        aux = toupper (bagui[i]);
        bagui[i] = aux;
        i++;
    }
}

tdadospaciente *cria_dados_paciente () { 
    tdadospaciente *dados;    
    dados = (tdadospaciente*) malloc(sizeof(tdadospaciente));
    dados->flag_atendimento_feito =0;
    return dados;
    }

void free_dados (tdadospaciente *dados) {
    free(dados);
}

void ler_dados (tdadospaciente *dados) {  
    scanf("\n%s", dados->data_atendimento);

    scanf("\n%s", dados->diabetes);
    upper_baguid(dados->diabetes);

    scanf("\n%s", dados->fumante);
    upper_baguid(dados->fumante);
    
    scanf("\n%s", dados->alergias); 
    upper_baguid(dados->alergias);

    if (strcmp(dados->alergias,"SIM") == 0) {
         scanf("\n%100[^\n]",dados->nomes_remedios);
    } 

    scanf("\n%s", dados->cancer);
    upper_baguid(dados->cancer);

    scanf("\n%s", dados->tipopele);
    dados->flag_atendimento_feito = 1;
}

int retorna_flag (tdadospaciente *dados) {
    return dados->flag_atendimento_feito;
}

void print_dados_paciente (tdadospaciente *dados,FILE *path) {
   
    fprintf(path,"DIABETES:%s\n", dados->diabetes);
    fprintf(path,"FUMANTE: %s\n", dados->fumante);
    fprintf(path,"ALERGIA A MEDICAMENTO: %s",dados->alergias);   
     if (strcmp(dados->alergias,"SIM") == 0) {
        fprintf(path," %s",dados->nomes_remedios);
    } 
    fprintf(path,"\n");
    fprintf(path,"HISTORICO DE CANCER: %s\n", dados->cancer);
    fprintf(path,"TIPO DE PELE: %s\n", dados->tipopele);
    fprintf(path,"\n");
}

char *retorna_data (tdadospaciente *dados) {
    return dados->data_atendimento;
}