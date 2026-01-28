
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//só pra dizer que tem
#include "funcoestrab.h"


//Só não consegui implementar o critério de desempate nas vagas do partido

typedef struct partido {
char nome[61];
char sigla[4];
char numero[3];
float quantvotospart;
float quantvagase;
float quantvagasf;
}tpartido;

typedef struct candidato {
    char nome[61];
    char genero[2];
    float idade;
    char cargo[2];
    char numero[6];
    char partido[3];
} tcandidato;

typedef struct eleitor {
    char nome[61];
    char identificador[7];
    int votou;
} teleitor;

typedef struct voto { // na real é desnecessária infelizmente.
    char governador[3];
    char deputadoestadual[7];
    char deputadofederal[7];
    char presidente[3];
    char aux[7];
} tvoto;

typedef struct linkarvotocandidato {
     char candidato[61];
     float  quantvotos;
} tquantvotos;

typedef struct ranking { // igual a struct candidato! para fazer as trocas e organizar o ranking
    char nome[61];
    char genero[2];
    float idade;
    char cargo[2];
    char numero[6];
    char partido[3];
    float  quantvotos;  // + essa pra ordenar
} tranking;




 int quantlinhapar () {
    FILE *partidos = fopen("partidos.csv","r");
int i;
tpartido partido;
if (partidos == NULL) {
    printf("erro na abertura do arquivo");
    exit(1);
    }
i=0;
while (fscanf (partidos,"%61[^,],%6[^,],%i\n", partido.nome, partido.sigla, &partido.numero) != -1) {
    i =i+1;
}

 fclose(partidos);
return (i-1); //o i está contando uma última linha fantasma.
}


float quantlinhaelei () {
    FILE *eleitores = fopen("eleitores.csv","r");
float i;
teleitor eleitor;
if (eleitores == NULL) {
    printf("erro na abertura do arquivo");
    exit(1);
    }
i=0;
fscanf (eleitores,"Nome,Identificador");
while (fscanf (eleitores,"%60[^,],%6[^\n]\n ", eleitor.nome, eleitor.identificador) != -1) { //com %6 entra em loop infinito não sei bem o motivo.
    i =i+1;   
 }

 fclose(eleitores);

return (i);
}

int quantlinhacand () {
    FILE *candidatos = fopen("candidatos.csv","r");
int i;
tcandidato candidato;
if (candidatos == NULL) {
    printf("erro na abertura do arquivo");
    exit(1);
    }
i=0;
fscanf (candidatos,"Nome,Genero,Idade,Cargo,Numero,Partido\n");
while (fscanf (candidatos,"%61[^,],%2[^,],%f,%2[^,],%6[^,],%4[^\n]", candidato.nome, candidato.genero, &candidato.idade,candidato.cargo,candidato.numero,candidato.partido) != -1) {
    i =i+1;
  }
  fclose(candidatos);
 return i; 
}



int main (int argc, char *argv[]) {
 int i,j,k,auxexiste,auxrefaz,auxv,auxv2,auxv3;
 float presentes,brancoE,brancoF,brancoG,brancoP,nuloE,nuloF,nuloG,nuloP,idadep,idadeg,idadef,idadee,auxf,m,f,o;
 auxexiste=auxv3=presentes=auxf=m=f=o=0;
 brancoE=brancoF=brancoG=brancoP=0;
 nuloE=nuloF=nuloG=nuloP=0;
 idadep=idadeg=idadef=idadee=0;
 char finalizador[2],id[7],auxs[61];;
tvoto votos[1000];//usar quantidade de eleitores;
tquantvotos quantvotos[360];
tcandidato candidato[360];
tpartido partido[10];
teleitor eleitor[1000];
char argumento[100],argumento2[100];

 //------------------------------------------------------------------------------------------------------------------------
sprintf(argumento, "%s/partidos.csv", argv[1]);
 FILE *partidos = fopen(argumento,"r");


if (partidos == NULL) {
    printf("erro na abertura do arquivo");
    exit(1);
    }
i=0;

fscanf (partidos,"Partido,Sigla,Numero\n]");
while (fscanf (partidos,"%61[^,],%[^,],%3[^\n]\n", partido[i].nome, partido[i].sigla, partido[i].numero) != -1) {
    i =i+1;
    }
for (j=0; j < i; j++) { //o i está lendo uma linha fantasma então é até i-1
//printf("nome:%s \n sigla:%s \n numero:%i\n", partido[j].nome, partido[j].sigla, partido[j].numero);
  }
fclose(partidos);

//-------------------------------------------------------------------------------------------------------------------------
strcpy(argumento,"\0");
sprintf(argumento, "%s/candidatos.csv", argv[1]);
 FILE *candidatos = fopen(argumento,"r");

if (candidatos == NULL) {
    printf("erro na abertura do arquivo");
    exit(1);
    }
i=0;        

fscanf (candidatos,"Nome,Genero,Idade,Cargo,Numero,Partido\n");
while (!feof(candidatos)) {
    auxexiste =0;
    fscanf (candidatos,"%61[^,],%2[^,],%f,%2[^,],%6[^,],%3[^\n]\n",candidato[i].nome,candidato[i].genero,&candidato[i].idade,candidato[i].cargo,candidato[i].numero,candidato[i].partido);
    masculo(candidato[i].nome);
    //printf("nome:%s\ngenero:%s\nidade:%i\ncargo:%s\nnumero:%i\npartido:%s\n", candidato[i].nome, candidato[i].genero, candidato[i].idade,candidato[i].cargo,candidato[i].numero,candidato[i].partido);
    i =i+1; // quantidade lida
}

fclose(candidatos);

//------------------------------------------------------------------------------------------------------------------------- 
strcpy(argumento,"\0");
sprintf(argumento, "%s/eleitores.csv", argv[1]);


FILE *eleitores = fopen(argumento,"r");

if (eleitores == NULL) {
    printf("erro na abertura do arquivo");
    exit(1);
    }
i=0;

fscanf (eleitores,"Nome,Identificador\n");

while (!feof(eleitores)) {
       
fscanf (eleitores,"%60[^,],%6[^\n]\n ", eleitor[i].nome,eleitor[i].identificador);
   // printf("nome:%s \n identificador:%s\n", eleitor[i].nome,eleitor[i].identificador);
    i =i+1;
}
fclose(eleitores);
//-------------------------------------------------------------------------------------------------------------------------------------------------
//impugnar candidato
auxv = auxv2 =0;
for (k=0; k<320; k++) {
    for (i=0; i<10; i++) {
     auxv = strcmp(candidato[k].partido,partido[i].sigla);
     if (auxv2 == 0) {
        quantvotos[k].quantvotos = 1; // usando essa struct só pra não criar outra;
     }
   }
}

for (k=0; k<320; k++) {
    if (quantvotos[k].quantvotos != 1) { // partido inválido
        //candidato impugnado;
        strcpy (candidato[k].nome,"\0");
        strcpy (candidato[k].genero,"\0");
        candidato[k].idade = 0;
        strcpy (candidato[k].cargo,"\0");
        strcpy (candidato[k].numero,"\0");
        strcpy (candidato[k].partido,"\0");
    }
}
for (k=0; k<320; k++) {
    auxv = strcmp(candidato[k].cargo,"P");
    if (auxv == 0) {
        quantvotos[k].quantvotos = 2; //pra não ter que resetar o array
    }
    auxv = strcmp(candidato[k].cargo,"G");
    if (auxv == 0) {
        quantvotos[k].quantvotos = 2;
    }
    auxv = strcmp(candidato[k].cargo,"F");
    if (auxv == 0) {
        quantvotos[k].quantvotos = 2;
    }
    auxv = strcmp(candidato[k].cargo,"E");
    if (auxv == 0) {
        quantvotos[k].quantvotos = 2;
    }
}

for (k=0; k<320; k++) {
    if (quantvotos[k].quantvotos != 2) { // cargo não existe
        //candidato impugnado;
        strcpy (candidato[k].nome,"\0");
        strcpy (candidato[k].genero,"\0");
        candidato[k].idade = 0;
        strcpy (candidato[k].cargo,"\0");
        strcpy (candidato[k].numero,"\0");
        strcpy (candidato[k].partido,"\0");
    }
}

for (k=0; k<320; k++) {
    for (i=0; i<10; i++) {
     
    auxv2 = strcmp(candidato[k].partido,partido[i].sigla);
    
    auxv = strcmp(candidato[k].cargo,"P");
    if (auxv == 0 && auxv2 == 0) {
       auxv3 = strcmp(candidato[k].numero,partido[i].numero);
       if (auxv3 == 0) {
         quantvotos[k].quantvotos = 3;
       }
    }
    auxv = strcmp(candidato[k].cargo,"G");
    if (auxv == 0 && auxv2 == 0) {
        auxv3 = strcmp(candidato[k].numero,partido[i].numero);
       if (auxv3 == 0) {
         quantvotos[k].quantvotos = 3;
       }
    }
    auxv = strcmp(candidato[k].cargo,"F");
    if (auxv == 0 && auxv2 == 0) { //comparar somente os dois primeiros caracteres da string
        if ((candidato[k].numero[0] == partido[i].numero[0]) && (candidato[k].numero[1] == partido[i].numero[1]));
        quantvotos[k].quantvotos = 3;
    }
    auxv = strcmp(candidato[k].cargo,"E");
    if (auxv == 0 && auxv2 == 0) {
        if ((candidato[k].numero[0] == partido[i].numero[0]) && (candidato[k].numero[1] == partido[i].numero[1]));
        quantvotos[k].quantvotos = 3;
    }
  }
}

for (k=0; k<320; k++) {
    if (quantvotos[k].quantvotos != 3) { //numero incompatível com o partido
        //candidato impugnado;
        strcpy (candidato[k].nome,"\0");
        strcpy (candidato[k].genero,"\0");
        candidato[k].idade = 0;
        strcpy (candidato[k].cargo,"\0");
        strcpy (candidato[k].numero,"\0");
        strcpy (candidato[k].partido,"\0");
    }
}


for (k=0; k<320; k++) {
    auxv = strcmp(candidato[k].cargo,"P");
    if (auxv == 0) {
      auxv2=strlen(candidato[k].numero);
      if (auxv2 == 2) {
        quantvotos[k].quantvotos = 4;
      }
    }
  }

  for (k=0; k<320; k++) {
    auxv = strcmp(candidato[k].cargo,"G");
    if (auxv == 0) {
      auxv2=strlen(candidato[k].numero);
      if (auxv2 == 2) {
        quantvotos[k].quantvotos = 4;
      }
    }
  }

  for (k=0; k<320; k++) {
    auxv = strcmp(candidato[k].cargo,"F");
    if (auxv == 0) {
      auxv2=strlen(candidato[k].numero);
      if (auxv2 == 4) {
        quantvotos[k].quantvotos = 4;
      }
    }
  }

  for (k=0; k<320; k++) {
    auxv = strcmp(candidato[k].cargo,"E");
    if (auxv == 0) {
      auxv2=strlen(candidato[k].numero);
      if (auxv2 == 5) {
        quantvotos[k].quantvotos = 4;
      }
    }
  }

  for (k=0; k<320; k++) {
    if (quantvotos[k].quantvotos != 4) { //numero imcompativel com o cargo
        //candidato impugnado;
        strcpy (candidato[k].nome,"\0");
        strcpy (candidato[k].genero,"\0");
        candidato[k].idade = 0;
        strcpy (candidato[k].cargo,"\0");
        strcpy (candidato[k].numero,"\0");
        strcpy (candidato[k].partido,"\0");
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------
//enchendo os array's de votos com 0's;
for (k=0; k<320; k++) {
   quantvotos[k].quantvotos = 0;
}

for (k=0;k<1000;k++) {
eleitor[k].votou = 0;
}
//COMEÇO DA VOTAÇÃO -------------------------------------------------------------------------------------------------------------------------------
for (i=0; i<1000; i++) { // até mil leituras de id. começo da votação!


auxv = strcmp("f",finalizador);
auxv2 = strcmp ("F", finalizador);
if ((auxv == 0) || (auxv2 == 0)) {
    break;
}

bemvindo();
scanf("%s",id); 
auxexiste = 0;

for (k=0;k<1000;k++) {
auxv = strcmp(id, eleitor[k].identificador); //verifica se o id é valido
auxexiste = 0; // só pra ter certeza que a variável ta zerando sempre.

if (auxv == 0 && eleitor[k].votou == 1){
    i = i-1; 
    printf("digite um id valido:\n");
    continue;
}

if (auxv == 0 && eleitor[k].votou == 0) { // condição para entrar na votação
   // strcpy(eleitor[k].identificador,"-1");
    eleitor[k].votou = 1;
    
//registar o primeiro voto deputado estadual ----------------------------------------------------------------------------------------------------
for (auxrefaz = 0; auxrefaz <1; auxrefaz++) { //caso o eleitor queira refazer o contador será resetado para 0 e a votação irá repetir
printf("########################################################");
printf("################# URNA ELETRONICA #######################");
printf("########################################################");
printf("- VOTE PARA DEPUTADO ESTADUAL:");
scanf("%s",votos[i].deputadoestadual);

//verificar se o número do deputado é valido;
for (k=0;k<360;k++) {
      auxv = strcmp(votos[i].deputadoestadual,candidato[k].numero);
      auxv2 = strcmp("E",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
      auxexiste = auxexiste +1; // para não entrar no anula;
     }
}

// no refaz o auexiste não reseta.
for (k=0;k<360;k++) {
     auxv = strcmp(votos[i].deputadoestadual,candidato[k].numero);
     auxv2 = strcmp("E",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em:");
    printf("- Nome: %s",candidato[k].nome);
    printf("- PARTIDO: %s",candidato[k].partido);
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].deputadoestadual);
         auxv = strcmp(votos[i].deputadoestadual,"r");
         auxv2 = strcmp(votos[i].deputadoestadual,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
       
    }else {
    quantvotos[k].quantvotos = quantvotos[k].quantvotos+1; //linkar voto ao político; nova struct? seguir a ordem i e criar um array de votos
                                                           //preciso encher o array de zeros antes; seguindo a ordem dos candidatos;
    }
  }
}



auxv = strcmp(votos[i].deputadoestadual,"b");
auxv2 = strcmp(votos[i].deputadoestadual,"B");
if ((auxexiste == 0) && (auxv != 0) && (auxv2 != 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta ANULANDO seu voto:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].deputadoestadual);
    auxv = strcmp(votos[i].deputadoestadual,"r");
    auxv2 = strcmp(votos[i].deputadoestadual,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    } else {
        nuloE = nuloE+1;
    }
}

// branco
auxv = strcmp(votos[i].deputadoestadual,"b");
auxv2 = strcmp(votos[i].deputadoestadual,"B");
if ((auxv == 0 || auxv2 == 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em BRANCO:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].deputadoestadual);
    auxv = strcmp(votos[i].deputadoestadual,"r");
    auxv2 = strcmp(votos[i].deputadoestadual,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
        
    } else {
        brancoE = brancoE+1;
    }
  }
}
//----------------------------------------------------------------------------------------------------------------------------
//registrar segundo voto deputado federal
//resetando variáveis úteis
auxexiste = 0;
for (auxrefaz = 0; auxrefaz <1; auxrefaz++) { //caso o eleitor queira refazer o contador será resetado para 0 e a votação irá repetir
printf("########################################################");
printf("################# URNA ELETRONICA #######################");
printf("########################################################");
printf("- VOTE PARA DEPUTADO FEDERAL:");

scanf("%s",votos[i].deputadofederal);

for (k=0;k<360;k++) {
     auxv = strcmp(votos[i].deputadofederal,candidato[k].numero);
     auxv2 = strcmp("F",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
      auxexiste = auxexiste +1;
     }
}



for (k=0;k<360;k++) {
     auxv = strcmp(votos[i].deputadofederal,candidato[k].numero);
     auxv2 = strcmp("F",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em:");
    printf("- Nome: %s",candidato[k].nome);
    printf("- PARTIDO: %s",candidato[k].partido);
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
         scanf("%s",votos[i].deputadofederal);
         auxv = strcmp(votos[i].deputadofederal,"r");
         auxv2 = strcmp(votos[i].deputadofederal,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    }else {
    quantvotos[k].quantvotos = quantvotos[k].quantvotos+1;
    }
  }
}

auxv = strcmp(votos[i].deputadofederal,"b");
auxv2 = strcmp(votos[i].deputadofederal,"B");
if ((auxexiste == 0) && (auxv != 0) && (auxv2 != 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta ANULANDO seu voto:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].deputadofederal);
         auxv = strcmp(votos[i].deputadofederal,"r");
         auxv2 = strcmp(votos[i].deputadofederal,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    } else {
        nuloF = nuloF+1;
    }
}

// branco
auxv = strcmp(votos[i].deputadofederal,"b");
auxv2 = strcmp(votos[i].deputadofederal,"B");
if ((auxv == 0 || auxv2 == 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em BRANCO:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
        scanf("%s",votos[i].deputadofederal);
         auxv = strcmp(votos[i].deputadofederal,"r");
         auxv2 = strcmp(votos[i].deputadofederal,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    } else {
        brancoF = brancoF+1;
    }
  }
}  
//--------------------------------------------------------------------------------------------------------------------------------------
//registrar terceiro voto governador
//resetando váriavéis úteis.
auxexiste = 0;
for (auxrefaz = 0; auxrefaz <1; auxrefaz++) { //caso o eleitor queira refazer o contador será resetado para 0 e a votação irá repetir
printf("########################################################");
printf("################# URNA ELETRONICA #######################");
printf("########################################################");
printf("- VOTE PARA GOVERNADOR:");

scanf("%s",votos[i].governador);

for (k=0;k<360;k++) {
      auxv = strcmp(votos[i].governador,candidato[k].numero);
      auxv2 = strcmp("G",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
      auxexiste = auxexiste +1;
     }
}



for (k=0;k<360;k++) {
     auxv = strcmp(votos[i].governador,candidato[k].numero);
     auxv2 = strcmp("G",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em:");
    printf("- Nome: %s",candidato[k].nome);
    printf("- PARTIDO: %s",candidato[k].partido);
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
         scanf("%s",votos[i].governador);
         auxv = strcmp(votos[i].governador,"r");
         auxv2 = strcmp(votos[i].governador,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
  } else {
    quantvotos[k].quantvotos = quantvotos[k].quantvotos+1;
    }
 }
}

auxv = strcmp(votos[i].governador,"b");
auxv2 = strcmp(votos[i].governador,"B");
if ((auxexiste == 0) && (auxv != 0) && (auxv2 != 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta ANULANDO seu voto:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].governador);
         auxv = strcmp(votos[i].governador,"r");
         auxv2 = strcmp(votos[i].governador,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1; 
        } else {
        nuloG = nuloG+1;
    }
}

// branco
auxv = strcmp(votos[i].governador,"b");
auxv2 = strcmp(votos[i].governador,"B");
if ((auxv == 0 || auxv2 == 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em BRANCO:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].governador);
         auxv = strcmp(votos[i].governador,"r");
         auxv2 = strcmp(votos[i].governador,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    } else {
        brancoG = brancoG+1;
    }
  }
}  

//-------------------------------------------------------------------------------------------------------------------------------------------
//registrando quarto voto presidente
//resetando váriavéis úteis.
auxexiste = 0;
for (auxrefaz = 0; auxrefaz <1; auxrefaz++) { //caso o eleitor queira refazer o contador será resetado para 0 e a votação irá repetir
printf("########################################################");
printf("################# URNA ELETRONICA #######################");
printf("########################################################");
printf("- VOTE PARA PRESIDENTE:");

scanf("%s",votos[i].presidente);

for (k=0;k<360;k++) {
      auxv = strcmp(votos[i].presidente,candidato[k].numero);
      auxv2 = strcmp("P",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
      auxexiste = auxexiste +1;
     }
}


for (k=0;k<360;k++) {
    auxv = strcmp(votos[i].presidente,candidato[k].numero);
    auxv2 = strcmp("P",candidato[k].cargo);
     if (auxv == 0 && auxv2 == 0) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em:");
    printf("- Nome: %s",candidato[k].nome);
    printf("- PARTIDO: %s",candidato[k].partido);
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
         scanf("%s",votos[i].presidente);
         auxv = strcmp(votos[i].presidente,"r");
         auxv2 = strcmp(votos[i].presidente,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    } else {
    quantvotos[k].quantvotos = quantvotos[k].quantvotos+1;
    }
  }
}

auxv = strcmp(votos[i].presidente,"b");
auxv2 = strcmp(votos[i].presidente,"B");
if ((auxexiste == 0) && (auxv != 0) && (auxv2 != 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta ANULANDO seu voto:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].presidente);
         auxv = strcmp(votos[i].presidente,"r");
         auxv2 = strcmp(votos[i].presidente,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    } else {
        nuloP = nuloP+1;
    }
}

// branco
auxv = strcmp(votos[i].presidente,"b");
auxv2 = strcmp(votos[i].presidente,"B");
if ((auxv == 0 || auxv2 == 0)) {
    printf("########################################################");
    printf("################# URNA ELETRONICA #######################");
    printf("########################################################");
    printf("- Voce esta votando em BRANCO:");
    printf("- Confirmar (c ou C) ou Corrigir (r ou R)?");
    scanf("%s",votos[i].presidente);
         auxv = strcmp(votos[i].presidente,"r");
         auxv2 = strcmp(votos[i].presidente,"R");
    if ((auxv == 0 || auxv2 == 0)) {
        auxrefaz = auxrefaz -1;
    } else {
        brancoP = brancoP+1;
    }
  }
} 

printf("########################################################");
printf("################# URNA ELETRONICA #######################");
printf("########################################################");
printf("- VOTO REGISTRADO COM SUCESSO");
printf("- Deseja registrar um novo voto (n ou N) ou finalizar (f ou F) a votação?\n");
presentes = presentes +1;
scanf ("%s", finalizador);
 auxv = strcmp("f",finalizador);
 auxv2 = strcmp("F",finalizador);
if (auxv == 0 || auxv2 == 0) {
    break; // ta errado vou tentar la em cima
    
}

//NOVO VOTO OU FINALIZAÇÃO---------------------------------------------------------------------------------------------------------------
   }
 }
}//TUDO DENTRO DO for

//FIM DA VOTAÇÃO ---------------------------------------------------------------------------------------------------------------------


// GERANDO O BOLETIM
strcpy(argumento,"\0");
sprintf(argumento, "%s/boletim.csv", argv[2]);

FILE *boletim;
    boletim = fopen(argumento, "w");
fprintf(boletim,"CANDIDATO,PARTIDO,VOTOS\n");

for(k=0; k<360; k++) {
    auxv = strcmp("P", candidato[k].cargo);
    if (auxv == 0) {
        fprintf(boletim,"%s,%s,%.0f (%.2f%%)\n", candidato[k].nome,candidato[k].partido,quantvotos[k].quantvotos,(quantvotos[k].quantvotos/presentes)*100);

    }
}

fprintf (boletim,"BRANCOS E NULOS,-,%0.f (%.2f%%)\n", brancoP+nuloP,((brancoP+nuloP)/presentes)*100);
fprintf (boletim, "-,-,-\n");        

//------------------------------------------------------------------------------------------------------------------------------------------------

for(k=0; k<360; k++) {
    auxv = strcmp("G", candidato[k].cargo);
    if (auxv == 0) {
        fprintf(boletim,"%s,%s,%.0f (%.2f%%)\n", candidato[k].nome,candidato[k].partido,quantvotos[k].quantvotos,(quantvotos[k].quantvotos/presentes)*100);

    }
  }
 
 fprintf (boletim,"BRANCOS E NULOS,-,%0.f (%.2f%%)\n", brancoG+nuloG,((brancoG+nuloG)/presentes)*100);
 fprintf (boletim, "-,-,-\n");

//------------------------------------------------------------------------------------------------------------------------------------------------

for(k=0; k<360; k++) {
    auxv = strcmp("F", candidato[k].cargo);
    if (auxv == 0) {
       fprintf(boletim,"%s,%s,%.0f (%.2f%%)\n", candidato[k].nome,candidato[k].partido,quantvotos[k].quantvotos,(quantvotos[k].quantvotos/presentes)*100);
        
    }
}

fprintf (boletim,"BRANCOS E NULOS,-,%0.f (%.2f%%)\n", brancoF+nuloF,((brancoF+nuloF)/presentes)*100);
fprintf (boletim, "-,-,-\n");

//------------------------------------------------------------------------------------------------------------------------------------------------

for(k=0; k<360; k++) {
    auxv = strcmp("E", candidato[k].cargo);
    if (auxv == 0) {
        fprintf(boletim,"%s,%s,%.0f (%.2f%%)\n", candidato[k].nome,candidato[k].partido,quantvotos[k].quantvotos,(quantvotos[k].quantvotos/presentes)*100);

    }
}

fprintf (boletim,"BRANCOS E NULOS,-,%0.f (%.2f%%)\n", brancoE+nuloE,((brancoE+nuloE)/presentes)*100);
fprintf (boletim, "-,-,-\n");
fprintf (boletim,"TOTAL DE ELEITORES,-,%0.f (100.0%%)\n", quantlinhaelei());
fprintf (boletim,"ELEITORES PRESENTES,-, %0.f (%.2f%%)\n",presentes,(presentes/quantlinhaelei())*100);
fprintf (boletim,"ELEITORES AUSENTES,-, %0.f (%.2f%%)\n",quantlinhaelei()-presentes,((quantlinhaelei()-presentes)/quantlinhaelei())*100);

fclose(boletim);
//DIVISÃO DE VAGAS LEGISLATIVO-------------------------------------------------------------------------------------------------------------------------

//SOMAR TOTAL DE VOTOS--------------------------------------------------------------------------------------------------------------------------------------------
float somatotal;
somatotal = 0;
for (auxv2 =0; auxv2 < 10; auxv2 ++) {
  for(k=0; k<360; k++) {
    
    auxv = strcmp(partido[auxv2].sigla, candidato[k].partido);
    auxv3 = strcmp("E", candidato[k].cargo);
   if (auxv == 0 && auxv3 ==0) {
    partido[auxv2].quantvotospart = partido[auxv2].quantvotospart + quantvotos[k].quantvotos;
   }
  }
 somatotal =  somatotal + partido[auxv2].quantvotospart;
 }


// ORDENAR PARTIDOS POR ORDEM DE MAIOR QUANTIDADE DE VOTOS;

for(k=9; k>0; k--) {
        for(int i=0; i<k; i++) {
            if (partido[i].quantvotospart < partido[i+1].quantvotospart) {
                
                auxv = partido[i+1].quantvotospart;
                partido[i+1].quantvotospart = partido[i].quantvotospart;
                partido[i].quantvotospart = auxv;

                strcpy(auxs,partido[i+1].nome);
                strcpy(partido[i+1].nome,partido[i].nome);
                strcpy(partido[i].nome,auxs);

                strcpy(auxs,partido[i+1].sigla);
                strcpy(partido[i+1].sigla,partido[i].sigla);
                strcpy(partido[i].sigla,auxs);
                
                strcpy(auxs,partido[i+1].numero);
                strcpy(partido[i+1].numero,partido[i].numero);
                strcpy(partido[i].numero,auxs);
            }
        }
    }

//DEFINIR QUANTAS VAGAS CADA PARTIDO VAI TER DIREITO ESTADUAL
auxv =10;

for (k =0; k < 10; k ++) {
    if (auxv > 0) { //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    partido[k].quantvagase = 10*(partido[k].quantvotospart/somatotal); // sempre menor que 10;
    auxv2 = partido[k].quantvagase; //pegando somente a parte inteira
    partido[k].quantvagase = partido[k].quantvagase-auxv2; // pegando a parte decimal entre 0 e 0.99
    if (partido[k].quantvagase >= 0.5) {
        auxv2 = auxv2+1;
  }
   partido[k].quantvagase = auxv2;
   if ((auxv-partido[k].quantvagase) < 0) {
    auxv2 = auxv2-1;
    partido[k].quantvagase = auxv2;
    break;
   }
   auxv = auxv - partido[k].quantvagase;
   
 }
}

strcpy(argumento,"\0");
sprintf(argumento, "%s/bancada_deputado_estadual.csv", argv[2]);

FILE *bancada_deputado_estadual;
    bancada_deputado_estadual = fopen(argumento, "w");

fprintf(bancada_deputado_estadual,"Partido,Eleitos\n");

for (k=0; k<quantlinhapar() ;k++) {
    fprintf(bancada_deputado_estadual, "%s,%0.f\n",partido[k].sigla,partido[k].quantvagase);
}
fclose(bancada_deputado_estadual);

// --------------------------------------------------------------------------------------------------------------------------------------------
//DEFINIR QUANTAS VAGAS CADA PARTIDO VAI TER DIREITO FEDERAL

somatotal = 0;
for(k=0; k<10; k++) {
 partido[k].quantvotospart=0;
}
for (auxv2 =0; auxv2 < 10; auxv2 ++) {
  for(k=0; k<360; k++) {
    
    auxv = strcmp(partido[auxv2].sigla, candidato[k].partido);
    auxv3 = strcmp("F", candidato[k].cargo);
   if (auxv == 0 && auxv3 ==0) {
    partido[auxv2].quantvotospart = partido[auxv2].quantvotospart + quantvotos[k].quantvotos;
   }
  }

 somatotal =  somatotal + partido[auxv2].quantvotospart;
 }
// ORDENAR PARTIDOS POR ORDEM DE MAIOR QUANTIDADE DE VOTOS; utilizando o bubble sort dnv pra ordenar em relação aos votos do federal;

for(k=9; k>0; k--) {
        for(int i=0; i<k; i++) {
            if (partido[i].quantvotospart < partido[i+1].quantvotospart) {
                
                auxv = partido[i+1].quantvagasf;
                partido[i+1].quantvagasf = partido[i].quantvagasf;
                partido[i].quantvagasf = auxv;

                auxv = partido[i+1].quantvagase;
                partido[i+1].quantvagase = partido[i].quantvagase;
                partido[i].quantvagase = auxv;

                auxv = partido[i+1].quantvotospart;
                partido[i+1].quantvotospart = partido[i].quantvotospart;
                partido[i].quantvotospart = auxv;

                strcpy(auxs,partido[i+1].nome);
                strcpy(partido[i+1].nome,partido[i].nome);
                strcpy(partido[i].nome,auxs);

                strcpy(auxs,partido[i+1].sigla);
                strcpy(partido[i+1].sigla,partido[i].sigla);
                strcpy(partido[i].sigla,auxs);
                
                strcpy(auxs,partido[i+1].numero);
                strcpy(partido[i+1].numero,partido[i].numero);
                strcpy(partido[i].numero,auxs);
            }
        }
    }

//DEFINIR QUANTAS VAGAS CADA PARTIDO VAI TER DIREITO FEDERAL


auxv =5;
for (k =0; k < 5; k ++) { 
    partido[k].quantvagasf = 5*(partido[k].quantvotospart/somatotal); // sempre menor que 10;
    auxv2 = partido[k].quantvagasf; //aux2 é a parte inteira
    partido[k].quantvagasf = partido[k].quantvagasf-auxv2; //vira a parte real entre 0 e 0.99
    if (partido[k].quantvagasf >= 0.5) {
        auxv2 = auxv2+1;
  }
   partido[k].quantvagasf = auxv2;
   if ((auxv-partido[k].quantvagasf) < 0) {
    auxv2 = auxv2-1;
    partido[k].quantvagasf = auxv2;
    break;
   }
   auxv = auxv - partido[k].quantvagasf;
   
 }

  
strcpy(argumento,"\0");
sprintf(argumento, "%s/bancada_deputado_federal.csv", argv[2]);
FILE *bancada_deputado_federal;
    bancada_deputado_federal = fopen(argumento, "w");

fprintf(bancada_deputado_federal,"Partido,Eleitos\n");

for (k=0; k<quantlinhapar() ;k++) {
    fprintf(bancada_deputado_federal, "%s,%0.f\n",partido[k].sigla,partido[k].quantvagasf);
}

fclose(bancada_deputado_federal);

// GERANDO OS RANKINGS ------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------- 
tranking ranking[150];



int aux;
auxv2 = 0;
aux = 0; // posso usar auxv3 aqui.
for(k=0; k<320; k++) {          //armazenar somente os presidentes na nova struct para ordenar e gerar o arquivo ranking;
   auxv = strcmp("P", candidato[k].cargo);
   if (auxv ==0) {
    strcpy(ranking[auxv2].nome,candidato[k].nome);
    strcpy(ranking[auxv2].genero,candidato[k].genero);
    ranking[auxv2].idade = candidato[k].idade;
    strcpy(ranking[auxv2].cargo,candidato[k].cargo);
    strcpy(ranking[auxv2].numero,candidato[k].numero);
    strcpy(ranking[auxv2].partido,candidato[k].partido);
    ranking[auxv2].quantvotos = quantvotos[k].quantvotos;
    auxv2 = auxv2+1;
   }
}

 
    for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if (ranking[k].quantvotos < ranking[k+1].quantvotos) {
                
                auxv = partido[i+1].quantvagasf;
                partido[i+1].quantvagasf = partido[i].quantvagasf;
                partido[i].quantvagasf = auxv;

                auxv = partido[i+1].quantvagase;
                partido[i+1].quantvagase = partido[i].quantvagase;
                partido[i].quantvagase = auxv;

                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);


            }
        }
    }
     for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if ((ranking[k].quantvotos == ranking[k+1].quantvotos) && (strcmp(ranking[k].nome,ranking[k+1].nome)) > 0) { 
                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);
            
           

            }
        }
    }
strcpy(argumento,"\0");
sprintf(argumento, "%s/ranking_presidente.csv", argv[2]);

FILE *ranking_presidente; //pode ser qualquer coisa aqui?
    ranking_presidente = fopen(argumento, "w");

fprintf(ranking_presidente,"NOME,PARTIDO,VOTOS,PERCENTUAL\n");
for(k=0; k<auxv2; k++) {
    if (ranking[k].quantvotos != 0) {
    fprintf(ranking_presidente,"%s,%s,%.0f,%.2f%%\n", ranking[k].nome,ranking[k].partido,ranking[k].quantvotos,(ranking[k].quantvotos/(presentes-brancoP-nuloP))*100);
  }
 }
 fclose (ranking_presidente);
//GERANDO OS ELEITOS---------------------------------------------------------------------------------------------------------------------------
strcpy(argumento,"\0");
sprintf(argumento, "%s/eleitos.csv", argv[2]);
FILE *eleitos;
    eleitos = fopen(argumento, "w");

fprintf(eleitos,"CARGO,NOME,PARTIDO\n");
fprintf(eleitos,"PRESIDENTE,%s,%s\n", ranking[0].nome,ranking[0].partido);
//GERANDO ARQUIVO IDADE---------------------------------------------------------------------------------------------------------------------------

idadep = ranking[0].idade;

//------------------------------------------------------------------------------------------------------------------------------------------------




auxv2 = 0;
aux = 0;
for(k=0; k<320; k++) {          //armazenar somente os governadores na nova struct para ordenar e gerar o arquivo ranking;
   auxv = strcmp("G", candidato[k].cargo);
   if (auxv ==0) {
    strcpy(ranking[auxv2].nome,candidato[k].nome);
    strcpy(ranking[auxv2].genero,candidato[k].genero);
    ranking[auxv2].idade = candidato[k].idade;
    strcpy(ranking[auxv2].cargo,candidato[k].cargo);
    strcpy(ranking[auxv2].numero,candidato[k].numero);
    strcpy(ranking[auxv2].partido,candidato[k].partido);
    ranking[auxv2].quantvotos = quantvotos[k].quantvotos;
    auxv2 = auxv2+1;
   }
}

    for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if (ranking[k].quantvotos < ranking[k+1].quantvotos) {
                
                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);


            }
        }
    }

     for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if ((ranking[k].quantvotos == ranking[k+1].quantvotos) && (strcmp(ranking[k].nome,ranking[k+1].nome)) > 0) { 
                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);
            
           

            }
        }
    }
strcpy(argumento2,"\0");
sprintf(argumento2, "%s/ranking_governador.csv", argv[2]); //usando o argumento2 por que o eleitores ainda está aberto e não posso redefirir a saída
FILE *ranking_governador;
    ranking_governador = fopen(argumento2, "w");

fprintf(ranking_governador,"NOME,PARTIDO,VOTOS,PERCENTUAL\n");
for(k=0; k<auxv2; k++) {
    if (ranking[k].quantvotos != 0) {
    fprintf(ranking_governador,"%s,%s,%.0f,%.2f%%\n", ranking[k].nome,ranking[k].partido,ranking[k].quantvotos,(ranking[k].quantvotos/(presentes-brancoG-nuloG))*100);
   }
 }
 fclose(ranking_governador);
//GERANDO OS ELEITOS---------------------------------------------------------------------------------------------------------------------------

fprintf(eleitos,"GOVERNADOR,%s,%s\n", ranking[0].nome,ranking[0].partido);

//GERANDO ARQUIVO IDADE---------------------------------------------------------------------------------------------------------------------------

idadeg = ranking[0].idade;

//------------------------------------------------------------------------------------------------------------------------------------------------


auxv2 = 0;
aux = 0;
for(k=0; k<320; k++) {         
   auxv = strcmp("F", candidato[k].cargo); // só federais
   if (auxv ==0) {
    strcpy(ranking[auxv2].nome,candidato[k].nome);
    strcpy(ranking[auxv2].genero,candidato[k].genero);
    ranking[auxv2].idade = candidato[k].idade;
    strcpy(ranking[auxv2].cargo,candidato[k].cargo);
    strcpy(ranking[auxv2].numero,candidato[k].numero);
    strcpy(ranking[auxv2].partido,candidato[k].partido);
    ranking[auxv2].quantvotos = quantvotos[k].quantvotos;
    auxv2 = auxv2+1;
   }
}

    for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if (ranking[k].quantvotos < ranking[k+1].quantvotos) {
                
                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);


            }
        }
    }
    // coloca em ordem alfabética se os votos forem iguais 
    for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if ((ranking[k].quantvotos == ranking[k+1].quantvotos) && (strcmp(ranking[k].nome,ranking[k+1].nome)) > 0) { 
                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);
            
           

            }
        }
    }
strcpy(argumento2,"\0");
sprintf(argumento2, "%s/ranking_deputado_federal.csv", argv[2]);
FILE *ranking_deputado_federal;
    ranking_deputado_federal = fopen(argumento2, "w");

fprintf(ranking_deputado_federal,"NOME,PARTIDO,VOTOS,PERCENTUAL\n");
for(k=0; k<auxv2; k++) {
    if (ranking[k].quantvotos != 0) {
    fprintf(ranking_deputado_federal,"%s,%s,%.0f,%.2f%%\n", ranking[k].nome,ranking[k].partido,ranking[k].quantvotos,(ranking[k].quantvotos/(presentes-brancoF-nuloF))*100);
   }
 }
 fclose(ranking_deputado_federal);
 //GERANDO OS ELEITOS---------------------------------------------------------------------------------------------------------------------------
for(k=0; k<150; k++) { // tive que colocar a mais pra ir até o final da lista pois o break tava fazendo estourar antes de completar as vagas.
   for (i=0; i<10; i++) {
    auxv = strcmp(partido[i].sigla, ranking[k].partido);
    if(auxv ==0) {
        auxv = k; //para percorrer o ranking procurando os eleitos sem variar no k e atrapalhar a aleição do próximo eleito;
    while (partido[i].quantvagasf > 0) {
    fprintf(eleitos,"DEPUTADO FEDERAL,%s,%s\n", ranking[auxv].nome,ranking[auxv].partido);
    partido[i].quantvagasf = partido[i].quantvagasf - 1; //retira uma vaga linkada ao partido
          
     // aqui vai entrar o arquivo genero e o idade por que eu me desatentei na hora de preencher essas vagas e esses arquivos estavam pegando só seguindo o ranking.
        auxv3 = strcmp(ranking[auxv].genero,"M");
        if (auxv3 == 0) {
        m = m+1; 
        }
        auxv3 = strcmp(ranking[auxv].genero,"F");
        if (auxv3 == 0) {
        f = f+1;
       }    
        auxv3 = strcmp(ranking[auxv].genero,"O");
        if (auxv3 == 0) {
        o = o+1;
       }

       idadef = idadef + ranking[auxv].idade;
    // fim dos arquivos genero e idade.  
    
     
      auxv2 = strcmp(partido[i].sigla,ranking[aux+1].partido);// se sobrar vaga do anterior, só vai printar caso o próx da lista seja do mesmo partido.
      if(auxv2 != 0) {
      break; // sai do while caso não seja do mesmo partido que está sobrando vagas;
      } else {
        auxv = auxv +1;
        }
     }
   }
 }
}


//------------------------------------------------------------------------------------------------------------------------------------------------


auxv2 = 0;
aux = 0;
for(k=0; k<320; k++) {          //armazenar somente os estaduais na nova struct para ordenar e gerar o arquivo ranking;
   auxv = strcmp("E", candidato[k].cargo);
   if (auxv ==0) {
    strcpy(ranking[auxv2].nome,candidato[k].nome);
    strcpy(ranking[auxv2].genero,candidato[k].genero);
    ranking[auxv2].idade = candidato[k].idade;
    strcpy(ranking[auxv2].cargo,candidato[k].cargo);
    strcpy(ranking[auxv2].numero,candidato[k].numero);
    strcpy(ranking[auxv2].partido,candidato[k].partido);
    ranking[auxv2].quantvotos = quantvotos[k].quantvotos;
    auxv2 = auxv2+1;
   }
}

    for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if (ranking[k].quantvotos < ranking[k+1].quantvotos) {
                
                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);


            }
        }
    } 
      for(int posFim=auxv2-1; posFim>0; posFim--) {
        for(int k=0; k<posFim; k++) {
            if ((ranking[k].quantvotos == ranking[k+1].quantvotos) && (strcmp(ranking[k].nome,ranking[k+1].nome)) > 0) { 
                aux = ranking[k+1].quantvotos;
                ranking[k+1].quantvotos = ranking[k].quantvotos;
                ranking[k].quantvotos = aux;
                
                aux = ranking[k+1].idade;
                ranking[k+1].idade = ranking[k].idade;
                ranking[k].idade = aux;
                
                strcpy(auxs,ranking[k+1].nome);
                strcpy(ranking[k+1].nome,ranking[k].nome);
                strcpy(ranking[k].nome,auxs);

                strcpy(auxs,ranking[k+1].genero);
                strcpy(ranking[k+1].genero,ranking[k].genero);
                strcpy(ranking[k].genero,auxs);

                strcpy(auxs,ranking[k+1].cargo);
                strcpy(ranking[k+1].cargo,ranking[k].cargo);
                strcpy(ranking[k].cargo,auxs);

                strcpy(auxs,ranking[k+1].numero);
                strcpy(ranking[k+1].numero,ranking[k].numero);
                strcpy(ranking[k].numero,auxs);

                strcpy(auxs,ranking[k+1].partido);
                strcpy(ranking[k+1].partido,ranking[k].partido);
                strcpy(ranking[k].partido,auxs);
            
           

            }
        }
    }
strcpy(argumento2,"\0");
sprintf(argumento2, "%s/ranking_deputado_estadual.csv", argv[2]);
FILE *ranking_deputado_estadual;
    ranking_deputado_estadual = fopen(argumento2, "w");

fprintf(ranking_deputado_estadual,"NOME,PARTIDO,VOTOS,PERCENTUAL\n");

for(k=0; k<auxv2; k++) {
    if (ranking[k].quantvotos != 0) {
    fprintf(ranking_deputado_estadual,"%s,%s,%.0f,%.2f%%\n", ranking[k].nome,ranking[k].partido,ranking[k].quantvotos,(ranking[k].quantvotos/(presentes-brancoE-nuloE))*100);
   }
  }
  fclose(ranking_deputado_estadual);
 //GERANDO OS ELEITOS---------------------------------------------------------------------------------------------------------------------------

for(k=0; k<150; k++) { // tive que colocar a mais pra ir até o final da lista pois o break tava fazendo estourar antes de completar as vagas.
   for (i=0; i<10; i++) {
    auxv = strcmp(partido[i].sigla, ranking[k].partido);
    if(auxv ==0) {
        auxv = k; //para percorrer o ranking procurando os eleitos sem variar no k e atrapalhar a aleição do próx;
    while (partido[i].quantvagase > 0) {
    fprintf(eleitos,"DEPUTADO ESTADUAL,%s,%s\n", ranking[auxv].nome,ranking[auxv].partido);
      partido[i].quantvagase = partido[i].quantvagase - 1; //retira uma vaga linkada ao partido
     
     // aqui vai entrar o arquivo genero e o idade por que eu me desatentei na hora de preencher essas vagas e esses arquivos estavam pegando só seguindo o ranking.
        auxv3 = strcmp(ranking[auxv].genero,"M");
        if (auxv3 == 0) {
        m = m+1; 
        }
        auxv3 = strcmp(ranking[auxv].genero,"F");
        if (auxv3 == 0) {
        f = f+1;
       }    
        auxv3 = strcmp(ranking[auxv].genero,"O");
        if (auxv3 == 0) {
        o = o+1;
       }

       idadee = idadee + ranking[auxv].idade;
    // fim dos arquivos genero e idade.  
    
      auxv2 = strcmp(partido[i].sigla,ranking[aux+1].partido);// se sobrar vaga do anterior, só vai printar caso o próx da lista seja do mesmo partido.
      if(auxv2 != 0) {
      break; // sai do while caso não seja do mesmo partido que está sobrando vagas;
      } else {
        auxv = auxv +1;
        }
     }
   }
 }
}

//------------------------------------------------------------------------------------------------------------------------------------------------
strcpy(argumento2,"\0");
sprintf(argumento2, "%s/genero_legislativo.csv", argv[2]);

FILE *genero_legislativo;
    genero_legislativo = fopen(argumento2, "w");

fprintf(genero_legislativo,"GENERO,PERCENTUAL\n");
fprintf(genero_legislativo,"M,%0.f%%\n", (m/(m+f+o))*100);
fprintf(genero_legislativo,"F,%0.f%%\n", (f/(m+f+o))*100);
fprintf(genero_legislativo,"O,%0.f%%\n", (o/(m+f+o))*100);
 
fclose(genero_legislativo);

//------------------------------------------------------------------------------------------------------------------------------------------------
strcpy(argumento2,"\0");
sprintf(argumento2, "%s/media_idade.csv", argv[2]);

FILE *media_idade;
    media_idade = fopen(argumento2, "w");

fprintf(media_idade,"CARGO,MEDIA\n");
fprintf(media_idade,"DEPUTADO ESTADUAL,%.2f\n",idadee/10);
fprintf(media_idade,"DEPUTADO FEDERAL,%.2f\n",idadef/5);
fprintf(media_idade,"GOVERNADOR,%.2f\n",idadeg);
fprintf(media_idade,"PRESIDENTE,%.2f\n",idadep);


fclose(media_idade);



//------------------------------------------------------------------------------------------------------------------------------------------------


//CRITÉRIOS DE DESEMPATE; falta partidos;
return 0;
}


