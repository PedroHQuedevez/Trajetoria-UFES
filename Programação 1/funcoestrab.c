#include "funcoestrab.h"

char masculo (char a[61]) {
int i,j,b;
b =0;
i = strlen(a);
       for (j=0; j<=i; j++) {
        if (a[j] >= 97 && a[j] <= 122) {
        b = a[j]-32;
        a[j] = b;
       }
   }
}


void bemvindo () { 
printf("########################################################");
printf("            \nBEM-VINDO A MINI URNA ELETRONICA");
printf("\n########################################################");
printf("\n- Instrucoes para votar:");
printf("\n-- Digite o numero do candidato para votar");
printf("\n-- Aperte b ou B para votar em BRANCO");
printf("\n########################################################");
printf("\n- Digite seu ID para iniciar:");
}

