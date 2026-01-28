#include "paciente.h"
#include "dadospaciente.h"
#include "lesoes.h"
#include "data.h"
#include <math.h>
#include <ctype.h>

struct paciente {
    char nome[100];
    char sus[19];
    char data[11];
    char telefone[18];
    char endereco[200];
    char genero[10];
    tdadospaciente *dados;
    tlesao **lesoes;
    int qntlesoes;
};

void upper_baguic (char *bagui) {
    char aux;
    int i=0;
    while (bagui[i] != '\0') {
        aux = toupper (bagui[i]);
        bagui[i] = aux;
        i++;
    }
}

tpaciente *cria_paciente () {
    tpaciente *paciente;    
    paciente = (tpaciente*) malloc (sizeof(tpaciente));
    
    paciente->lesoes = criar_lista_lesao();

    paciente->dados = cria_dados_paciente();

    paciente->qntlesoes = 0;
    return paciente; 
}


void free_paciente (tpaciente *paciente) {
    free_lesao_lista(paciente->lesoes, paciente->qntlesoes); 
    free_dados(paciente->dados);
    free(paciente);
}


void atribui_paciente (tpaciente *paciente, char *nome, char *sus, char *data, char *telefone,char *endereco ,char *genero) {
strcpy(paciente->nome,nome);
upper_baguic(paciente->nome);

strcpy(paciente->sus,sus);
strcpy(paciente->data,data);
strcpy(paciente->telefone,telefone);

strcpy(paciente->endereco,endereco);
upper_baguic(paciente->endereco);

strcpy(paciente->genero,genero);
upper_baguic(paciente->genero);
paciente->qntlesoes = 0;
}

void ler_paciente (tpaciente *paciente) {
    printf("paciente:\n");
    scanf("\n%100[^\n]",paciente->nome);
    scanf("\n%s",paciente->sus);
    scanf("\n%s",paciente->data);
    scanf("\n%s",paciente->telefone);
    scanf("\n%200[^\n]",paciente->endereco);
    scanf("\n%s",paciente->genero);
    upper_baguic(paciente->genero);

    paciente->qntlesoes = 0;        
}


void print_paciente (tpaciente *paciente, FILE *path) {
    
    fprintf(path,"NOME: %s\n",paciente->nome);
    fprintf(path,"DATA DE NASCIMENTO: %s (%i ANOS)\n",paciente->data,calcular_idade(paciente->data,retorna_data(paciente->dados)));
    fprintf(path,"GENERO: %s\n",paciente->genero);
    fprintf(path,"TELEFONE: %s\n",paciente->telefone);
    fprintf(path,"ENDERECO: %s\n",paciente->endereco);
    //fprintf(path,"\n");
    
}

void atribui_dados_paciente (tpaciente *paciente) {
    ler_dados(paciente->dados);
}

int encontra_paciente (char *sus, tpaciente *paciente) {
    if (strcmp(sus,paciente->sus) == 0) {
        return 1;
    }
    return 0;
}




void atribui_lesoes_paciente (tpaciente *paciente, int qnt_les_cadastradas,char *nome_lesao) {
    paciente->lesoes = (tlesao**) realloc(paciente->lesoes, sizeof(tlesao*) * (paciente->qntlesoes + 1));
    paciente->lesoes[paciente->qntlesoes] = adicionar_lesao_lista(paciente->qntlesoes,nome_lesao);
    paciente->qntlesoes++;
}



void gera_log (tpaciente *paciente, char *argv1, int qnt_atendimentos) {
    char path[100];
    sprintf(path, "%s/logs/log_%d", argv1,qnt_atendimentos);
    FILE *log;
    log = fopen(path,"w");
    fprintf(log,"%s\n",paciente->sus);
    fprintf(log,"%s\n",retorna_data(paciente->dados));
    for (int i=0; i<paciente->qntlesoes;i++) {
        fprintf(log,"%s\n",retorna_rotulo(paciente->lesoes,i));
    }
    fclose(log);
}


int qnt_cirur_paciente (tpaciente *paciente) {
int total;
    total = calc_qnt_cirur(paciente->lesoes,paciente->qntlesoes);
return total;
}

int qnt_crio_paciente (tpaciente *paciente) {
int total;
    total = calc_qnt_crio(paciente->lesoes,paciente->qntlesoes);
return total;
}

int tam_total_lesoes_pac (tpaciente *paciente) {
    int total;
    total = soma_tam_lesoes (paciente->lesoes, paciente->qntlesoes);
    return total;
}


void print_descricoes_lista (tpaciente *paciente ,int qnt_lesoes_paciente, FILE *path) {
for (int i=0; i<qnt_lesoes_paciente; i++) {
    print_descricao_lesao(paciente->lesoes[i],path);
    }
}

void print_busca_paciente (tpaciente *paciente,char *argv1) {
    char path[100];
    sprintf(path, "%s/buscas/busca_%s", argv1,paciente->sus);
    FILE *busca;
    busca = fopen(path,"w");
    print_paciente(paciente,busca);
    
if (retorna_flag(paciente->dados) == 1) {
    print_dados_paciente(paciente->dados,busca);
    
    fprintf(busca,"LESOES:\n");
    fprintf(busca,"TOTAL: %d\n",paciente->qntlesoes);
    fprintf(busca,"ENVIADA PARA CIRURGIA: %d\n", calc_qnt_cirur(paciente->lesoes,paciente->qntlesoes));
    fprintf(busca,"ENVIADA PARA CRIOTERAPIA: %d\n", calc_qnt_crio(paciente->lesoes,paciente->qntlesoes));
    
    
    if (paciente->lesoes[0] != NULL) {
    fprintf(busca,"\nDESCRICAO DAS LESOES:\n"); 
    print_descricoes_lista(paciente,paciente->qntlesoes,busca);
    }
}
    fclose(busca);
}

// relatório.

void media_idade (tpaciente **pacientes, int qnt_pac_cadas,FILE *path) {
int total = 0;
    for (int i=0; i< qnt_pac_cadas; i++) {
        total = total + (calcular_idade(pacientes[i]->data,retorna_data(pacientes[i]->dados)));
        }
int media = total/qnt_pac_cadas;        
    

    
int somatorio_diferencas=0;
    for (int i=0; i< qnt_pac_cadas; i++) {
        somatorio_diferencas = somatorio_diferencas + ((calcular_idade(pacientes[i]->data,retorna_data(pacientes[i]->dados))-media)*(calcular_idade(pacientes[i]->data,retorna_data(pacientes[i]->dados))-media));
        }
int desvio = 0;
    desvio = sqrt(somatorio_diferencas/qnt_pac_cadas);
    
    fprintf(path,"IDADE MEDIA: %d +- %d ANOS\n",media,desvio);        
}

void distribuicao_genero (tpaciente **pacientes, int qnt_pac_cadas,FILE *path) {
float totalMAS = 0;
float totalFEM = 0;
float totalOUT = 0;
    for (int i=0; i< qnt_pac_cadas; i++) {
        if (strcmp(pacientes[i]->genero,"MASCULINO")==0){
            totalMAS++; 
          }
        }  
    for (int i=0; i< qnt_pac_cadas; i++) {
        if (strcmp(pacientes[i]->genero,"FEMININO")==0){
            totalFEM++;
          }
        } 
    for (int i=0; i< qnt_pac_cadas; i++) {
        if (strcmp(pacientes[i]->genero,"OUTROS")==0){
            totalOUT++; 
          }
        }
    
    int TOTAL = totalFEM+totalMAS+totalOUT; 
      
    fprintf(path,"DISTRIBUICAO POR GENERO:\n");
    fprintf(path," - FEMININO: %.2f%%\n",(totalFEM/TOTAL)*100);
    fprintf(path," - MASCULINO: %.2f%%\n",(totalMAS/TOTAL)*100);
    fprintf(path," - OUTROS: %.2f%%\n",(totalOUT/TOTAL)*100);             
}


void media_total_lesoes (tpaciente **pacientes, int qnt_pac_cadas, int qnt_lesoes_cadas,FILE *path) {
int total = 0,somatorio = 0;
if (qnt_lesoes_cadas == 0) {
    qnt_lesoes_cadas = 1; //testar se não vai mudar outros casos;
}
    for (int i=0; i< qnt_pac_cadas; i++) {
        total = total + (tam_total_lesoes_pac(pacientes[i]));
        }

int media = total/qnt_lesoes_cadas;

    for (int i=0; i< qnt_pac_cadas; i++) {
        somatorio = somatorio + (soma_desvio_lesao(pacientes[i]->lesoes,pacientes[i]->qntlesoes,media));
        }

float desvio = sqrt(somatorio/(qnt_lesoes_cadas));
    fprintf(path,"TAMANHO MEDIO DAS LESOES: %d +- %.0f MM\n",media,desvio);   
}


void total_cirur_crio (tpaciente **pacientes, int qnt_pac_cadastrado,int total_lesao_cadastrada,FILE *path) {
float totalcirur,totalcrio;
int flag = 0;
totalcirur=totalcrio=0;

        for (int i=0; i< qnt_pac_cadastrado; i++) {
            totalcirur = totalcirur + calc_qnt_cirur(pacientes[i]->lesoes,pacientes[i]->qntlesoes);
            totalcrio = totalcrio + calc_qnt_crio(pacientes[i]->lesoes,pacientes[i]->qntlesoes);
    }

   fprintf(path,"NUMERO TOTAL LESOES: %i\n",total_lesao_cadastrada);
   
if (total_lesao_cadastrada == 0) {
total_lesao_cadastrada = 1;
flag = 1; 
}
   fprintf(path,"NUMERO TOTAL DE CIRURGIAS: %.f (%.2f%%)\n", totalcirur ,(totalcirur/total_lesao_cadastrada)*100);
   fprintf(path,"NUMERO TOTAL DE CRIOTERAPIAS: %.f (%.2f%%)\n",totalcrio ,(totalcrio/total_lesao_cadastrada)*100);

if (total_lesao_cadastrada == 1 && flag == 1) {
total_lesao_cadastrada = 0; //para evitar problemas aleatórios;
flag = 0; 
}

}




void totais_tipos_lesoes (tpaciente **pacientes, int qnt_pac_cadastrado,FILE *path) {

float total,tceratoseact,tcarcibaso,tcarciespi,tnevo,tceratoseseb,tmelanoma,toutros;
total=tceratoseact=tcarcibaso=tcarciespi=tnevo=tceratoseseb=tmelanoma=toutros=0;
int flag; 
    for (int i=0; i< qnt_pac_cadastrado; i++) {
       tceratoseact = tceratoseact + compara_diagnostico("CERATOSE ACTINICA",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       tcarcibaso = tcarcibaso + compara_diagnostico("CARCINOMA BASOCELULAR",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       tcarciespi = tcarciespi + compara_diagnostico("CARCINOMA ESPINOCELULAR",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       tnevo = tnevo + compara_diagnostico("NEVO",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       tceratoseseb = tceratoseseb + compara_diagnostico("CERATOSE SEBORREICA",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       tmelanoma = tmelanoma + compara_diagnostico("MELANOMA",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       toutros = toutros + compara_diagnostico("OUTROS",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
    }
    total =  tcarcibaso + tcarciespi + tceratoseact +  tceratoseseb  + tnevo  + tmelanoma;

  fprintf(path,"DISTRIBUICAO POR DIAGNOSTICO:\n");
 
    for (int j=total; j >= 0; j--) {
        
    if (total == 0) {
    total = 1;
    flag = 1; 
    }

        if (tcarcibaso == j) {
           fprintf(path,"- CARCINOMA BASOCELULAR: %.f (%.2f%%)\n",tcarcibaso,(tcarcibaso/total)*100);
           
            }
        if (tcarciespi == j) {
           fprintf(path,"- CARCINOMA ESPINOCELULAR: %.f (%.2f%%)\n",tcarciespi,(tcarciespi/total)*100);
        }    
        if (tceratoseact == j) {
           fprintf(path,"- CERATOSE ACTINICA: %.f (%.2f%%)\n",tceratoseact,(tceratoseact/total)*100);
        }   
        if (tceratoseseb == j) {
           fprintf(path,"- CERATOSE SEBORREICA: %.f (%.2f%%)\n",tceratoseseb,(tceratoseseb/total)*100);
        }     
        if (tmelanoma == j) {
           fprintf(path,"- MELANOMA: %.f (%.2f%%)\n",tmelanoma,(tmelanoma/total*100));
        }
        if (tnevo == j) {
           fprintf(path,"- NEVO: %.f (%.2f%%)\n",tnevo,(tnevo/total*100));
        }
        if (tnevo == j) {
           fprintf(path,"- OUTROS: %.f (%.2f%%)\n",toutros,(toutros/total*100));
        }      

    if (total == 0 && flag == 1) {
    total = 0;
    flag = 0; //para evitar problemas aleatórios;
    }

    }
}


void gera_relatorio (tpaciente **pacientes, int qnt_pac_cadastrados,int qnt_les_cadastradas,char *argv1) {
    char path[100];
    sprintf(path, "%s/relatorio/relatorio_final", argv1);
    FILE *relatorio;
    relatorio = fopen(path,"w");

    fprintf(relatorio,"NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", qnt_pac_cadastrados);
    media_idade(pacientes,qnt_pac_cadastrados,relatorio);
    distribuicao_genero(pacientes,qnt_pac_cadastrados,relatorio);
    media_total_lesoes(pacientes,qnt_pac_cadastrados,qnt_les_cadastradas,relatorio);
    total_cirur_crio(pacientes,qnt_pac_cadastrados,qnt_les_cadastradas,relatorio);
    totais_tipos_lesoes(pacientes,qnt_pac_cadastrados,relatorio);
    totais_regioes(pacientes,qnt_pac_cadastrados,relatorio);


    fclose(relatorio);
}



void totais_regioes (tpaciente **pacientes, int qnt_pac_cadastrado,FILE *path) {

float total,face,abdome,antebraco,braco,canela,couro_cabeludo,coxa,dorso,mao,outros,orelha,pe,peitoral;
total=face=abdome=antebraco=braco=canela=couro_cabeludo=coxa=dorso=mao=outros=orelha=pe=peitoral=0;
int flag; 
    for (int i=0; i< qnt_pac_cadastrado; i++) {
       face = face + compara_regiao ("FACE",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       abdome = abdome + compara_regiao("ABDOME",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       antebraco = antebraco + compara_regiao("ANTEBRACO",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       braco = braco + compara_regiao("BRACO",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       canela = canela + compara_regiao("CANELA",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       couro_cabeludo= couro_cabeludo + compara_regiao("COURO CABELUDO",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       coxa = coxa + compara_regiao("COXA",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       dorso= dorso + compara_regiao("DORSO",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       mao = mao + compara_regiao("MAO",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       outros = outros + compara_regiao("OUTROS",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       orelha = orelha + compara_regiao("ORELHA",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       pe = pe + compara_regiao("PE",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
       peitoral = peitoral + compara_regiao("PEITORAL",pacientes[i]->lesoes,pacientes[i]->qntlesoes);
     
    }
    total =  face+abdome+antebraco+braco+canela+couro_cabeludo+coxa+dorso+mao+outros+orelha+pe+peitoral;

  fprintf(path,"DISTRIBUICAO POR REGIAO:\n");
 
    for (int j=total; j >= 0; j--) {
        
    if (total == 0) {
    total = 1;
    flag = 1; 
    }

        if (face == j) {
           fprintf(path,"- FACE: %.f (%.2f%%)\n",face,(face/total)*100);
           
            }
        if (abdome == j) {
           fprintf(path,"- ABDOME: %.f (%.2f%%)\n",abdome,(abdome/total)*100);
        }    
        if (antebraco == j) {
           fprintf(path,"- ANTEBRACO: %.f (%.2f%%)\n",antebraco,(antebraco/total)*100);
        }   
        if (braco == j) {
           fprintf(path,"- BRACO: %.f (%.2f%%)\n",braco,(braco/total)*100);
        }     
        if (canela == j) {
           fprintf(path,"- CANELA: %.f (%.2f%%)\n",canela,(canela/total*100));
        }
        if (couro_cabeludo == j) {
           fprintf(path,"- COURO CABELUDO: %.f (%.2f%%)\n",couro_cabeludo,(couro_cabeludo/total*100));
        }
        if (coxa == j) {
           fprintf(path,"- COXA: %.f (%.2f%%)\n",coxa,(coxa/total*100));
        }
        if (dorso == j) {
           fprintf(path,"- DORSO: %.f (%.2f%%)\n",dorso,(dorso/total*100));
        }  
        if (mao == j) {
           fprintf(path,"- MAO: %.f (%.2f%%)\n",mao,(mao/total*100));
        }
         if (orelha == j) {
           fprintf(path,"- ORELHA: %.f (%.2f%%)\n",orelha,(orelha/total*100));
        }    
        if (outros== j) {
           fprintf(path,"- OUTROS: %.f (%.2f%%)\n",outros,(outros/total*100));
        }  
        if (pe == j) {
           fprintf(path,"- PE: %.f (%.2f%%)\n",pe,(pe/total*100));
        }  
        if (peitoral == j) {
           fprintf(path,"- PEITORAL: %.f (%.2f%%)\n",peitoral,(peitoral/total*100));
        }        

    if (total == 0 && flag == 1) {
    total = 0;
    flag = 0; //para evitar problemas aleatórios;
    }

    }
}



int calc_qnt_cirur_lista (tpaciente **pacientes,int qnt_pac_cad) {   
int total =0;
for (int i=0; i< qnt_pac_cad; i++) {
    total = total +calc_qnt_cirur(pacientes[i]->lesoes,pacientes[i]->qntlesoes);
}
return total;
}

int calc_qnt_crio_lista (tpaciente **pacientes,int qnt_pac_cad) {   
int total =0;
for (int i=0; i< qnt_pac_cad; i++) {
    total = total + calc_qnt_crio(pacientes[i]->lesoes,pacientes[i]->qntlesoes);
}
return total;
}

// char path[100];
//     sprintf(path, "%s/buscas/busca_%s", argv1,paciente->sus);
//     FILE *busca;
//     busca = fopen(path,"w");
//     print_paciente(paciente,busca);



void gera_resumo (tpaciente **pacientes, int qnt_pac_cadastrados,int qnt_les_cadastradas,int qnt_cirurgias, int qnt_crioterapias,char *argv1) {
    char path[100];
    sprintf(path, "%s/resumo", argv1);
    FILE *resumo;
    resumo = fopen(path,"w");
    
    fprintf(resumo,"PACIENTES: %i\n",qnt_pac_cadastrados);
    fprintf(resumo,"LESOES: %i\n",qnt_les_cadastradas);
    fprintf(resumo,"CIRURGIAS: %i\n",qnt_cirurgias);
    fprintf(resumo,"CRIOTERAPIAS: %i\n",qnt_crioterapias);
}


