#include "tPosicao.h"

tPosicao *CriaPosicao(int linha, int coluna)
{
    tPosicao *Posicao = (tPosicao *)calloc(1, sizeof(tPosicao));
    Posicao->linha = linha;
    Posicao->coluna = coluna;
    return Posicao;
}

tPosicao *ClonaPosicao(tPosicao *posicao)
{
    tPosicao *PosicaoClonada = (tPosicao *)calloc(1, sizeof(tPosicao));
    PosicaoClonada->coluna = posicao->coluna;
    PosicaoClonada->linha = posicao->linha;
    return PosicaoClonada;
}

int ObtemLinhaPosicao(tPosicao *posicao)
{
    return posicao->linha;
}

int ObtemColunaPosicao(tPosicao *posicao)
{
    return posicao->coluna;
}

void AtualizaPosicao(tPosicao *posicaoAtual, tPosicao *posicaoNova)
{
    posicaoAtual->coluna = posicaoNova->coluna;
    posicaoAtual->linha = posicaoNova->linha;
}

bool SaoIguaisPosicao(tPosicao *posicao1, tPosicao *posicao2)
{
    if ((posicao1->linha == posicao2->linha) && posicao1->coluna == posicao2->coluna)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DesalocaPosicao(tPosicao *posicao)
{
    free(posicao);
}