#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tLesoes.h"
#include "tMedico.h"

struct Listalesoes
{
    tLesao **lesoes;
    int allocated;
    int size;
};

struct Lesao
{
    char rotulo[6];
    char diaginosticoclinico[30];
    char regiao[30];
    int tamanho;
    int cirurgia;
    int crioterapia;
    int origem;
};

tListaLesoes *CriaListaLesoes()
{
    tListaLesoes *lista = (tListaLesoes *)calloc(1, sizeof(tListaLesoes));
    lista->lesoes = (tLesao **)calloc(1, sizeof(tLesao *));
    return lista;
}

tLesao *CriaLesao()
{
    tLesao *lesao = (tLesao *)calloc(1, sizeof(tLesao));
    lesao->cirurgia = -1;
    lesao->crioterapia = -1;
    lesao->tamanho = -1;
    return lesao;
}

void CadastrarLesaoArquivo(tListaLesoes *lista, FILE *file, tListaLesoes *listalesaogerais)
{
    lista->size++;
    lista->lesoes = (tLesao **)realloc(lista->lesoes, sizeof(tLesao *) * lista->size);

    listalesaogerais->size++;
    listalesaogerais->lesoes = (tLesao **)realloc(listalesaogerais->lesoes, sizeof(tLesao *) * listalesaogerais->size);

    tLesao *Lesao = CriaLesao();
    int elementosLidos;
    elementosLidos = fread(Lesao, sizeof(tLesao), 1, file);
    Lesao->origem = 0;
    if ((Lesao != NULL) && (Lesao->tamanho > 0))
    {
        lista->lesoes[lista->size - 1] = Lesao;
        listalesaogerais->lesoes[listalesaogerais->size - 1] = Lesao;
    }
    else
    {
        lista->size--;
        listalesaogerais->size--;
    }
}

// void CadastrarLesaoGeraisArquivo(FILE *file, tListaLesoes *listalesaogerais)
// {
//     listalesaogerais->size++;
//     listalesaogerais->lesoes = (tLesao **)realloc(listalesaogerais->lesoes, sizeof(tLesao *) * listalesaogerais->size);

//     tLesao *Lesao = CriaLesao();
//     int elementosLidos;
//     elementosLidos = fread(Lesao, sizeof(tLesao), 1, file);
//     if ((Lesao != NULL) && (Lesao->tamanho > 0))
//     {
//         listalesaogerais->lesoes[lista->size - 1] = Lesao;
//     }
//     else
//     {
//         listalesaogerais->size--;
//     }
// }

void AdicionaLesaoListaLesao(tListaLesoes *lista, tLesao *lesao)
{
    if (lista == NULL)
    {
        lista = CriaListaLesoes();
    }

    lista->size++;
    lista->lesoes = (tLesao **)realloc(lista->lesoes, sizeof(tLesao *) * lista->size);

    lista->lesoes[lista->size - 1] = lesao;
}

void CadastraLesaoTeclado(tPaciente *paciente, tListaLesoes *lesoesgerais, int quantLesoesConsulta)
{
    tListaLesoes *lista = RetornaListaLesoesPaciente(paciente);

    if (lista == NULL)
    {
        lista = CriaListaLesoes();
    }

    lista->size++;
    lista->lesoes = (tLesao **)realloc(lista->lesoes, sizeof(tLesao *) * lista->size);

    tLesao *lesao = CriaLesao();

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");
    printf("DIAGNOSTICO CLINICO:\n");
    scanf("\n%30[^\n]", lesao->diaginosticoclinico);
    printf("REGIAO DO CORPO:\n");
    scanf("\n%30[^\n]", lesao->regiao);
    printf("TAMANHO:\n");
    scanf("\n%i", &lesao->tamanho);
    printf("ENVIAR PARA CIRURGIA\n");
    scanf("\n%i", &lesao->cirurgia);
    printf("ENVIAR PARA CRIOTERAPIA:\n");
    scanf("\n%i", &lesao->crioterapia);

    char rotulo[6];
    sprintf(rotulo, "L%i", quantLesoesConsulta);
    strcpy(lesao->rotulo, rotulo);
    lesao->origem = 1;
    lista->lesoes[lista->size - 1] = lesao;
    AdicionaLesaoListaLesao(lesoesgerais, lesao);

    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
}

int VerificaExisteCasoCirurgico(tListaLesoes *lista)
{
    for (int i = 0; i < lista->size; i++)
    {
        if (lista->lesoes[i]->cirurgia == 1)
        {
            return 1;
        }
    }
    return 0;
}

void AuxiliaArquivoBiopsiaTela(tPaciente *paciente) // para o secretario realizando consulta
{

    tListaLesoes *lista = RetornaListaLesoesPaciente(paciente);
    for (int i = 0; i < lista->size; i++)
    {
        tLesao *lesao = lista->lesoes[i];
        if (lesao->cirurgia == 1 && lesao->origem == 1)
        {
            printf("%s - %s - %s - %iMM\n", lesao->rotulo, lesao->diaginosticoclinico, lesao->regiao, lesao->tamanho);
        }
    }
}

void AuxiliaArquivoBiopsiaArquivo(tPaciente *paciente, FILE *file)
{
    tListaLesoes *lista = RetornaListaLesoesPaciente(paciente);
    for (int i = 0; i < lista->size; i++)
    {
        tLesao *lesao = lista->lesoes[i];
        if (lesao->cirurgia == 1 && lesao->origem == 1)
        {
            fprintf(file, "%s - %s - %s - %iMM\n", lesao->rotulo, lesao->diaginosticoclinico, lesao->regiao, lesao->tamanho);
        }
    }
}

void EscreveListaLesaoBinario(tListaLesoes *lista, FILE *file)
{
    if ((lista != NULL) && (lista->lesoes != NULL))
        for (int i = 0; i < lista->size; i++)
        {
            if (lista->lesoes[i] != NULL)
            {
                fwrite(lista->lesoes[i], sizeof(tLesao), 1, file);
            }
        }
}

int CalculaTamMedioLesoes(tListaLesoes *listaLesoesgerais)
{
    int totaltamanhos = 0;
    if (listaLesoesgerais->lesoes != NULL)
    {
        for (int i = 0; i < listaLesoesgerais->size; i++)
        {
            if (listaLesoesgerais->lesoes[i] != NULL && listaLesoesgerais->lesoes[i]->tamanho != -1 && listaLesoesgerais->lesoes[i]->tamanho != 0)
            {
                totaltamanhos = totaltamanhos + listaLesoesgerais->lesoes[i]->tamanho;
            }
        }
    }

    if (listaLesoesgerais->size == 0)
    {
        listaLesoesgerais->size = 1;
    }
    return totaltamanhos / listaLesoesgerais->size;
}
int CalculaTotalLesoes(tListaLesoes *listaLesoesgerais)
{
    if (listaLesoesgerais->lesoes != NULL)
    {
        return listaLesoesgerais->size;
    }
    return 0;
}
int CalculaTotalCirurgias(tListaLesoes *listaLesoesgerais)
{
    int count = 0;
    if (listaLesoesgerais->lesoes != NULL)
    {
        for (int i = 0; i < listaLesoesgerais->size; i++)
        {
            if (listaLesoesgerais->lesoes[i] != NULL && listaLesoesgerais->lesoes[i]->cirurgia != -1)
            {
                if (listaLesoesgerais->lesoes[i]->cirurgia == 1)
                {
                    count++;
                }
            }
        }
    }

    return count;
}
int CalculaTotalCrioterapia(tListaLesoes *listaLesoesgerais)
{
    int count = 0;
    if (listaLesoesgerais->lesoes != NULL)
    {
        for (int i = 0; i < listaLesoesgerais->size; i++)
        {
            if (listaLesoesgerais->lesoes[i] != NULL)
            {
                if (listaLesoesgerais->lesoes[i]->crioterapia == 1 && listaLesoesgerais->lesoes[i]->crioterapia != -1)
                {
                    count++;
                }
            }
        }
    }

    return count;
}

void DestroiListaLesoes(tListaLesoes *lista)
{
    for (int i = 0; i < lista->size; i++)
    {
        free(lista->lesoes[i]);
    }
    free(lista->lesoes);
    free(lista);
}

void DestroiListaLesoesGerais(tListaLesoes *lista)
{
    free(lista->lesoes);
    free(lista);
}

void printaListaLesoes(tListaLesoes *lista)
{
    for (int i = 0; i < lista->size; i++)
    {
        printf("\n\n********************\n%s %s %s %i\n***********************\n\n",
               lista->lesoes[i]->rotulo, lista->lesoes[i]->diaginosticoclinico,
               lista->lesoes[i]->regiao, lista->lesoes[i]->tamanho);
    }
}

void ImprimeListaLesaoArquivoTexto (tListaLesoes *lista, FILE *file, int quantImprimir) {

    for (int i = 0; i < quantImprimir; i++) {
        tLesao *Lesao = lista->lesoes[i];
        if (Lesao != NULL && strcmp(Lesao->diaginosticoclinico,"")!= 0) {
        fprintf(file,"ROTULO: %s\n", Lesao->rotulo);
        fprintf(file,"DIAGNOSTICO CLINICO: %s\n",Lesao->diaginosticoclinico);
        fprintf(file,"REGIAO DO CORPO: %s\n",Lesao->regiao);
        fprintf(file,"TAMANHO: %i\n",Lesao->tamanho);
        
        if (Lesao->cirurgia == 0) {
    fprintf(file,"ENVIADO PARA CIRURGIA: NAO\n");
} else {
    fprintf(file,"ENVIADO PARA CIRURGIA: SIM\n");
}
    
      if (Lesao->crioterapia == 0) {
    fprintf(file,"ENVIADO PARA CRIOTERAPIA: NAO\n");
} else {
    fprintf(file,"ENVIADO PARA CRIOTERAPIA: SIM\n");
}

        fprintf(file,"- -\n");
        }
    }

}
