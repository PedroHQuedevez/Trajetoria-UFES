#include "tMapa.h"

tMapa *CriaMapa(const char *caminhoConfig)
{
    tMapa *mapa = (tMapa *)calloc(1, sizeof(tMapa));
    // mapa->grid[0] = (char *)malloc(sizeof(char));
    // mapa->nLinhas = 1;
    char path[1001];
    char char_lido;

    FILE *arq;

    sprintf(path, "%s/mapa.txt", caminhoConfig);

    arq = fopen(path, "r");

    if (arq == NULL)
    {
        printf("ERRO: nao foi possível ler o arquivo %s", path);
        exit(1);
    }

    fscanf(arq, "%d", &mapa->nMaximoMovimentos);

    int NumeroColunaAuxiliar = 0;
    while (fscanf(arq, "%c", &char_lido) != -1)
    {
        if (char_lido == '*')
        {
            mapa->nFrutasAtual++;
        }

        if (char_lido == '\n')
        {
            mapa->nLinhas++;
            mapa->grid = (char **)realloc(mapa->grid, (mapa->nLinhas) * (sizeof(char *)));
            mapa->grid[mapa->nLinhas - 1] = NULL;
            mapa->nColunas = NumeroColunaAuxiliar;
            NumeroColunaAuxiliar = 0;
            // printf("\n");
        }
        else
        {
            NumeroColunaAuxiliar++;
            mapa->grid[mapa->nLinhas - 1] = (char *)realloc(mapa->grid[mapa->nLinhas - 1], (NumeroColunaAuxiliar) * sizeof(char));
            mapa->grid[mapa->nLinhas - 1][NumeroColunaAuxiliar - 1] = char_lido;
            // printf("*\n");
            // printf("%c", mapa->grid[mapa->nLinhas - 1][NumeroColunaAuxiliar - 1]);
        }
    }
    //-----------------------------------------------------------------------
    // Não tem como saber como a pessoa que implementou lidou com o último /n na leitura dela, tem várias formas de fazer e não tem como adivinhar!!!!!
    free(mapa->grid[mapa->nLinhas - 1]);
    mapa->grid = (char **)realloc(mapa->grid, (mapa->nLinhas - 1) * (sizeof(char *)));
    mapa->nLinhas--;

    //-----------------------------------------------------------------------

    tPosicao *posicaoTunel = ObtemPosicaoItemMapa(mapa, '@');
    tPosicao *acesso1 = NULL;
    tPosicao *acesso2 = NULL;
    int acesso = 1;
    if (posicaoTunel != NULL)
    {
        for (int i = 0; i < mapa->nLinhas; i++)
        {
            for (int j = 0; j < mapa->nColunas; j++)
            {
                if ((mapa->grid[i][j] == '@') && (acesso == 1))
                {
                    acesso1 = CriaPosicao(i, j);
                    
                    acesso++;
                }
                else if ((mapa->grid[i][j] == '@') && (acesso == 2))
                {
                    acesso2 = CriaPosicao(i, j);
                    
                }
            }
        }
        if (acesso1 != NULL && acesso2 != NULL) {
        mapa->tunel = CriaTunel(ObtemLinhaPosicao(acesso1), ObtemColunaPosicao(acesso1), ObtemLinhaPosicao(acesso2), ObtemColunaPosicao(acesso2));
        }
        DesalocaPosicao(acesso1);
        DesalocaPosicao(acesso2);
        DesalocaPosicao(posicaoTunel);
    }

    fclose(arq);
    return mapa;
}

void PrintaMapa(tMapa *mapa)
{
    for (int i = 0; i < mapa->nLinhas; i++)
    {
        for (int j = 0; j < mapa->nColunas; j++)
        {
            printf("%c", mapa->grid[i][j]);
        }
        printf("\n");
    }
}

void DesalocaMapa(tMapa *mapa)
{
    if (mapa != NULL)
    {
        for (int i = 0; i < mapa->nLinhas; i++)
        {
            free(mapa->grid[i]);
        }
        free(mapa->grid);
        if (mapa->tunel != NULL)
        {
            DesalocaTunel(mapa->tunel);
        }

        free(mapa);
    }
}

tPosicao *ObtemPosicaoItemMapa(tMapa *mapa, char item)
{

    for (int i = 0; i < mapa->nLinhas; i++)
    {
        for (int j = 0; j < mapa->nColunas; j++)
        {
            if (mapa->grid[i][j] == item)
            {
                tPosicao *posicaoItemMapa = CriaPosicao(i, j);
                return posicaoItemMapa;
            }
        }
    }
    // printf("\n***não achou\n");
    return NULL;
}

tTunel *ObtemTunelMapa(tMapa *mapa)
{
    return mapa->tunel;
}

char ObtemItemMapa(tMapa *mapa, tPosicao *posicao)
{
    return mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)];
}

int ObtemNumeroLinhasMapa(tMapa *mapa)
{
    return mapa->nLinhas;
}

int ObtemNumeroColunasMapa(tMapa *mapa)
{
    return mapa->nColunas;
}

int ObtemQuantidadeFrutasIniciaisMapa(tMapa *mapa)
{
    return mapa->nFrutasAtual; // aqui não faz muito sentido;
}

int ObtemNumeroMaximoMovimentosMapa(tMapa *mapa)
{
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa *mapa, tPosicao *posicao)
{
    if ((mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] == '*'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool EncontrouParedeMapa(tMapa *mapa, tPosicao *posicao)
{
    if ((mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] == '#'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AtualizaItemMapa(tMapa *mapa, tPosicao *posicao, char item)
{
    mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] = item;
    return true;
}

bool PossuiTunelMapa(tMapa *mapa)
{
    if (mapa->tunel != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AcessouTunelMapa(tMapa *mapa, tPosicao *posicao)
{
    if (PossuiTunelMapa(mapa) == true)
    {
        return EntrouTunel(mapa->tunel, posicao);
    }
    else
    {
        return false;
    }
    return false;
}

void EntraTunelMapa(tMapa *mapa, tPosicao *posicao)
{
    LevaFinalTunel(mapa->tunel, posicao);
}