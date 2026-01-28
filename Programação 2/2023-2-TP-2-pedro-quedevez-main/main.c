#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tConsulta.h"
#include "tDocumento.h"
#include "tFila.h"
#include "tLesoes.h"
#include "tMedico.h"
#include "tMenus.h"
#include "tPaciente.h"
#include "tReceita.h"
#include "tSecretario.h"
#include "tBanco.h"
#include "tEncaminhamento.h"
#include "tBiopsia.h"
#include "tBusca.h"
#include "tRelatorio.h"

// arrumar caminhos para o script

void iniciaArquivostxt(char *path)
{
    char arquivo[1001];
    sprintf(arquivo, "%s/saida/biopsia.txt", path);
    FILE *file = fopen(arquivo, "w");
    fclose(file);

    sprintf(arquivo, "%s/saida/lista_busca.txt", path);
    file = fopen(arquivo, "w");
    fclose(file);

    sprintf(arquivo, "%s/saida/encaminhamento.txt", path);
    file = fopen(arquivo, "w");
    fclose(file);

    sprintf(arquivo, "%s/saida/receita.txt", path);
    file = fopen(arquivo, "w");
    fclose(file);

    sprintf(arquivo, "%s/saida/relatorio_geral.txt", path);
    file = fopen(arquivo, "w");
    fclose(file);
}

int main(int argc, char *argv[])
{

    //------------------------------------------------------------------------------------------------------------------
    // LEITURA BANCO DE DADOS
    tListaSecretarios *listaSecretarios = CriaListaSecretarios();
    tListaMedicos *listaMedicos = CriaListaMedicos();
    tListaPacientes *listaPacientes = CriaListaPacientes();
    tListaLesoes *listaLesoesgerais = CriaListaLesoes();
    tListaConsultas *listaConsultasgerais = CriaListaConsultas();
    tFila *fila = criaFila();

    MenuCaminho();
    char path[1001];
    scanf("\n%s", path);

    iniciaArquivostxt(argv[1]);

    char arquivo[1051];
    sprintf(arquivo, "%s/%s/secretarios.bin", argv[1], path);
    FILE *fileSecretarios = fopen(arquivo, "rb");

    sprintf(arquivo, "%s/%s/medicos.bin", argv[1], path);
    FILE *fileMedicos = fopen(arquivo, "rb");

    sprintf(arquivo, "%s/%s/pacientes.bin", argv[1], path);
    FILE *filePacientes = fopen(arquivo, "rb");

    sprintf(arquivo, "%s/%s/lesoes.bin", argv[1], path);
    FILE *fileLesoes = fopen(arquivo, "rb");
    fileLesoes = iniciaArquivoBin(arquivo, fileLesoes);

    sprintf(arquivo, "%s/%s/consultas.bin", argv[1], path);
    FILE *fileConsultas = fopen(arquivo, "rb");
    fileConsultas = iniciaArquivoBin(arquivo, fileConsultas);

    // sprintf(arquivo, "%s/inicio.bin", argv[1]);
    // FILE *fileInicio = fopen(arquivo, "rb");
    // fileInicio = iniciaArquivoBin(arquivo, fileInicio);

   if (LeBancoDadosSecretarios(listaSecretarios, fileSecretarios) == 0)
    {     
        PrimeiroCadastro(listaSecretarios);
    }

    if (LeBancoDadosMedicos(listaMedicos, fileMedicos) == 0)
    {
        // CadastrarMedicoTeclado(listaMedicos, path);
    }

    if (LeBancoDadosPacientes(listaPacientes, filePacientes, fileLesoes, fileConsultas, listaLesoesgerais) == 0)
    {
        // CadastrarMedicoTeclado(listaMedicos, path);
    }
    if (fileSecretarios != NULL)
    {
        fclose(fileSecretarios);
    }
    if (fileMedicos != NULL)
    {
        fclose(fileMedicos);
    }
    if (filePacientes != NULL)
    {
        fclose(filePacientes);
    }
    if (fileLesoes != NULL)
    {
        fclose(fileLesoes);
    }
    if (fileConsultas != NULL)
    {
        fclose(fileConsultas);
    }

    //------------------------------------------------------------------------------------------------------------------
    // LOGIN
    char tipoLogin;
    tSecretario *usuarioS = NULL;
    tMedico *usuarioM = NULL;
    char lixo;
    while (1)
    {
        MenuLogin();
        char login[31], senha[31];
        scanf("\n%s", login);
        scanf("\n%s", senha);

        usuarioS = RealizaLoginS(listaSecretarios, login, senha);
        usuarioM = RealizaLoginM(listaMedicos, login, senha);

        if (usuarioS != NULL)
        {
            printf("Login bem sucedido.\n");
            if (VerificaNivelAcesso(usuarioS) == 1)
            {
                tipoLogin = 'A';
                break;
            }
            else
            {
                tipoLogin = 'S';
                break;
            }
        }
        else if (usuarioM != NULL)
        {
            printf("Login bem sucedido.\n");
            tipoLogin = 'M';
            break;
        }
        else
        {
            printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
        }
    }
    //------------------------------------------------------------------------------------------------------------------
    // INICIO FLUXO PROGRAMA - SECRETÁRIO - ADM
    int opcao = 0;
    if (tipoLogin == 'A')
    {
        while (1)
        {
            MenuPrincipalSecretarioAdmin();
            scanf("\n%d", &opcao);
            if (opcao == 1)
            {
                CadastrarSecretarioTeclado(listaSecretarios);
            }
            else if (opcao == 2)
            {
                CadastrarMedicoTeclado(listaMedicos);
            }
            else if (opcao == 3)
            {
                CadastrarPacienteTeclado(listaPacientes);
            }
            else if (opcao == 4)
            {
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("CPF DO PACIENTE: \n");
                char cpf[15];
                scanf("\n%s", cpf);
                printf("############################################################\n");
                int idxpaciente = VerificaCpfExiste(listaPacientes, cpf);

                if (idxpaciente != -1)
                {
                    tConsulta *consultaAtual;
                    tPaciente *pacienteSendoAtendido = RetornaPacienteidx(listaPacientes, idxpaciente);
                    consultaAtual = IniciaConsulta(listaPacientes, path, cpf, pacienteSendoAtendido, listaConsultasgerais);
                    int quantLesoesConsulta = 0;

                    while (opcao != 5)
                    {

                        MenuConsultaMedica();
                        scanf("\n%d", &opcao);
                        if (opcao == 1)
                        {
                            quantLesoesConsulta++;
                            CadastraLesaoTeclado(pacienteSendoAtendido, listaLesoesgerais, quantLesoesConsulta);
                            IncrementaQuantidadeLesaoPaciente(pacienteSendoAtendido);
                            IncrementaQuantLesaoConsulta(consultaAtual);
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 2)
                        {
                            printf("#################### CONSULTA MEDICA #######################\n");
                            printf("RECEITA MEDICA:\n");
                            printf("TIPO DE USO: \n");
                            char tipoUso[7];
                            scanf("\n%s", tipoUso);
                            int t;
                            if (strcmp("ORAL", tipoUso) == 0)
                            {
                                t = 0;
                            }
                            else
                            {
                                t = 1;
                            }

                            printf("NOME DO MEDICAMENTO: \n");
                            char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
                            scanf("\n%50[^\n]", nomeMedicamento);
                            printf("TIPO DE MEDICAMENTO: \n");
                            char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
                            scanf("\n%50[^\n]", tipoMedicamento);
                            printf("QUANTIDADE: \n");
                            int quantidade;
                            scanf("\n%i", &quantidade);
                            printf("INSTRUÇÕES DE USO: \n");
                            char intrucoesUso[MAX_TAM_INSTRUCOES];
                            scanf("\n%300[^\n]", intrucoesUso);
                            // -----
                            tReceita *receita = criaReceita(RetornaNomePaciente(pacienteSendoAtendido), t, nomeMedicamento, tipoMedicamento, intrucoesUso, quantidade, "", "", RetornaDataConsulta(consultaAtual));
                            insereDocumentoFila(fila, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
                            IncrementaQuantidadeConsultaPaciente(pacienteSendoAtendido);
                            // -----
                            printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO.PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                            printf("############################################################\n");
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 3)
                        {
                            if (VerificaExisteCasoCirurgico(RetornaListaLesoesPaciente(pacienteSendoAtendido)) == 1)
                            {
                                //----
                                tBiopsia *biopsia = CriaBiopsia(RetornaNomePaciente(pacienteSendoAtendido), RetornaCpfPaciente(pacienteSendoAtendido), NULL, NULL, RetornaDataConsulta(consultaAtual), pacienteSendoAtendido);
                                insereDocumentoFila(fila, biopsia, ImprimeNaTelaBiopsia, ImprimeEmArquivoBiopsia, DesalocaBiopsia);
                                //----
                                printf("#################### CONSULTA MEDICA #######################\n");
                                printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                                printf("############################################################\n");
                            }

                            else
                            {
                                printf("#################### CONSULTA MEDICA #######################\n");
                                printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                                printf("############################################################\n");
                            }
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 4)
                        {
                            // Fazer leituras;
                            printf("#################### CONSULTA MEDICA #######################\n");
                            printf("ENCAMINHAMENTO:\n");
                            printf("ESPECIALIDADE ENCAMINHADA: \n");
                            char especialidade[100];
                            scanf("\n%100[^\n]", especialidade);
                            printf("MOTIVO: \n");
                            char motivo[300];
                            scanf("\n%300[^\n]", motivo);
                            //-----
                            tEncaminhamento *encaminhamento = CriaEncaminhamento(RetornaNomePaciente(pacienteSendoAtendido), RetornaCpfPaciente(pacienteSendoAtendido),
                                                                                 especialidade, motivo, NULL, NULL, RetornaDataConsulta(consultaAtual));
                            insereDocumentoFila(fila, encaminhamento, ImprimeNaTelaEncaminhamento, ImprimeEmArquivoEncaminhamento, DesalocaEncaminhamento);
                            //-----
                            printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                            printf("############################################################\n");
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 5)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    printf("#################### CONSULTA MEDICA #######################\n");
                    printf("CPF DO PACIENTE: %s\n", cpf);
                    printf("PACIENTE SEM CADASTRO\n\n");
                    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    scanf("%c", &lixo);
                }
            }
            else if (opcao == 5)
            {
                printf("#################### BUSCAR PACIENTES #######################\n");
                printf("NOME DO PACIENTE: \n");
                char nomeProcurado[101];
                scanf("\n%s", nomeProcurado);
                printf("############################################################\n");
                //----
                tBusca *busca = CriaBusca(listaPacientes, nomeProcurado, path);
                printf("#################### BUSCAR PACIENTES #######################\n");
                //----
                if (busca == NULL)
                {
                    printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");
                    free(busca);
                }
                else
                {
                    ImprimeNaTelaBusca(busca);
                    printf("SELECIONE UMA OPÇÃO:\n");
                    printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
                    printf("(2) RETORNAR AO MENU PRINCIPAL\n");
                    printf("############################################################\n");

                    scanf("\n%i", &opcao);
                    if (opcao == 1)
                    {
                        insereDocumentoFila(fila, busca, ImprimeNaTelaBusca, ImprimeEmArquivoBusca, DesalocaBusca);
                        printf("#################### BUSCAR PACIENTES #######################\n");
                        printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
                        printf("############################################################\n");
                        scanf("\n%c", &lixo);
                    }
                }
            }
            else if (opcao == 6)
            {
                int numeroTotalAtendidos = CalculaTotalAtendidos(listaPacientes);
                int idademedia = CalculaIdadeMediaPacientes(listaPacientes);
                int fem = CalculaTotalFem(listaPacientes);
                int masc = CalculaTotalMasc(listaPacientes);
                int out = CalculaTotalOut(listaPacientes);
                printaListaLesoes(listaLesoesgerais);
                int tamanhoMedioLesoes = CalculaTamMedioLesoes(listaLesoesgerais);
                int numeroTotalLesoes = CalculaTotalLesoes(listaLesoesgerais);
                int numeroTotalCirurgias = CalculaTotalCirurgias(listaLesoesgerais);
                int numeroTotalCrioterapia = CalculaTotalCrioterapia(listaLesoesgerais);
                tRelatorio *relatorio = CriaRelatorio(numeroTotalAtendidos, idademedia, fem, masc, out, tamanhoMedioLesoes, numeroTotalLesoes, numeroTotalCirurgias, numeroTotalCrioterapia);
                ImprimeNaTelaRelatorio(relatorio);

                printf("SELECIONE UMA OPÇÃO:\n");
                printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
                printf("(2) RETORNAR AO MENU PRINCIPAL\n");
                printf("############################################################\n");

                scanf("\n%i", &opcao);
                if (opcao == 1)
                {
                    insereDocumentoFila(fila, relatorio, ImprimeNaTelaRelatorio, ImprimeEmArquivoRelatorio, DesalocaRelatorio);
                    printf("#################### RELATORIO GERAL #######################\n");
                    printf("RELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");

                    scanf("\n%c", &lixo);
                }
            }
            else if (opcao == 7)
            {
                while (opcao != 2)
                {
                    printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
                    printf("ESCOLHA UMA OPCAO:\n");
                    printf("EXECUTAR FILA DE IMPRESSAO\n");
                    printf("RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");
                    scanf("\n%i", &opcao);

                    if (opcao == 1)
                    {
                        printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
                        printf("EXECUTANDO FILA DE IMPRESSÃO:\n");
                        char caminhodefinidopeloscript[1051];
                        sprintf(caminhodefinidopeloscript, "%s/saida", argv[1]);
                        imprimeFila(fila, caminhodefinidopeloscript);
                        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR\n");
                        printf("###########################################################\n");
                        scanf("\n%c", &lixo);
                    }
                }
            }
            else if (opcao == 8)
            {
                break;
            }
        }
    }
    else if (tipoLogin == 'S')
    {
        while (1)
        {
            MenuPrincipalSecretarioUser();
            scanf("%d", &opcao);

            if (opcao == 2)
            {
                CadastrarMedicoTeclado(listaMedicos);
            }
            else if (opcao == 3)
            {
                CadastrarPacienteTeclado(listaPacientes);
            }
            else if (opcao == 5)
            {
                printf("#################### BUSCAR PACIENTES #######################\n");
                printf("NOME DO PACIENTE: \n");
                char nomeProcurado[101];
                scanf("\n%s", nomeProcurado);
                printf("############################################################\n");
                //----
                tBusca *busca = CriaBusca(listaPacientes, nomeProcurado, path);
                printf("#################### BUSCAR PACIENTES #######################\n");
                //----
                if (busca == NULL)
                {
                    printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");
                    free(busca);
                }
                else
                {
                    ImprimeNaTelaBusca(busca);
                    printf("SELECIONE UMA OPÇÃO:\n");
                    printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
                    printf("(2) RETORNAR AO MENU PRINCIPAL\n");
                    printf("############################################################\n");

                    scanf("\n%i", &opcao);
                    if (opcao == 1)
                    {
                        insereDocumentoFila(fila, busca, ImprimeNaTelaBusca, ImprimeEmArquivoBusca, DesalocaBusca);
                        printf("#################### BUSCAR PACIENTES #######################\n");
                        printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
                        printf("############################################################\n");
                        scanf("\n%c", &lixo);
                    }
                }
            }
            else if (opcao == 6)
            {
                int numeroTotalAtendidos = CalculaTotalAtendidos(listaPacientes);
                int idademedia = CalculaIdadeMediaPacientes(listaPacientes);
                int fem = CalculaTotalFem(listaPacientes);
                int masc = CalculaTotalMasc(listaPacientes);
                int out = CalculaTotalOut(listaPacientes);
                printaListaLesoes(listaLesoesgerais);
                int tamanhoMedioLesoes = CalculaTamMedioLesoes(listaLesoesgerais);
                int numeroTotalLesoes = CalculaTotalLesoes(listaLesoesgerais);
                int numeroTotalCirurgias = CalculaTotalCirurgias(listaLesoesgerais);
                int numeroTotalCrioterapia = CalculaTotalCrioterapia(listaLesoesgerais);
                tRelatorio *relatorio = CriaRelatorio(numeroTotalAtendidos, idademedia, fem, masc, out, tamanhoMedioLesoes, numeroTotalLesoes, numeroTotalCirurgias, numeroTotalCrioterapia);
                ImprimeNaTelaRelatorio(relatorio);

                printf("SELECIONE UMA OPÇÃO:\n");
                printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
                printf("(2) RETORNAR AO MENU PRINCIPAL\n");
                printf("############################################################\n");

                scanf("\n%i", &opcao);
                if (opcao == 1)
                {
                    insereDocumentoFila(fila, relatorio, ImprimeNaTelaRelatorio, ImprimeEmArquivoRelatorio, DesalocaRelatorio);
                    printf("#################### RELATORIO GERAL #######################\n");
                    printf("RELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");

                    scanf("\n%c", &lixo);
                }
            }
            else if (opcao == 7)
            {
                while (opcao != 2)
                {
                    printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
                    printf("ESCOLHA UMA OPCAO:\n");
                    printf("EXECUTAR FILA DE IMPRESSAO\n");
                    printf("RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");
                    scanf("\n%i", &opcao);

                    if (opcao == 1)
                    {
                        printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
                        printf("EXECUTANDO FILA DE IMPRESSÃO:\n");
                        char caminhodefinidopeloscript[1051];
                        sprintf(caminhodefinidopeloscript, "%s/saida", argv[1]);
                        imprimeFila(fila, caminhodefinidopeloscript);
                        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR\n");
                        printf("###########################################################\n");
                        scanf("\n%c", &lixo);
                    }
                }
            }
            else if (opcao == 8)
            {
                break;
            }
        }
    }
    else if (tipoLogin == 'M')
    {
        while (1)
        {
            MenuPrincipalMedicos();
            scanf("%d", &opcao);

            if (opcao == 4)
            {
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("CPF DO PACIENTE: \n");
                char cpf[15];
                scanf("\n%s", cpf);
                printf("############################################################\n");
                int idxpaciente = VerificaCpfExiste(listaPacientes, cpf);

                if (idxpaciente != -1)
                {
                    tPaciente *pacienteSendoAtendido = RetornaPacienteidx(listaPacientes, idxpaciente);
                    tConsulta *consultaAtual;
                    consultaAtual = IniciaConsulta(listaPacientes, path, cpf, pacienteSendoAtendido, listaConsultasgerais);
                    int quantLesoesConsulta = 0;
                    while (opcao != 5)
                    {

                        MenuConsultaMedica();
                        scanf("\n%d", &opcao);

                        if (opcao == 1)
                        {
                            quantLesoesConsulta++;
                            CadastraLesaoTeclado(pacienteSendoAtendido, listaLesoesgerais, quantLesoesConsulta);
                            IncrementaQuantidadeLesaoPaciente(pacienteSendoAtendido);
                            IncrementaQuantLesaoConsulta(consultaAtual);
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 2)
                        {
                            printf("#################### CONSULTA MEDICA #######################\n");
                            printf("RECEITA MEDICA:\n");
                            printf("TIPO DE USO: \n");
                            char tipoUso[7];
                            scanf("\n%s", tipoUso);
                            int t;
                            if (strcmp("ORAL", tipoUso) == 0)
                            {
                                t = 0;
                            }
                            else
                            {
                                t = 1;
                            }

                            printf("NOME DO MEDICAMENTO: \n");
                            char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
                            scanf("\n%50[^\n]", nomeMedicamento);
                            printf("TIPO DE MEDICAMENTO: \n");
                            char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
                            scanf("\n%50[^\n]", tipoMedicamento);
                            printf("QUANTIDADE: \n");
                            int quantidade;
                            scanf("\n%i", &quantidade);
                            printf("INSTRUÇÕES DE USO: \n");
                            char intrucoesUso[MAX_TAM_INSTRUCOES];
                            scanf("\n%300[^\n]", intrucoesUso);
                            // -----
                            tReceita *receita = criaReceita(RetornaNomePaciente(pacienteSendoAtendido), t, nomeMedicamento, tipoMedicamento, intrucoesUso, quantidade, RetornaNomeMedico(usuarioM), RetornaCRMMedico(usuarioM), RetornaDataConsulta(consultaAtual));
                            insereDocumentoFila(fila, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
                            IncrementaQuantidadeConsultaPaciente(pacienteSendoAtendido);
                            // -----
                            printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO.PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                            printf("############################################################\n");
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 3)
                        {
                            if (VerificaExisteCasoCirurgico(RetornaListaLesoesPaciente(pacienteSendoAtendido)) == 1)
                            {
                                //----
                                tBiopsia *biopsia = CriaBiopsia(RetornaNomePaciente(pacienteSendoAtendido), RetornaCpfPaciente(pacienteSendoAtendido), RetornaNomeMedico(usuarioM), RetornaCRMMedico(usuarioM), RetornaDataConsulta(consultaAtual), pacienteSendoAtendido);
                                insereDocumentoFila(fila, biopsia, ImprimeNaTelaBiopsia, ImprimeEmArquivoBiopsia, DesalocaBiopsia);
                                //----
                                printf("#################### CONSULTA MEDICA #######################\n");
                                printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                                printf("############################################################\n");
                            }

                            else
                            {
                                printf("#################### CONSULTA MEDICA #######################\n");
                                printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                                printf("############################################################\n");
                            }
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 4)
                        {
                            // Fazer leituras;
                            printf("#################### CONSULTA MEDICA #######################\n");
                            printf("ENCAMINHAMENTO:\n");
                            printf("ESPECIALIDADE ENCAMINHADA: \n");
                            char especialidade[100];
                            scanf("\n%100[^\n]", especialidade);
                            printf("MOTIVO: \n");
                            char motivo[300];
                            scanf("\n%300[^\n]", motivo);
                            //-----
                            tEncaminhamento *encaminhamento = CriaEncaminhamento(RetornaNomePaciente(pacienteSendoAtendido), RetornaCpfPaciente(pacienteSendoAtendido),
                                                                                 especialidade, motivo, RetornaNomeMedico(usuarioM), RetornaCRMMedico(usuarioM), RetornaDataConsulta(consultaAtual));
                            insereDocumentoFila(fila, encaminhamento, ImprimeNaTelaEncaminhamento, ImprimeEmArquivoEncaminhamento, DesalocaEncaminhamento);
                            //-----
                            printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                            printf("############################################################\n");
                            scanf("\n%c", &lixo);
                        }
                        else if (opcao == 5)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    printf("#################### CONSULTA MEDICA #######################\n");
                    printf("CPF DO PACIENTE: %s\n", cpf);
                    printf("PACIENTE SEM CADASTRO\n\n");
                    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
                    scanf("%c", &lixo);
                }
            }
            else if (opcao == 5)
            {
                printf("#################### BUSCAR PACIENTES #######################\n");
                printf("NOME DO PACIENTE: \n");
                char nomeProcurado[101];
                scanf("\n%s", nomeProcurado);
                printf("############################################################\n");
                //----
                tBusca *busca = CriaBusca(listaPacientes, nomeProcurado, path);
                printf("#################### BUSCAR PACIENTES #######################\n");
                //----
                if (busca == NULL)
                {
                    printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");
                    free(busca);
                }
                else
                {
                    ImprimeNaTelaBusca(busca);
                    printf("SELECIONE UMA OPÇÃO:\n");
                    printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
                    printf("(2) RETORNAR AO MENU PRINCIPAL\n");
                    printf("############################################################\n");

                    scanf("\n%i", &opcao);
                    if (opcao == 1)
                    {
                        insereDocumentoFila(fila, busca, ImprimeNaTelaBusca, ImprimeEmArquivoBusca, DesalocaBusca);
                        printf("#################### BUSCAR PACIENTES #######################\n");
                        printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
                        printf("############################################################\n");
                        scanf("\n%c", &lixo);
                    }
                    else
                    {
                        free(busca);
                    }
                }
            }
            else if (opcao == 6)
            {
                int numeroTotalAtendidos = CalculaTotalAtendidos(listaPacientes);
                int idademedia = CalculaIdadeMediaPacientes(listaPacientes);
                int fem = CalculaTotalFem(listaPacientes);
                int masc = CalculaTotalMasc(listaPacientes);
                int out = CalculaTotalOut(listaPacientes);
                printaListaLesoes(listaLesoesgerais);
                int tamanhoMedioLesoes = CalculaTamMedioLesoes(listaLesoesgerais);
                int numeroTotalLesoes = CalculaTotalLesoes(listaLesoesgerais);
                int numeroTotalCirurgias = CalculaTotalCirurgias(listaLesoesgerais);
                int numeroTotalCrioterapia = CalculaTotalCrioterapia(listaLesoesgerais);
                tRelatorio *relatorio = CriaRelatorio(numeroTotalAtendidos, idademedia, fem, masc, out, tamanhoMedioLesoes, numeroTotalLesoes, numeroTotalCirurgias, numeroTotalCrioterapia);
                ImprimeNaTelaRelatorio(relatorio);

                printf("SELECIONE UMA OPÇÃO:\n");
                printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
                printf("(2) RETORNAR AO MENU PRINCIPAL\n");
                printf("############################################################\n");

                scanf("\n%i", &opcao);
                if (opcao == 1)
                {
                    insereDocumentoFila(fila, relatorio, ImprimeNaTelaRelatorio, ImprimeEmArquivoRelatorio, DesalocaRelatorio);
                    printf("#################### RELATORIO GERAL #######################\n");
                    printf("RELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");

                    scanf("\n%c", &lixo);
                }
            }
            else if (opcao == 7)
            {
                while (opcao != 2)
                {
                    printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
                    printf("ESCOLHA UMA OPCAO:\n");
                    printf("EXECUTAR FILA DE IMPRESSAO\n");
                    printf("RETORNAR AO MENU ANTERIOR\n");
                    printf("############################################################\n");
                    scanf("\n%i", &opcao);

                    if (opcao == 1)
                    {
                        printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
                        printf("EXECUTANDO FILA DE IMPRESSÃO:\n");
                        char caminhodefinidopeloscript[1051];
                        sprintf(caminhodefinidopeloscript, "%s/saida", argv[1]);
                        imprimeFila(fila, caminhodefinidopeloscript);
                        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR\n");
                        printf("###########################################################\n");
                        scanf("\n%c", &lixo);
                    }
                }
            }
            else if (opcao == 8)
            {
                break;
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------
    sprintf(arquivo, "%s/%s/secretarios.bin", argv[1], path);
    fileSecretarios = fopen(arquivo, "wb");

    sprintf(arquivo, "%s/%s/medicos.bin", argv[1], path);
    fileMedicos = fopen(arquivo, "wb");

    sprintf(arquivo, "%s/%s/pacientes.bin", argv[1], path);
    filePacientes = fopen(arquivo, "wb");

    sprintf(arquivo, "%s/%s/lesoes.bin", argv[1], path);
    fileLesoes = fopen(arquivo, "wb");

    sprintf(arquivo, "%s/%s/consultas.bin", argv[1], path);
    fileConsultas = fopen(arquivo, "wb");

    EscreveBinarioSecretarios(listaSecretarios, fileSecretarios);
    EscreveBinarioMedicos(listaMedicos, fileMedicos);
    EscreveBinarioPacientes(listaPacientes, filePacientes, fileLesoes, fileConsultas);

    char caminhodefinidopeloscript[1051];
    sprintf(caminhodefinidopeloscript, "%s/saida", argv[1]);
    ImprimeListaMedicoArquivoTexto(listaMedicos, caminhodefinidopeloscript);
    ImprimeListaSecretariosArquivoTexto(listaSecretarios, caminhodefinidopeloscript);
    ImprimeListaPacienteArquivoTexto(listaPacientes,caminhodefinidopeloscript);
    // EscreveListaLesaoBinario(listaLesoesgerais, fileLesoes);
    // EscreveListaConsultaBinario(listaConsultasgerais, fileConsultas);
    //------------------------------------------------------------------------------------------------------------------
    //  LIBERACAO DE MEMORIA
    DestroiListaSecretario(listaSecretarios);
    DestroiListaMedico(listaMedicos);
    DestroiListaPaciente(listaPacientes);
    DestroiListaLesoesGerais(listaLesoesgerais);
    DestroiListaConsultasGerais(listaConsultasgerais);
    desalocaFila(fila);
    //------------------------------------------------------------------------------------------------------------------
    return 0;
}