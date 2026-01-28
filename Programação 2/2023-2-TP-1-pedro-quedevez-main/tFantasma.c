#include <stdio.h>
#include <stdlib.h>
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tFantasma.h"

tfantasma *CriaFantasma(char tipofantasma, tPosicao *posicaoInicial)
{
    tfantasma *fantasma = (tfantasma *)calloc(1, sizeof(tfantasma));
    fantasma->tipoFantasma = tipofantasma;
    fantasma->posicaoAtual = posicaoInicial;
    return fantasma;
}

tlistafantasmas *CriaListaFantasmas(tMapa *mapa)
{
    tlistafantasmas *lista = (tlistafantasmas *)calloc(1, sizeof(tlistafantasmas));

    for (int i = 0; i < mapa->nLinhas - 1; i++)
    {
        for (int j = 0; j < mapa->nColunas; j++)
        {
            if (mapa->grid[i][j] == 'B')
            {
                tPosicao *posicaoInicialFantasma = CriaPosicao(i, j);
                AdicionaFantasmaLista(lista, CriaFantasma('B', posicaoInicialFantasma));
                AtualizaItemMapa(mapa, posicaoInicialFantasma, ' ');
            }
            else if (mapa->grid[i][j] == 'P')
            {
                tPosicao *posicaoInicialFantasma = CriaPosicao(i, j);
                AdicionaFantasmaLista(lista, CriaFantasma('P', posicaoInicialFantasma));
                AtualizaItemMapa(mapa, posicaoInicialFantasma, ' ');
            }
            else if (mapa->grid[i][j] == 'I')
            {
                tPosicao *posicaoInicialFantasma = CriaPosicao(i, j);
                AdicionaFantasmaLista(lista, CriaFantasma('I', posicaoInicialFantasma));
                AtualizaItemMapa(mapa, posicaoInicialFantasma, ' ');
            }
            else if (mapa->grid[i][j] == 'C')
            {
                tPosicao *posicaoInicialFantasma = CriaPosicao(i, j);
                AdicionaFantasmaLista(lista, CriaFantasma('C', posicaoInicialFantasma));
                AtualizaItemMapa(mapa, posicaoInicialFantasma, ' ');
            }
            else if (mapa->grid[i][j] == 'H')
            {
                tPosicao *posicaoInicialFantasma = CriaPosicao(i, j);
                AdicionaFantasmaLista(lista, CriaFantasma('H', posicaoInicialFantasma));
                AtualizaItemMapa(mapa, posicaoInicialFantasma, ' ');
            }
            else if (mapa->grid[i][j] == 'V')
            {
                tPosicao *posicaoInicialFantasma = CriaPosicao(i, j);
                AdicionaFantasmaLista(lista, CriaFantasma('V', posicaoInicialFantasma));
                AtualizaItemMapa(mapa, posicaoInicialFantasma, ' ');
            }
        }
    }
    return lista;
}

void AdicionaFantasmaLista(tlistafantasmas *lista, tfantasma *fantasma)
{
    lista->quantidadeFantasmas++;
    lista->listaFantasmas = (tfantasma **)realloc(lista->listaFantasmas, lista->quantidadeFantasmas * (sizeof(tfantasma *)));
    lista->listaFantasmas[lista->quantidadeFantasmas - 1] = fantasma;
}

bool PrintaFantasmaMapa(tMapa *mapa, tlistafantasmas *lista, int linha, int coluna)
{
    tPosicao *posicaoMapaComparar = CriaPosicao(linha, coluna);
    for (int i = 0; i < lista->quantidadeFantasmas; i++)
    {
        if (SaoIguaisPosicao(posicaoMapaComparar, lista->listaFantasmas[i]->posicaoAtual) == true)
        {

            printf("%c", lista->listaFantasmas[i]->tipoFantasma);

            DesalocaPosicao(posicaoMapaComparar);
            return true;
        }
    }
    DesalocaPosicao(posicaoMapaComparar);
    return false;
}

bool PrintaFantasmaMapaRelatorioSaida(tMapa *mapa, tlistafantasmas *lista, int linha, int coluna, FILE *RelatorioSaida)
{
    tPosicao *posicaoMapaComparar = CriaPosicao(linha, coluna);
    for (int i = 0; i < lista->quantidadeFantasmas; i++)
    {
        if (SaoIguaisPosicao(posicaoMapaComparar, lista->listaFantasmas[i]->posicaoAtual) == true)
        {

            fprintf(RelatorioSaida, "%c", lista->listaFantasmas[i]->tipoFantasma);

            DesalocaPosicao(posicaoMapaComparar);
            return true;
        }
    }
    DesalocaPosicao(posicaoMapaComparar);
    return false;
}

void MoveFantasmas(tMapa *mapa, tlistafantasmas *lista)
{
    for (int i = 0; i < lista->quantidadeFantasmas; i++)
    {
        if (lista->listaFantasmas[i]->tipoFantasma == 'B')
        {
            MoveFantasmaB(mapa, lista->listaFantasmas[i]);
        }
        else if (lista->listaFantasmas[i]->tipoFantasma == 'P')
        {
            MoveFantasmaP(mapa, lista->listaFantasmas[i]);
        }
        else if (lista->listaFantasmas[i]->tipoFantasma == 'I')
        {
            MoveFantasmaI(mapa, lista->listaFantasmas[i]);
        }
        else if (lista->listaFantasmas[i]->tipoFantasma == 'C')
        {
            MoveFantasmaC(mapa, lista->listaFantasmas[i]);
        }
        else if (lista->listaFantasmas[i]->tipoFantasma == 'H')
        {
            MoveFantasmaH(mapa, lista->listaFantasmas[i]);
        }
        else if (lista->listaFantasmas[i]->tipoFantasma == 'V')
        {
            MoveFantasmaV(mapa, lista->listaFantasmas[i]);
        }
    }
}

void MoveFantasmaH(tMapa *mapa, tfantasma *fantasma)
{

    tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) + 1));

    if (ObtemColunaPosicao(novaPosicao) == (ObtemNumeroColunasMapa(mapa) - 1))
    {
        DesalocaPosicao(novaPosicao);
        tPosicao *novaPosicao2 = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (1));
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao2;
        return;
    }
    DesalocaPosicao(fantasma->posicaoAtual);
    fantasma->posicaoAtual = novaPosicao;
    return;
}

void MoveFantasmaV(tMapa *mapa, tfantasma *fantasma)
{

    tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual) - 1, (ObtemColunaPosicao(fantasma->posicaoAtual)));

    if (ObtemLinhaPosicao(novaPosicao) == 0)
    {
        DesalocaPosicao(novaPosicao);
        tPosicao *novaPosicao2 = CriaPosicao(ObtemNumeroLinhasMapa(mapa) - 2, ObtemColunaPosicao(fantasma->posicaoAtual));
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao2;
        return;
    }
    DesalocaPosicao(fantasma->posicaoAtual);
    fantasma->posicaoAtual = novaPosicao;
    return;
}

void MoveFantasmaB(tMapa *mapa, tfantasma *fantasma)
{
    if (fantasma->bateuParede == 0)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) - 1));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 0)
            {
                fantasma->bateuParede = 1;
            }

            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) + 1));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
    else if (fantasma->bateuParede == 1)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) + 1));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 1)
            {
                fantasma->bateuParede = 0;
            }

            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) - 1));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
}

void MoveFantasmaP(tMapa *mapa, tfantasma *fantasma)
{
    if (fantasma->bateuParede == 0)
    {
        tPosicao *novaPosicao = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) - 1), ObtemColunaPosicao(fantasma->posicaoAtual));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 0)
            {
                fantasma->bateuParede = 1;
            }

            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) + 1), ObtemColunaPosicao(fantasma->posicaoAtual));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
    else if (fantasma->bateuParede == 1)
    {
        tPosicao *novaPosicao = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) + 1), ObtemColunaPosicao(fantasma->posicaoAtual));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 1)
            {
                fantasma->bateuParede = 0;
            }

            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) - 1), ObtemColunaPosicao(fantasma->posicaoAtual));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
}

void MoveFantasmaI(tMapa *mapa, tfantasma *fantasma)
{
    if (fantasma->bateuParede == 0)
    {
        tPosicao *novaPosicao = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) + 1), ObtemColunaPosicao(fantasma->posicaoAtual));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 0)
            {
                fantasma->bateuParede = 1;
            }
            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) - 1), ObtemColunaPosicao(fantasma->posicaoAtual));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
    else if (fantasma->bateuParede == 1)
    {
        tPosicao *novaPosicao = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) - 1), ObtemColunaPosicao(fantasma->posicaoAtual));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 1)
            {
                fantasma->bateuParede = 0;
            }
            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao((ObtemLinhaPosicao(fantasma->posicaoAtual) + 1), ObtemColunaPosicao(fantasma->posicaoAtual));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
}

void MoveFantasmaC(tMapa *mapa, tfantasma *fantasma)
{
    if (fantasma->bateuParede == 0)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) + 1));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 0)
            {
                fantasma->bateuParede = 1;
            }

            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) - 1));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
    else if (fantasma->bateuParede == 1)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) - 1));
        if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
            if (fantasma->bateuParede == 1)
            {
                fantasma->bateuParede = 0;
            }

            DesalocaPosicao(novaPosicao);
            tPosicao *novaPosicao2 = CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual), (ObtemColunaPosicao(fantasma->posicaoAtual) + 1));
            DesalocaPosicao(fantasma->posicaoAtual);
            fantasma->posicaoAtual = novaPosicao2;
            return;
        }
        DesalocaPosicao(fantasma->posicaoAtual);
        fantasma->posicaoAtual = novaPosicao;
        return;
    }
}

void DesalocaFantasma(tfantasma *fantasma)
{
    DesalocaPosicao(fantasma->posicaoAtual);
    free(fantasma);
}

void DesalocaListaFantasmas(tlistafantasmas *lista)
{
    for (int i = 0; i < lista->quantidadeFantasmas; i++)
    {
        DesalocaFantasma(lista->listaFantasmas[i]);
    }
    free(lista->listaFantasmas);
    free(lista);
}

tfantasma *ClonaFantasma(tfantasma *fantasmaOriginal)
{
    tPosicao *posicaoClonada = ClonaPosicao(fantasmaOriginal->posicaoAtual);
    tfantasma *fantasmaClone = CriaFantasma(fantasmaOriginal->tipoFantasma, posicaoClonada);
    fantasmaClone->bateuParede = fantasmaOriginal->bateuParede;
    return fantasmaClone;
}

tlistafantasmas *ClonaListaFantasmas(tlistafantasmas *listaOriginal)
{
    tlistafantasmas *listaClonada = (tlistafantasmas *)calloc(1, sizeof(tlistafantasmas));
    listaClonada->quantidadeFantasmas = listaOriginal->quantidadeFantasmas;
    listaClonada->listaFantasmas = (tfantasma **)calloc(listaClonada->quantidadeFantasmas, sizeof(tfantasma *));

    for (int i = 0; i < listaOriginal->quantidadeFantasmas; i++)
    {
        listaClonada->listaFantasmas[i] = ClonaFantasma(listaOriginal->listaFantasmas[i]);
    }

    return listaClonada;
}
