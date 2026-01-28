#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tConsulta.h"
#include "tPaciente.h"

struct ListaConsultas
{
    tConsulta **consultas;
    int allocated;
    int size;
};

struct Consulta
{
    int diabetes;
    int fumante;
    int alergia;
    int historicoCancer;
    char tipopele[3];
    char dataconsulta[11];
    int quantidadeLesoesLidas;
};

tListaConsultas *CriaListaConsultas()
{
    tListaConsultas *lista = (tListaConsultas *)calloc(1, sizeof(tListaConsultas));
    lista->consultas = (tConsulta **)calloc(1, sizeof(tConsulta *));
    return lista;
}

tConsulta *CriaConsulta()
{
    tConsulta *consulta = (tConsulta *)calloc(1, sizeof(tConsulta));
    return consulta;
}

char *RetornaDataConsulta(tConsulta *c)
{
    return c->dataconsulta;
}

tConsulta *RetornaUltimaConsulta(tListaConsultas *lista)
{
    return lista->consultas[lista->size - 1];
}

void AdicionaConsultaListaConsulta(tListaConsultas *lista, tConsulta *Consulta)
{
    if (lista == NULL)
    {
        lista = CriaListaConsultas();
    }

    lista->size++;
    lista->consultas = (tConsulta **)realloc(lista->consultas, sizeof(tConsulta *) * lista->size);

    lista->consultas[lista->size - 1] = Consulta;
}

tConsulta *LeConsulta(tPaciente *paciente, tListaConsultas *consultasgerais)
{
    tListaConsultas *lista = RetornaListaConsultasPaciente(paciente);

    if (lista == NULL)
    {
        lista = CriaListaConsultas();
    }

    lista->size++;
    lista->consultas = (tConsulta **)realloc(lista->consultas, sizeof(tConsulta *) * lista->size);

    tConsulta *consulta = CriaConsulta();

    printf("DATA DA CONSULTA: \n");
    scanf("\n%s", consulta->dataconsulta);
    printf("POSSUI DIABETES:\n");
    scanf("\n%i", &consulta->diabetes);
    printf("FUMANTE:\n");
    scanf("\n%i", &consulta->fumante);
    printf("ALEGIA A MEDICAMENTO:\n");
    scanf("\n%i", &consulta->alergia);
    printf("HISTORICO DE CANCER:\n");
    scanf("\n%i", &consulta->historicoCancer);
    printf("TIPO DE PELE:\n");
    scanf("\n%s", consulta->tipopele);

    RemoveZerosEsquerda(consulta->dataconsulta);

    lista->consultas[lista->size - 1] = consulta;
    AdicionaConsultaListaConsulta(consultasgerais, consulta);

    return consulta;
}

tConsulta *IniciaConsulta(tListaPacientes *lista, char *path, char *cpf, tPaciente *pacienteSendoAtendido, tListaConsultas *consultasgerais)
{

    // tPaciente *paciente = RetornaPacienteidx(lista, idx);
    tConsulta *consulta;
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: %s\n", cpf);
    printf("---\n");
    ImprimeNomeDataPaciente(pacienteSendoAtendido);
    SetaPacienteAtendido(pacienteSendoAtendido);
    printf("---\n");

    // tConsulta *consulta = CriaConsulta();
    consulta = LeConsulta(pacienteSendoAtendido, consultasgerais);
    // VinculaConsultaPaciente(paciente, consulta);
    printf("############################################################\n");
    return consulta;
}

void CadastrarConsultaArquivo(tListaConsultas *lista, FILE *file)
{

    lista->size++;
    lista->consultas = (tConsulta **)realloc(lista->consultas, sizeof(tConsulta *) * lista->size);
    tConsulta *Consulta = CriaConsulta();
    int elementosLidos;
    elementosLidos = fread(Consulta, sizeof(tConsulta), 1, file);
    if (Consulta != NULL)
    {
        lista->consultas[lista->size - 1] = Consulta;
    }
    else
    {
        lista->size--;
    }
}

void EscreveListaConsultaBinario(tListaConsultas *lista, FILE *file)
{
    for (int i = 0; i < lista->size; i++)
    {
        if (lista->consultas[i] != NULL)
        {
            fwrite(lista->consultas[i], sizeof(tConsulta), 1, file);
        }
    }
}

void DestroiListaConsultas(tListaConsultas *lista)
{
    for (int i = 0; i < lista->size; i++)
    {
        free(lista->consultas[i]);
    }
    free(lista->consultas);
    free(lista);
}
void DestroiListaConsultasGerais(tListaConsultas *lista)
{
    free(lista->consultas);
    free(lista);
}

void IncrementaQuantLesaoConsulta (tConsulta *consulta) {
    consulta->quantidadeLesoesLidas++;
}


void RemoveZerosEsquerdaC(char *data)
{
    int dia, mes, ano;

    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    sprintf(data, "%d/%d/%d", dia, mes, ano);
}

void ImprimeListaConsultaArquivoTexto (tListaConsultas *lista, FILE *file, int quant) {
tConsulta *consultaa = lista->consultas[0];

if (consultaa->diabetes == 0) {
    fprintf(file,"DIABETES: NAO\n");
} else {
    fprintf(file,"DIABETES: SIM\n");
}

if (consultaa->diabetes == 0) {
    fprintf(file,"FUMANTE: NAO\n");
} else {
    fprintf(file,"FUMANTE: SIM\n");
}

if (consultaa->diabetes == 0) {
    fprintf(file,"ALERGIA: NAO\n");
} else {
    fprintf(file,"ALERGIA: SIM\n");
}

if (consultaa->diabetes == 0) {
    fprintf(file,"HISTORICO DE CANCER: NAO\n");
} else {
    fprintf(file,"HISTORICO DE CANCER: SIM\n");
}

if (consultaa->diabetes == 0) {
    fprintf(file,"TIPO DE PELE: NAO\n");
} else {
    fprintf(file,"TIPO DE PELE: SIM\n");
}

fprintf(file,"QUANTIDADE DE CONSULTAS: %i\n", quant);
fprintf(file,"- - - - - - \n");

    for (int i = 0; i < quant; i++) {
        tConsulta *consulta = lista->consultas[i];
        if (consulta != NULL && strcmp(consulta,"")!= 0) {
         RemoveZerosEsquerdaC(consulta->dataconsulta);   
        fprintf(file,"DATA DA CONSULTA: \n",consulta->dataconsulta);
        fprintf(file,"QUANTIDADE DE LESOES GERADAS: %i\n",consulta->quantidadeLesoesLidas);
        fprintf(file,"- -\n");
        }
    }

}
