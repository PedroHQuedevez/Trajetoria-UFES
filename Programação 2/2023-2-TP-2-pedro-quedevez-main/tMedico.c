#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tMedico.h"

struct ListaMedicos
{
    tMedico **medicos;
    int allocated;
    int size;
};

struct Medico
{
    char nome[101];
    char cpf[15];
    char dataNascimento[11];
    char telefone[15];
    char genero[10];
    char user[21];
    char senha[21];
    char CRM[13];
};

char *RetornaNomeMedico(tMedico *m)
{
    return m->nome;
}

char *RetornaCRMMedico(tMedico *m)
{
    return m->CRM;
}

tListaMedicos *CriaListaMedicos()
{
    tListaMedicos *lista = (tListaMedicos *)calloc(1, sizeof(tListaMedicos));
    lista->medicos = (tMedico **)calloc(1, sizeof(tMedico *));
    return lista;
}

tMedico *CriaMedico()
{
    tMedico *medico = (tMedico *)calloc(1, sizeof(tMedico));
    return medico;
}

int CadastrarMedicoArquivo(tListaMedicos *lista, FILE *file)
{
    lista->size++;
    lista->medicos = (tMedico **)realloc(lista->medicos, sizeof(tMedico *) * lista->size);
    tMedico *Medico = CriaMedico();
    int elementosLidos;
    elementosLidos = fread(Medico, sizeof(tMedico), 1, file);
    if (Medico != NULL)
    {
        lista->medicos[lista->size - 1] = Medico;
    }
    else
    {
        lista->size--;
    }
    return elementosLidos;
}

tMedico *LeMedicoArquivo (tListaMedicos *ListaMedicos,FILE *FileMedicosBin) {
    tMedico *MedicoPrintar;
    fread(MedicoPrintar, sizeof(tMedico), 1, FileMedicosBin);

}

int VerificaCpfExisteM(char *cpf, tListaMedicos *lista)
{
    if (lista != NULL)
    {
        for (int i = 0; i < (lista->size - 1); i++)
        {
            if (lista->medicos[i] != NULL)
            {
                if (strcmp(cpf, lista->medicos[i]->cpf) == 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void RemoveZerosEsquerdaM(char *data)
{
    int dia, mes, ano;

    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    sprintf(data, "%d/%d/%d", dia, mes, ano);
}

void CadastrarMedicoTeclado(tListaMedicos *lista)
{
    lista->size++;
    lista->medicos = (tMedico **)realloc(lista->medicos, sizeof(tMedico *) * lista->size);

    tMedico *medico = CriaMedico();
    printf("#################### CADASTRO MEDICO #######################\n");
    printf("NOME COMPLETO: ");
    scanf("\n%101[^\n]", medico->nome);
    printf("\n");
    printf("CPF:");
    scanf("\n%15[^\n]", medico->cpf);
    printf("\n");
    printf("DATA DE NASCIMENTO: ");
    scanf("\n%11[^\n]", medico->dataNascimento);
    printf("\n");
    printf("TELEFONE: ");
    scanf("\n%15[^\n]", medico->telefone);
    printf("\n");
    printf("GENERO: ");
    scanf("\n%10[^\n]", medico->genero);
    printf("\n");
    printf("CRM:");
    scanf("\n%13[^\n]", medico->CRM);
    printf("\n");
    printf("NOME DE USUARIO: ");
    scanf("\n%21[^\n]", medico->user);
    printf("\n");
    printf("SENHA: ");
    scanf("\n%21[^\n]", medico->senha);
    printf("\n");

    RemoveZerosEsquerdaM(medico->dataNascimento);

    if (VerificaCpfExisteM(medico->cpf, lista) == 1)
    {
        free(medico);
        lista->size--;
    }
    else
    {
        lista->medicos[lista->size - 1] = medico;

        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("############################################################");
        char lixo;
        scanf("\n%c", &lixo);
    }
}

void PrintaMedico(tMedico *Medico)
{
    printf("%s\n", Medico->nome);
    printf("%s\n", Medico->cpf);
    printf("%s\n", Medico->dataNascimento);
    printf("%s\n", Medico->telefone);
    printf("%s\n", Medico->genero);
    printf("%s\n", Medico->user);
    printf("%s\n", Medico->senha);
    printf("%s\n", Medico->CRM);
}

int ProcuraLoginM(tListaMedicos *lista, char *login)
{
    for (int i = 0; i < lista->size; i++)
    {

        if (strcmp(lista->medicos[i]->user, login) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int ProcuraSenhaM(tListaMedicos *lista, char *senha)
{
    for (int i = 0; i < lista->size; i++)
    {

        if (strcmp(lista->medicos[i]->senha, senha) == 0)
        {
            return 1;
        }
    }
    return 0;
}

tMedico *RealizaLoginM(tListaMedicos *lista, char *login, char *senha)
{
    for (int i = 0; i < lista->size; i++)
    {
        if ((strcmp(lista->medicos[i]->senha, senha) == 0) && ((strcmp(lista->medicos[i]->user, login) == 0)))
        {
            return lista->medicos[i];
        }
    }
    return NULL;
}
void DestroiMedico(tMedico *s)
{
    free(s);
}

void DestroiListaMedico(tListaMedicos *l)
{
    for (int i = 0; i < l->size; i++)
    {
        DestroiMedico(l->medicos[i]);
    }
    free(l->medicos);
    free(l);
}

void EscreveBinarioMedicos(tListaMedicos *lista, FILE *file)
{

    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
    }

    for (int i = 0; i < lista->size; i++)
    {
        if (lista->medicos[i] != NULL)
        {
            fwrite(lista->medicos[i], sizeof(tMedico), 1, file);
        }
    }
    fclose(file);
}

void ImprimeListaMedicoArquivoTexto (tListaMedicos *lista, char *path) {
    char arquivo[1001];
    sprintf(arquivo, "%s/medicos.txt", path);
    FILE *file = fopen(arquivo, "w");
    
    for (int i = 0; i < lista->size -1; i++) {
        tMedico *medico = lista->medicos[i];
        if (medico != NULL && strcmp(medico->nome,"")!= 0 ) {
        fprintf(file,"NOME: %s\n",medico->nome);
        fprintf(file,"CPF: %s\n", medico->cpf);
        fprintf(file,"DATA DE NASCIMENTO: %s\n", medico->dataNascimento);
        fprintf(file,"TELEFONE: %s\n",medico->telefone);
        fprintf(file,"GENERO: %s\n",medico->genero);
        fprintf(file,"CRM: %s\n", medico->CRM);
        fprintf(file,"NOME DE USUARIO: %s\n", medico->user);
        fprintf(file,"- - - - - -\n");
        }
    }
    fclose(file);
}