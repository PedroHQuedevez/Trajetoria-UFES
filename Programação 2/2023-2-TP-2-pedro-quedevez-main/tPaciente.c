#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tPaciente.h"
#include "tLesoes.h"

char datadefinida[11] = "09/11/2023";

struct ListaPacientes
{
    tPaciente **pacientes;
    int allocated;
    int size;
};

struct Paciente
{
    char nome[101];
    char cpf[15];
    char dataNascimento[11];
    int idade;
    char telefone[15];
    char genero[10];
    int numeroLesoes;
    int numeroConsultas;
    int atendido;
    tListaConsultas *consultas;
    tListaLesoes *lesoes;
};

char *RetornaNomePaciente(tPaciente *p)
{
    return p->nome;
}

char *RetornaCpfPaciente(tPaciente *p)
{
    return p->cpf;
}

tConsulta *RetornaConsultaPaciente(tPaciente *p)
{
    return RetornaUltimaConsulta(p->consultas);
}

int RetornaSizeListaPacientes(tListaPacientes *lista)
{
    return lista->size;
}

char *RetornaCpfPacienteLista(tListaPacientes *lista, int i)
{
    return lista->pacientes[i]->cpf;
}

tPaciente *CriaPaciente()
{
    tPaciente *Paciente = (tPaciente *)calloc(1, sizeof(tPaciente));
    return Paciente;
}

tListaPacientes *CriaListaPacientes()
{
    tListaPacientes *lista = (tListaPacientes *)calloc(1, sizeof(tListaPacientes));
    lista->pacientes = (tPaciente **)calloc(1, sizeof(tPaciente *));
    return lista;
}

int CadastrarPacienteArquivo(tListaPacientes *lista, FILE *filePacientes, FILE *fileLesoes, FILE *fileConsultas, tListaLesoes *listalesaogerais)
{
    lista->size++;
    lista->pacientes = (tPaciente **)realloc(lista->pacientes, sizeof(tPaciente *) * lista->size);
    tPaciente *Paciente = CriaPaciente();
    int elementosLidos;
    elementosLidos = fread(Paciente, sizeof(tPaciente), 1, filePacientes);
    Paciente->lesoes = CriaListaLesoes();
    Paciente->consultas = CriaListaConsultas();
    if ((elementosLidos > 0) && (Paciente != NULL) && (Paciente->numeroLesoes > 0))
    {
        for (int i = 0; i < (Paciente->numeroLesoes); i++)
        {
            CadastrarLesaoArquivo(Paciente->lesoes, fileLesoes, listalesaogerais);
        }
        for (int i = 0; i < (Paciente->numeroConsultas); i++)
        {
            CadastrarConsultaArquivo(Paciente->consultas, fileConsultas);
        }
    }
    if (Paciente != NULL)
    {
        lista->pacientes[lista->size - 1] = Paciente;
    }
    else
    {
        lista->size--;
    }

    return elementosLidos;
}

int VerificaCpfExisteP(char *cpf, tListaPacientes *lista)
{
    if (lista != NULL)
    {
        for (int i = 0; i < (lista->size - 1); i++)
        {
            if (lista->pacientes[i] != NULL)
            {
                if (lista->pacientes[i]->cpf != NULL && cpf != NULL)
                {
                    if (strcmp(cpf, lista->pacientes[i]->cpf) == 0)
                    {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

void CadastrarPacienteTeclado(tListaPacientes *lista)
{
    lista->size++;
    lista->pacientes = (tPaciente **)realloc(lista->pacientes, sizeof(tPaciente *) * lista->size);

    tPaciente *Paciente = CriaPaciente();
    printf("#################### CADASTRO PACIENTE #######################\n");
    printf("NOME COMPLETO: ");
    scanf("\n%101[^\n]", Paciente->nome);
    printf("\n");
    printf("CPF:");
    scanf("\n%15[^\n]", Paciente->cpf);
    printf("\n");
    printf("DATA DE NASCIMENTO: ");
    scanf("\n%11[^\n]", Paciente->dataNascimento);
    printf("\n");
    printf("TELEFONE: ");
    scanf("\n%15[^\n]", Paciente->telefone);
    printf("\n");
    printf("GENERO: ");
    scanf("\n%10[^\n]", Paciente->genero);
    printf("\n");

    Paciente->idade = calcularIdade(datadefinida, Paciente->dataNascimento);
    RemoveZerosEsquerda(Paciente->dataNascimento);

    if (VerificaCpfExisteP(Paciente->cpf, lista) == 1)
    {
        free(Paciente);
        lista->size--;
    }
    else
    {
        lista->pacientes[lista->size - 1] = Paciente;

        Paciente->lesoes = CriaListaLesoes();
        Paciente->consultas = CriaListaConsultas();

        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("############################################################");
        char lixo;
        scanf("\n%c", &lixo);
    }
}

void PrintaPaciente(tPaciente *paciente)
{
    printf("%s\n", paciente->nome);
    printf("%s\n", paciente->cpf);
    printf("%s\n", paciente->dataNascimento);
    printf("%s\n", paciente->telefone);
    printf("%s\n", paciente->genero);
}

void DestroiPaciente(tPaciente *p)
{
    DestroiListaLesoes(p->lesoes);
    DestroiListaConsultas(p->consultas);
    free(p);
}

void DestroiListaPaciente(tListaPacientes *l)
{
    for (int i = 0; i < l->size; i++)
    {
        DestroiPaciente(l->pacientes[i]);
        // free(l->pacientes[i]->lesoes);
        // free(l->pacientes[i]->consultas);
    }

    free(l->pacientes);
    free(l);
}

tPaciente *RetornaPacienteidx(tListaPacientes *lista, int pacienteidx)
{
    return lista->pacientes[pacienteidx];
}

// void VinculaConsultaPaciente(tPaciente *paciente, tConsulta *consulta)
// {
//     paciente->consulta = consulta;
// }

void ImprimeNomeDataPaciente(tPaciente *p)
{
    printf("-NOME: %s\n", p->nome);
    printf("-DATA DE NASCIMENTO: %s", p->dataNascimento);
}

tListaLesoes *RetornaListaLesoesPaciente(tPaciente *p)
{
    return p->lesoes;
}

tListaConsultas *RetornaListaConsultasPaciente(tPaciente *p)
{
    return p->consultas;
}

int VerificaCpfExiste(tListaPacientes *listaPacientes, char *cpf)
{
    for (int i = 0; i < listaPacientes->size; i++)
    {
        if (strcmp(listaPacientes->pacientes[i]->cpf, cpf) == 0)
        {
            return i;
        }
    }
    return -1;
}

int ComparaNomeBusca(tListaPacientes *lista, char *nomeProcurado, int idx)
{
    if (strcmp(lista->pacientes[idx]->nome, nomeProcurado) == 0)
    {
        return 1;
    }
    return 0;
}

void EscreveBinarioPacientes(tListaPacientes *listaPaciente, FILE *filePacientes, FILE *fileLesoes, FILE *fileConsultas)
{
    if (filePacientes == NULL || fileLesoes == NULL || fileConsultas == NULL)
    {
        printf("\nErro ao abrir o arquivo em EscreveBinarioPaciente.\n");
    }
    else
    {
        for (int i = 0; i < listaPaciente->size; i++)
        {
            fwrite(listaPaciente->pacientes[i], sizeof(tPaciente), 1, filePacientes);
            EscreveListaLesaoBinario(listaPaciente->pacientes[i]->lesoes, fileLesoes);
            EscreveListaConsultaBinario(listaPaciente->pacientes[i]->consultas, fileConsultas);
        }
    }
    fclose(filePacientes);
    fclose(fileLesoes);
    fclose(fileConsultas);
}

void IncrementaQuantidadeLesaoPaciente(tPaciente *p)
{
    p->numeroLesoes++;
}
void IncrementaQuantidadeConsultaPaciente(tPaciente *p)
{
    p->numeroConsultas++;
}

void SetaPacienteAtendido(tPaciente *p)
{
    p->atendido = 1;
}

int CalculaTotalAtendidos(tListaPacientes *listaPacientes)
{
    int count = 0;
    for (int i = 0; i < listaPacientes->size; i++)
    {
        if (listaPacientes->pacientes[i]->atendido == 1)
        {
            count++;
        }
    }
    return count;
}
int CalculaTotalFem(tListaPacientes *listaPacientes)
{
    int count = 0;
    for (int i = 0; i < listaPacientes->size; i++)
    {
        if (strcmp(listaPacientes->pacientes[i]->genero, "FEMININO") == 0)
        {
            count++;
        }
    }
    return count;
}
int CalculaTotalMasc(tListaPacientes *listaPacientes)
{
    int count = 0;
    for (int i = 0; i < listaPacientes->size; i++)
    {
        if (strcmp(listaPacientes->pacientes[i]->genero, "MASCULINO") == 0)
        {
            count++;
        }
    }
    return count;
}
int CalculaTotalOut(tListaPacientes *listaPacientes)
{
    int count = 0;
    for (int i = 0; i < listaPacientes->size; i++)
    {
        if (strcmp(listaPacientes->pacientes[i]->genero, "OUTROS") == 0)
        {
            count++;
        }
    }
    return count;
}

int calcularIdade(char *dataDefinida, char *dataNascimento)
{
    int diaDefinida, mesDefinida, anoDefinida;
    int diaNascimento, mesNascimento, anoNascimento;

    sscanf(dataDefinida, "%d/%d/%d", &diaDefinida, &mesDefinida, &anoDefinida);

    sscanf(dataNascimento, "%d/%d/%d", &diaNascimento, &mesNascimento, &anoNascimento);

    int idade = anoDefinida - anoNascimento;

    if (mesDefinida < mesNascimento || (mesDefinida == mesNascimento && diaDefinida < diaNascimento))
    {
        idade--;
    }

    return idade;
}

int CalculaIdadeMediaPacientes(tListaPacientes *listaPacientes)
{
    int somaidadeTotal = 0;
    int quantidadePacientes = 0;
    if (listaPacientes != NULL)
    {
        for (int i = 0; i < listaPacientes->size; i++)
        {
            if (listaPacientes->pacientes[i] != NULL && listaPacientes->pacientes[i]->idade != 0)
            {
                somaidadeTotal = somaidadeTotal + listaPacientes->pacientes[i]->idade;
                quantidadePacientes++;
            }
        }

        if (quantidadePacientes == 0)
        {
            quantidadePacientes++;
        }

        return somaidadeTotal / quantidadePacientes;
    }
    return 0;
}

void RemoveZerosEsquerda(char *data)
{
    int dia, mes, ano;

    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    sprintf(data, "%d/%d/%d", dia, mes, ano);
}

void ImprimeListaPacienteArquivoTexto (tListaPacientes *lista, char *path) {
    char arquivo[1001];
    sprintf(arquivo, "%s/pacientes.txt", path);
    FILE *file = fopen(arquivo, "w");
    fprintf(file,"%i\n",lista->size);
    for (int i = 0; i < lista->size; i++) {
        tPaciente *Paciente = lista->pacientes[i];
        if (Paciente != NULL) {
        fprintf(file,"NOME: %s\n",Paciente->nome);
        fprintf(file,"CPF: %s\n", Paciente->cpf);
        fprintf(file,"DATA DE NASCIMENTO: %s\n", Paciente->dataNascimento);
        fprintf(file,"TELEFONE: %s\n",Paciente->telefone);
        fprintf(file,"GENERO: %s\n",Paciente->genero);
        fprintf(file,"- - - - - -\n");
        }
        ImprimeListaConsultaArquivoTexto(Paciente->consultas, file, Paciente->numeroConsultas);
        ImprimeListaLesaoArquivoTexto(Paciente->lesoes, file, Paciente->numeroLesoes);
    }
    fclose(file);
}