#include "lesoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct lesao {
    char rotulo[5];
    char diagnostico[40];
    char regiao[11];
    int tamanho;
    char cirurgia[4];
    char crioterapia[4];
    int qnt_lesoes;
};

void upper_baguil (char *bagui) {
    char aux;
    int i=0;
    while (bagui[i] != '\0') {
        aux = toupper (bagui[i]);
        bagui[i] = aux;
        i++;
    }
}

tlesao **criar_lista_lesao () {
    tlesao **lesoes;
    lesoes = (tlesao **) malloc(sizeof(tlesao *));
    lesoes[0] = NULL;
    return lesoes;
}


tlesao *criar_lesao () {
    tlesao *lesao =(tlesao *) malloc(sizeof(tlesao));
    lesao->qnt_lesoes = 1;
    return lesao;
}

void lerlesao (tlesao *lesao,int qntlesaopac,char *nome_lesao) {
sprintf(lesao->rotulo,"L%i",qntlesaopac+1);

upper_baguil(nome_lesao);
sprintf(lesao->diagnostico,"%s",nome_lesao);

scanf("\n%s",lesao->regiao);
scanf("\n%d",&lesao->tamanho);

scanf("\n%s",lesao->cirurgia);
upper_baguil(lesao->cirurgia);

scanf("\n%s",lesao->crioterapia);
upper_baguil(lesao->crioterapia);

lesao->qnt_lesoes++;
}

tlesao* adicionar_lesao_lista (int qntlt,char *nome_lesao) {
    tlesao *lesao = criar_lesao();
    lerlesao(lesao,qntlt,nome_lesao);
    return lesao;
}


void free_lesao (tlesao *lesao) {
    free(lesao);
}


void free_lesao_lista (tlesao **lesoes, int qntlp) {
    for (int i=0; i <qntlp; i++) {
        free_lesao(lesoes[i]);
    }
    free (lesoes);
} 



void print_descricao_lesao (tlesao *lesao,FILE *path) {
   
    if (strcmp(lesao->cirurgia,"SIM") == 0) {    
    fprintf(path,"%s - %s - %s - %dMM - ENVIADA PARA A CIRURGIA\n",lesao->rotulo,lesao->diagnostico,lesao->regiao,lesao->tamanho);
    }   else if (strcmp(lesao->crioterapia,"SIM") == 0) {    
            fprintf(path,"%s - %s - %s - %dMM - ENVIADA PARA A CRIOTERAPIA\n",lesao->rotulo,lesao->diagnostico,lesao->regiao,lesao->tamanho);
        } else {
            fprintf(path,"%s - %s - %s - %dMM\n",lesao->rotulo,lesao->diagnostico,lesao->regiao,lesao->tamanho);
        }
}


//qnt_cadastrada_les é a quantidade de lesões cadastrada em cada paciente;
int calc_qnt_cirur (tlesao **lesoes, int qnt_cadastrada_les) {
int total = 0;
    for (int i =0 ; i<qnt_cadastrada_les; i++) {
            if (strcmp(lesoes[i]->cirurgia,"SIM")==0) {
                total++;
        }
    }
return total;    
}


int calc_qnt_crio (tlesao **lesoes, int qnt_cadastrada_les) {
    int total = 0;
    for (int i =0 ; i<qnt_cadastrada_les; i++) {
            if (strcmp(lesoes[i]->crioterapia,"SIM")==0) {
                total++;
        }
    }
return total;
}



int soma_tam_lesoes (tlesao **lesoes, int qnt_cadastrada_les) {
    int total = 0;
    for (int i =0 ; i<qnt_cadastrada_les; i++) {
        total = lesoes[i]->tamanho + total;
    }
    return total;
}

int soma_desvio_lesao (tlesao **lesoes, int qnt_cadastrada_les,int media) {
    int somatorio = 0;
    for (int i =0 ; i<qnt_cadastrada_les; i++) {
        somatorio = ((lesoes[i]->tamanho - media)*(lesoes[i]->tamanho - media));
    }
    return somatorio;
}

int compara_diagnostico (char *tipo_lesao, tlesao **lesoes,int qnt_cadastrad_les) {
 int total = 0;   
for (int i=0; i<qnt_cadastrad_les; i++) {
    if (strcmp(lesoes[i]->diagnostico,tipo_lesao)==0){
        total++;
    }
  }
  return total++;  
}

int compara_regiao (char *regiao, tlesao **lesoes,int qnt_cadastrad_les) {
 int total = 0;   
for (int i=0; i<qnt_cadastrad_les; i++) {
    if (strcmp(lesoes[i]->regiao,regiao)==0){
        total++;
    }
  }
  return total++;  
}


char *retorna_rotulo (tlesao **lesoes,int indice_lesao) {
    return lesoes[indice_lesao]->rotulo;
}