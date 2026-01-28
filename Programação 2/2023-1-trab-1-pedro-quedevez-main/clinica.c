#include "paciente.h"
#include "dadospaciente.h"
#include "lesoes.h"
#include "clinica.h"


struct clinica {
    tpaciente **pacientes;
};


void cria_pastas () {
char comando[100];


sprintf(comando, "mkdir %s/%s", "saida", "logs");
system(comando);

sprintf(comando, "mkdir %s/%s", "saida", "buscas");
system(comando);

sprintf(comando, "mkdir %s/%s", "saida", "relatorio");
system(comando);
}


void menu () {
printf("######################### MENU INICIAL ###########################\n");
printf("Escolha uma opcao:\n");
printf("- Pre-cadastrar um paciente (P ou p)\n");
printf("- Iniciar um atendimento (A ou a)\n");
printf("- Buscar um paciente (B ou b)\n");
printf("- Gerar relatorio (R ou r)\n");
printf("- Finalizar programa (F ou f)\n");
printf("###############################################################\n");
}


tclinica* construir_clinica () {
    tclinica *clinica;
    clinica = (tclinica*)malloc(sizeof(tclinica));
    clinica->pacientes = (tpaciente**)malloc(sizeof(tpaciente*));
    
    return clinica;
}

void free_clinica (tclinica *clinica, int qnt_pac_cadastrados) {
    for (int i=0; i < qnt_pac_cadastrados; i++) {
    free_paciente(clinica->pacientes[i]);
    }
    free(clinica->pacientes);
    free(clinica);
}



int return_int (int inteiro) {
    return inteiro;
}

//limite de acesso clinica.pacientes[i], nessa biblioteca;

void ler_clinica (tclinica *clinica, char *argv1) {
char operacao,aux_sus[19];
int qnt_pac_cadastrados = 0, qnt_les_cadastradas=0,qnt_atendimentos=0;
int pac_ja_cadastrado = 0, aux_sus_cadastrado = 0;
char l[30];

//-------------------
char nome[100];
char sus[19];
char data[11];
char telefone[18];
char endereco[200];
char genero[10];

//-------------------
    
    while (1) {
    menu();   
    scanf("\n%c",&operacao);
        
        if (operacao == 'P' || operacao == 'p') {
            
           //------------------------------- verificação de paciente já cadastrado
            scanf("\n%100[^\n]",nome);
            scanf("\n%s",sus);
           
            pac_ja_cadastrado = 0; //auxiliar de teste para cadastro já realizado;
            for (int i=0; i < qnt_pac_cadastrados; i++) {
                if (encontra_paciente(sus,clinica->pacientes[i]) == 1) {
                    pac_ja_cadastrado = 1;
                    
                }
            }
            if (pac_ja_cadastrado == 1) {
                printf("paciente já está cadastrado\n");
                continue;
            }

            scanf("\n%s",data);
            scanf("\n%s",telefone);
            scanf("\n%200[^\n]",endereco);
            scanf("\n%s",genero);
           //------------------------------- 
            clinica->pacientes = (tpaciente**)realloc(clinica->pacientes,sizeof(tpaciente*)*(qnt_pac_cadastrados+1));
            clinica->pacientes[qnt_pac_cadastrados]=cria_paciente();
            atribui_paciente(clinica->pacientes[qnt_pac_cadastrados],nome,sus,data,telefone,endereco,genero);
            qnt_pac_cadastrados++;
        }

       
       
       
        if (operacao == 'A' || operacao == 'a') {
        aux_sus_cadastrado = 0;
        scanf("\n%s",aux_sus);
        for (int i=0; i < qnt_pac_cadastrados; i++) {
                if (encontra_paciente(aux_sus,clinica->pacientes[i]) == 1) { 
                    aux_sus_cadastrado = 1;
                }
        }

if (aux_sus_cadastrado == 1) {
       
        int qnt_les_pac = 1; 
            for (int i=0; i < qnt_pac_cadastrados; i++) {
            
                if (encontra_paciente(aux_sus,clinica->pacientes[i]) == 1) {
                    atribui_dados_paciente(clinica->pacientes[i]);
                    
                    scanf("\n%100[^\n]",l);
                    while (strcmp(l,"E")!=0 ) {
                        atribui_lesoes_paciente(clinica->pacientes[i],qnt_les_pac,l);
                        qnt_les_pac++;
                        qnt_les_cadastradas++;
                        scanf("\n%100[^\n]",l);
                    }
                    qnt_atendimentos++;
                    gera_log(clinica->pacientes[i],argv1,qnt_atendimentos);                
                    }
            } 
        } else {
            printf("paciente não encontrado\n");
        }
     }
       
       
       
        if (operacao == 'B' || operacao == 'b') {
             aux_sus_cadastrado = 0;
             scanf("\n%s",aux_sus);

            for (int i=0; i < qnt_pac_cadastrados; i++) {
                if (encontra_paciente(aux_sus,clinica->pacientes[i]) == 1) { 
                    aux_sus_cadastrado = 1;
                }
            }


        if (aux_sus_cadastrado == 1) {
            for (int i=0; i < qnt_pac_cadastrados; i++) {
                if (encontra_paciente(aux_sus,clinica->pacientes[i]) == 1) {
                    print_busca_paciente(clinica->pacientes[i],argv1);
                    }
                }
            } else {
                printf("paciente não encontrado\n");
            } 
        }

       
       
       
        if (operacao == 'R' || operacao == 'r') {
            gera_relatorio (clinica->pacientes, qnt_pac_cadastrados,qnt_les_cadastradas,argv1);
        }

       
       
       
        if (operacao == 'F' || operacao == 'f') {
            printf("programa sendo finalizado.");
            gera_resumo(clinica->pacientes,qnt_pac_cadastrados,qnt_les_cadastradas,calc_qnt_cirur_lista(clinica->pacientes,qnt_pac_cadastrados),calc_qnt_crio_lista(clinica->pacientes,qnt_pac_cadastrados),argv1);
            break;
        }
    }
    free_clinica(clinica,qnt_pac_cadastrados);
    
    if (clinica != NULL) {
        free(clinica);
    }

}

