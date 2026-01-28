#include <stdlib.h>
#include <stdio.h>
#include "reconstrucao.h"
#include "centroides.h"

void gera_arquivo_reconstrucao (char *path_entrada, char *path_saida,char *nome_imagem,int dimensao1,int dimensao2,banco_imagens *banco) {
    FILE *arq;
   int pixels  = retorna_tam_img(banco);
   int array[pixels];
   char caminho_img[250];

   sprintf(caminho_img,"%s/%s.csv",path_entrada,nome_imagem);
   arq = fopen (caminho_img,"r");
    
    for (int j = 0; j <pixels; j++) {
        fscanf(arq,"%i,",&array[j]);
        //fscanf(file,",");
    }
    fclose(arq);





    char path_arquivo[250];
    sprintf(path_arquivo,"%s/rec_%s.csv",path_saida,nome_imagem);
    arq = fopen(path_arquivo, "w");
int i=0,j=0;

while (i < pixels) {
    j=0;
    while (j < dimensao1) {
        if (i == pixels) {
            break;
        }
        if (j == (dimensao1 - 1)) {
        fprintf(arq,"%i",array[i]);
        i++;
        j++;    
        } else {
        fprintf(arq,"%i,",array[i]);
        i++;
        j++;
        }
    }
    if (i == pixels) {
            break;
        }
    fprintf(arq,"\n");
}

    fclose(arq);


}