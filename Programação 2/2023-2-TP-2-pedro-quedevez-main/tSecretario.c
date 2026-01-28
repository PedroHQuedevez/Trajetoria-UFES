#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tSecretario.h"

struct ListaSecretarios
{
    tSecretario **Secretarios;
    int allocated;
    int size;
};

struct Secretario
{
    char nome[101];
    char cpf[16];
    char dataNascimento[12];
    char telefone[16];
    char genero[10];
    char user[21];
    char senha[21];
    int admin;
};

struct SecretarioInicio {
    char nome[100];
    char cpf[15];
    int dia;
    int mes;
    int ano;
    char telefone[15];
    char genero[13];
    char user[20];
    char senha[20];
    char admin[7];
};

tListaSecretarios *CriaListaSecretarios()
{
    tListaSecretarios *lista = (tListaSecretarios *)calloc(1, sizeof(tListaSecretarios));
    lista->Secretarios = (tSecretario **)calloc(1, sizeof(tSecretario *));
    return lista;
}

tSecretario *CriaSecretario()
{
    tSecretario *Secretario = (tSecretario *)calloc(1, sizeof(tSecretario));
    return Secretario;
}

int CadastrarSecretarioArquivo(tListaSecretarios *lista, FILE *file)
{
    lista->size++;
    lista->Secretarios = (tSecretario **)realloc(lista->Secretarios, sizeof(tSecretario *) * lista->size);
    tSecretario *Secretario = CriaSecretario();
    int elementosLidos;
    elementosLidos = fread(Secretario, sizeof(tSecretario), 1, file);
    lista->Secretarios[lista->size - 1] = Secretario;
    // PrintaSecretario(lista->Secretarios[lista->size - 1]);
    // printf("\n%i\n", lista);
    return elementosLidos;
}

int VerificaCpfExisteS(char *cpf, tListaSecretarios *lista)
{
    if (lista != NULL)
    {
        for (int i = 0; i < (lista->size - 1); i++)
        {
            if (lista->Secretarios[i] != NULL)
            {
                if (strcmp(cpf, lista->Secretarios[i]->cpf) == 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void RemoveZerosEsquerdaS(char *data)
{
    int dia, mes, ano;

    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    sprintf(data, "%d/%d/%d", dia, mes, ano);
}

void CadastrarSecretarioTeclado(tListaSecretarios *lista)
{
    lista->size++;
    lista->Secretarios = (tSecretario **)realloc(lista->Secretarios, sizeof(tSecretario *) * (lista->size));

    tSecretario *Secretario = CriaSecretario();
    printf("#################### CADASTRO SECRETARIO #######################\n");
    printf("NOME COMPLETO: ");
    scanf("\n%101[^\n]", Secretario->nome);
    printf("\n");
    printf("CPF:");
    scanf("\n%15[^\n]", Secretario->cpf);
    printf("\n");
    printf("DATA DE NASCIMENTO: ");
    scanf("\n%11[^\n]", Secretario->dataNascimento);
    printf("\n");
    printf("TELEFONE: ");
    scanf("\n%15[^\n]", Secretario->telefone);
    printf("\n");
    printf("GENERO: ");
    scanf("\n%10[^\n]", Secretario->genero);
    printf("\n");
    printf("NOME DE USUARIO: ");
    scanf("\n%21[^\n]", Secretario->user);
    printf("\n");
    printf("SENHA: ");
    scanf("\n%21[^\n]", Secretario->senha);
    printf("\n");
    printf("NIVEL DE ACESSO: ");
    char nivelacesso[10];
    scanf("\n%21[^\n]", nivelacesso);
    if (strcmp(nivelacesso, "ADMIN") == 0)
    {
        Secretario->admin = 1;
    }
    else
    {
        Secretario->admin = 0;
    }
    printf("\n");

    RemoveZerosEsquerdaS(Secretario->dataNascimento);

    if (VerificaCpfExisteS(Secretario->cpf, lista) == 1)
    {
        free(Secretario);
        lista->size--;
    }
    else
    {
        lista->Secretarios[lista->size - 1] = Secretario;

        // PrintaSecretario(lista->Secretarios[lista->size - 1]);

        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("############################################################\n");
        char lixo;
        scanf("\n%c", &lixo);
    }
}

int ProcuraLoginS(tListaSecretarios *lista, char *login)
{
    for (int i = 0; i < lista->size; i++)
    {

        if (strcmp(lista->Secretarios[i]->user, login) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int ProcuraSenhaS(tListaSecretarios *lista, char *senha)
{
    for (int i = 0; i < lista->size; i++)
    {

        if (strcmp(lista->Secretarios[i]->senha, senha) == 0)
        {
            return 1;
        }
    }
    return 0;
}

tSecretario *RealizaLoginS(tListaSecretarios *lista, char *login, char *senha)
{
    for (int i = 0; i < lista->size; i++)
    {
        if ((strcmp(lista->Secretarios[i]->senha, senha) == 0) && ((strcmp(lista->Secretarios[i]->user, login) == 0)))
        {
            return lista->Secretarios[i];
        }
    }
    return NULL;
}
void PrintaSecretario(tSecretario *Secretario)
{
    printf("%s\n", Secretario->nome);
    printf("%s\n", Secretario->cpf);
    printf("%s\n", Secretario->dataNascimento);
    printf("%s\n", Secretario->telefone);
    printf("%s\n", Secretario->genero);
    printf("%s\n", Secretario->user);
    printf("%s\n", Secretario->senha);
    printf("%i\n", Secretario->admin);
}

int VerificaNivelAcesso(tSecretario *s)
{
    return s->admin;
}

void DestroiSecretario(tSecretario *s)
{
    free(s);
}

void DestroiListaSecretario(tListaSecretarios *l)
{
    for (int i = 0; i < l->size; i++)
    {
        DestroiSecretario(l->Secretarios[i]);
    }
    free(l->Secretarios);
    free(l);
}

void EscreveBinarioSecretarios(tListaSecretarios *lista, FILE *file)
{

    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
    }

    for (int i = 0; i < lista->size; i++)
    {
        fwrite(lista->Secretarios[i], sizeof(tSecretario), 1, file);
    }
    fclose(file);
}

void PrimeiroCadastro(tListaSecretarios *lista)
{
    lista->size++;
    lista->Secretarios = (tSecretario **)realloc(lista->Secretarios, sizeof(tSecretario *) * (lista->size));

    tSecretario *Secretario = CriaSecretario();
    printf("#################### CADASTRO SECRETARIO #######################\n");
    printf("NOME COMPLETO: ");
    scanf("\n%101[^\n]", Secretario->nome);
    printf("\n");
    printf("CPF:");
    scanf("\n%15[^\n]", Secretario->cpf);
    printf("\n");
    printf("DATA DE NASCIMENTO: ");
    scanf("\n%11[^\n]", Secretario->dataNascimento);
    printf("\n");
    printf("TELEFONE: ");
    scanf("\n%15[^\n]", Secretario->telefone);
    printf("\n");
    printf("GENERO: ");
    scanf("\n%10[^\n]", Secretario->genero);
    printf("\n");
    printf("NOME DE USUARIO: ");
    scanf("\n%21[^\n]", Secretario->user);
    printf("\n");
    printf("SENHA: ");
    scanf("\n%21[^\n]", Secretario->senha);
    printf("\n");
    printf("NIVEL DE ACESSO: ");
    char nivelacesso[10];
    scanf("\n%21[^\n]", nivelacesso);
    if (strcmp(nivelacesso, "ADMIN") == 0)
    {
        Secretario->admin = 1;
    }
    else
    {
        Secretario->admin = 0;
    }
    printf("\n");

    lista->Secretarios[lista->size - 1] = Secretario;
}

void ImprimeListaSecretariosArquivoTexto (tListaSecretarios *lista, char *path) {
    char arquivo[1001];
    sprintf(arquivo, "%s/secretarios.txt", path);
    FILE *file = fopen(arquivo, "w");
    
    for (int i = 0; i < lista->size; i++) {
        tSecretario *secretario = lista->Secretarios[i];
        if (secretario != NULL && strcmp(secretario->nome,"")!= 0) {
        fprintf(file,"NOME: %s\n",secretario->nome);
        fprintf(file,"CPF: %s\n", secretario->cpf);
        fprintf(file,"DATA DE NASCIMENTO: %s\n", secretario->dataNascimento);
        fprintf(file,"TELEFONE: %s\n",secretario->telefone);
        fprintf(file,"GENERO: %s\n",secretario->genero);
        fprintf(file,"NOME DE USUARIO: %s\n", secretario->user);
        if (secretario->admin == 1) {
        fprintf(file,"NIVEL DE ACESSO: ADMIN\n");
        } else {
            fprintf(file,"NIVEL DE ACESSO: USER\n");
        }
        fprintf(file,"- - - - - -\n");
        }
    }
    fclose(file);
}


int CadastrarSecretarioInicioArquivo(tListaSecretarios *lista, FILE *file)
{
    lista->size++;
    lista->Secretarios = (tSecretario **)realloc(lista->Secretarios, sizeof(tSecretario *) * lista->size);
    tSecretarioInicio *secretarioinicio = (tSecretarioInicio*) calloc (1, sizeof(tSecretarioInicio));
    int elementosLidos;
    elementosLidos = fread(secretarioinicio, sizeof(tSecretarioInicio), 1, file);

    tSecretario *s = CriaSecretario();
    char dataNascimento[16];
    sprintf(dataNascimento, "%i/%i/%i", secretarioinicio->dia,secretarioinicio->mes,secretarioinicio->ano);

    strcpy(s->nome, secretarioinicio->nome);
    strcpy(s->cpf, secretarioinicio->cpf);
    strcpy(s->dataNascimento, dataNascimento);
    strcpy(s->telefone, secretarioinicio->telefone);
    strcpy(s->genero, secretarioinicio->genero);
    strcpy(s->user, secretarioinicio->user);
    if (strcmp(secretarioinicio->admin, "ADMIN") == 0) {
    s->admin = 1;
    } else {
    s->admin = 0;
    }
    strcpy(s->user, secretarioinicio->user);
    strcpy(s->senha, secretarioinicio->senha);
    free(secretarioinicio);
    lista->Secretarios[lista->size - 1] = s;
    // PrintaSecretario(lista->Secretarios[lista->size - 1]);
    // printf("\n%i\n", lista);
    return elementosLidos;
}

