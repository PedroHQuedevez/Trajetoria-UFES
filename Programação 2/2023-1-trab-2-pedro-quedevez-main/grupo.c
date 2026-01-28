#include <stdio.h>
#include "grupo.h"
#include "centroides.h"


void cria_arquivo_grupo_imagem (char *path_entrada, char *path_saida,char *nome_imagem,grupo_centroides *grupo,banco_imagens *banco) {
   FILE *arq;
   int pixels  = retorna_tam_img(banco);
   int array[pixels];
   char caminho_img[250];
   int menor, agrupamento,dist;

   sprintf(caminho_img,"%s/%s.csv",path_entrada,nome_imagem);
   arq = fopen (caminho_img,"r");
    
    for (int j = 0; j <pixels; j++) {
        fscanf(arq,"%i,",&array[j]);
        //fscanf(file,",");
    }
    fclose(arq);


    menor = dist_euclidiana(array,retorna_array_centroide(grupo,0),pixels); //manter ordem da entrada
    agrupamento = 0;
    for (int i = 1; i < retorna_quant_grupos(grupo); i++) {
        dist = dist_euclidiana(array,retorna_array_centroide(grupo,i),pixels);; //manter ordem da entrada
        //printf("CHEGOU5 %i\n",i);
        if (dist < menor) {
            menor = dist;
            agrupamento = i;  
        }
    }  


    char path_arquivo[250];
    sprintf(path_arquivo,"%s/grupo_%s.csv",path_saida,nome_imagem);
    arq = fopen(path_arquivo, "w");
    fprintf(arq,"%i",agrupamento);
    fclose(arq);

}


