#ifndef _TFANTASMA_H
#define _TFANTASMA_H

#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"

typedef struct fantasma
{
    char tipoFantasma;
    tPosicao *posicaoAtual;
    int bateuParede;
} tfantasma;

typedef struct listafantasmas
{
    tfantasma **listaFantasmas;
    int quantidadeFantasmas;
} tlistafantasmas;

tfantasma *CriaFantasma(char tipofantasma, tPosicao *posicaoInicial);
tlistafantasmas *CriaListaFantasmas(tMapa *mapa);
void AdicionaFantasmaLista(tlistafantasmas *lista, tfantasma *fantasma);
void MoveFantasmas(tMapa *mapa, tlistafantasmas *lista);
void MoveFantasmaB(tMapa *mapa, tfantasma *fantasma);
void MoveFantasmaP(tMapa *mapa, tfantasma *fantasma);
void MoveFantasmaI(tMapa *mapa, tfantasma *fantasma);
void MoveFantasmaC(tMapa *mapa, tfantasma *fantasma);
void MoveFantasmaV(tMapa *mapa, tfantasma *fantasma);
void MoveFantasmaH(tMapa *mapa, tfantasma *fantasma);
void DestroiFantasma(tfantasma *fantasma);
void DestroiListaFantasma(tlistafantasmas *lista);
bool PrintaFantasmaMapa(tMapa *mapa, tlistafantasmas *lista, int linha, int coluna);
bool PrintaFantasmaMapaRelatorioSaida(tMapa *mapa, tlistafantasmas *lista, int linha, int coluna, FILE *RelatorioSaida);
void DesalocaListaFantasmas(tlistafantasmas *lista);
tlistafantasmas *ClonaListaFantasmas(tlistafantasmas *listaOriginal);
void DesalocaFantasma(tfantasma *fantasma);
#endif