#include <stdio.h>
#include <stdlib.h>
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include "tFantasma.h"
#include "tUtils.h"

void PrintaMapaComMovimentacaoFantasmasRelatorioSaida(tMapa *mapa, tlistafantasmas *lista, FILE *arq, tPacman *pacman)
{
    for (int i = 0; i < mapa->nLinhas; i++)
    {
        for (int j = 0; j < mapa->nColunas; j++)
        {
            if (PrintaFantasmaMapaRelatorioSaida(mapa, lista, i, j, arq) == false)
            {
                if (mapa->grid[i][j] == '>' && (EstaVivoPacman(pacman) == 0))
                {
                    fprintf(arq, " ");
                }
                else
                {
                    fprintf(arq, "%c", mapa->grid[i][j]);
                }
            }
        }
        fprintf(arq, "\n");
    }
}

bool VerificaPerdeuJogo(tMapa *mapa, tPacman *pacman, tlistafantasmas *listaFantasmas, tPacman *pacmanClonado, tlistafantasmas *listaClonada)
{
    for (int i = 0; i < listaFantasmas->quantidadeFantasmas; i++)
    {
        if (SaoIguaisPosicao(pacman->posicaoAtual, listaFantasmas->listaFantasmas[i]->posicaoAtual) == true)
        {

            MataPacman(pacman);
            return true;
        }
    }

    for (int i = 0; i < listaFantasmas->quantidadeFantasmas; i++)
    {
        if ((SaoIguaisPosicao(pacman->posicaoAtual, listaClonada->listaFantasmas[i]->posicaoAtual) == true) &&
            (SaoIguaisPosicao(pacmanClonado->posicaoAtual, listaFantasmas->listaFantasmas[i]->posicaoAtual) == true))
        {

            MataPacman(pacman);
            return true;
        }
    }
    int numerosMovimentosTotais = pacman->nMovimentosBaixo + pacman->nMovimentosCima + pacman->nMovimentosDireita + pacman->nMovimentosEsquerda;
    if (numerosMovimentosTotais == mapa->nMaximoMovimentos)
    {
        // MataPacman(pacman);
        return true;
    }
    return false;
}

bool VerificaGanhouJogo(tMapa *mapa, tPacman *pacman)
{
    int numeroFrutasComidasTotal = pacman->nFrutasComidasBaixo + pacman->nFrutasComidasCima + pacman->nFrutasComidasDireita + pacman->nFrutasComidasEsquerda;
    if ((numeroFrutasComidasTotal == ObtemQuantidadeFrutasIniciaisMapa(mapa)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void cria_pastas(char *path)
{
    char comando[100];

    sprintf(comando, "mkdir %s", "saida");
    system(comando);
}

void AdicionaContadorMovimentosPorDirecao(char direcao, tPacman *Pacman)
{
    if (direcao == 'a')
    {
        Pacman->nMovimentosEsquerda++;
    }
    else if (direcao == 'w')
    {
        Pacman->nMovimentosCima++;
    }
    else if (direcao == 's')
    {
        Pacman->nMovimentosBaixo++;
    }
    else if (direcao == 'd')
    {
        Pacman->nMovimentosDireita++;
    }
}

void AdicionaContadorFrutasPorDirecao(char direcao, tPacman *pacman)
{
    if (direcao == 'a')
    {
        pacman->nFrutasComidasEsquerda++;
    }
    else if (direcao == 'w')
    {
        pacman->nFrutasComidasCima++;
    }
    else if (direcao == 's')
    {
        pacman->nFrutasComidasBaixo++;
    }
    else if (direcao == 'd')
    {
        pacman->nFrutasComidasDireita++;
    }
}

void AdicionaContadorColisoesPorDirecao(char direcao, tPacman *pacman)
{
    if (direcao == 'a')
    {
        pacman->nColisoesParedeEsquerda++;
    }
    else if (direcao == 'w')
    {
        pacman->nColisoesParedeCima++;
    }
    else if (direcao == 's')
    {
        pacman->nColisoesParedeBaixo++;
    }
    else if (direcao == 'd')
    {
        pacman->nColisoesParedeDireita++;
    }
}

void AdicionaContadorMovimentosSignificatos(tPacman *pacman)
{
    pacman->nMovimentosSignificativos++;
}

void SeriaParteDaMovePacman(tPacman *pacman, tMapa *mapa, COMANDO comando)
{
    if (comando == 0)
    {
        if ((ObtemColunaPosicao(pacman->posicaoAtual) - 1) >= 0)
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) - 1);
            if (EncontrouParedeMapa(mapa, novaPosicao) == true)
            {
                pacman->nColisoesParedeEsquerda++;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
                pacman->nMovimentosEsquerda++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (EncontrouComidaMapa(mapa, novaPosicao) == true)
            {
                pacman->nFrutasComidasEsquerda++;
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                pacman->nMovimentosEsquerda++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, novaPosicao) == true) // momento em que entra no túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosEsquerda++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, pacman->posicaoAtual) == true) // saindo do túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosEsquerda++;
                AtualizaTrilhaPacman(pacman);
            }
            else
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosEsquerda++;
                AtualizaTrilhaPacman(pacman);
            }

            DesalocaPosicao(novaPosicao);
            pacman->nMovimentosSignificativos++;
        }
    }
    else if (comando == 1)
    {
        if ((ObtemLinhaPosicao(pacman->posicaoAtual) - 1) >= 0)
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) - 1, ObtemColunaPosicao(pacman->posicaoAtual));
            if (EncontrouParedeMapa(mapa, novaPosicao) == true)
            {
                pacman->nColisoesParedeCima++;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
                pacman->nMovimentosCima++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (EncontrouComidaMapa(mapa, novaPosicao) == true)
            {
                pacman->nFrutasComidasCima++;
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                pacman->nMovimentosCima++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, novaPosicao) == true) // momento em que entra no túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosCima++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, pacman->posicaoAtual) == true) // saindo do túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosCima++;
                AtualizaTrilhaPacman(pacman);
            }
            else
            {

                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosCima++;
                AtualizaTrilhaPacman(pacman);
            }
            DesalocaPosicao(novaPosicao);
            pacman->nMovimentosSignificativos++;
        }
    }
    else if (comando == 2)
    {
        if ((ObtemLinhaPosicao(pacman->posicaoAtual) + 1) < ObtemNumeroLinhasMapa(mapa))
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) + 1, ObtemColunaPosicao(pacman->posicaoAtual));
            if (EncontrouParedeMapa(mapa, novaPosicao) == true)
            {
                pacman->nColisoesParedeBaixo++;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
                pacman->nMovimentosBaixo++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (EncontrouComidaMapa(mapa, novaPosicao) == true)
            {
                pacman->nFrutasComidasBaixo++;
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                pacman->nMovimentosBaixo++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, novaPosicao) == true) // momento em que entra no túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosBaixo++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, pacman->posicaoAtual) == true) // saindo do túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosBaixo++;
                AtualizaTrilhaPacman(pacman);
            }
            else
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosBaixo++;
                AtualizaTrilhaPacman(pacman);
            }
            DesalocaPosicao(novaPosicao);
            pacman->nMovimentosSignificativos++;
        }
    }
    else if (comando == 3)
    {
        if ((ObtemColunaPosicao(pacman->posicaoAtual) + 1) < ObtemNumeroColunasMapa(mapa))
        {
            tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) + 1);
            if (EncontrouParedeMapa(mapa, novaPosicao) == true)
            {
                pacman->nColisoesParedeDireita++;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
                pacman->nMovimentosDireita++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (EncontrouComidaMapa(mapa, novaPosicao) == true)
            {
                pacman->nFrutasComidasDireita++;
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                pacman->nMovimentosDireita++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, novaPosicao) == true) // momento em que entra no túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosDireita++;
                AtualizaTrilhaPacman(pacman);
            }
            else if (AcessouTunelMapa(mapa, pacman->posicaoAtual) == true) // saindo do túnel;
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosDireita++;
                AtualizaTrilhaPacman(pacman);
            }
            else
            {
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "nada");
                pacman->nMovimentosDireita++;
                AtualizaTrilhaPacman(pacman);
            }

            DesalocaPosicao(novaPosicao);
            pacman->nMovimentosSignificativos++;
        }
    }
}

void IniciaTrilhaComFlag(tPacman *pacman)
{
    for (int i = 0; i < (pacman->nLinhasTrilha * pacman->nColunasTrilha); i++)
    {
        *pacman->trilha[i] = -1;
    }
}

bool PegouPoderPacman(tMapa *mapa, tPosicao *posicao)
{
    char item = ObtemItemMapa(mapa, posicao);
    if (item == '+')
    {
        AtualizaItemMapa(mapa, posicao, ' ');
        return true;
    }
    else
    {
        return false;
    }
}

bool PegouPoderMatadorFantasma(tMapa *mapa, tPosicao *posicao)
{
    char item = ObtemItemMapa(mapa, posicao);
    if (item == 'x')
    {
        AtualizaItemMapa(mapa, posicao, ' ');
        return true;
    }
    else
    {
        return false;
    }
}

void MovePacmanComPoder(tPacman *pacman, tMapa *mapa, COMANDO comando)
{

    if (comando == 0)
    {

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) - 1);

        if (EncontrouComidaMapa(mapa, novaPosicao) == true)
        {
            pacman->nFrutasComidasEsquerda++;
            AtualizaItemMapa(mapa, novaPosicao, ' ');

            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
            // pacman->nMovimentosSignificativos++;
        }
        else if (PossuiTunelMapa(mapa) == true)
        {

            if (EntrouTunel(ObtemTunelMapa(mapa), novaPosicao) == true)
            {
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
            }
        }
        else if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
        }

        pacman->nMovimentosEsquerda++;
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        // AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 1)
    {

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) - 1, ObtemColunaPosicao(pacman->posicaoAtual));

        //AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), ' ');

        if (EncontrouComidaMapa(mapa, novaPosicao) == true)
        {
            pacman->nFrutasComidasCima++;
            AtualizaItemMapa(mapa, novaPosicao, ' ');

            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
            // pacman->nMovimentosSignificativos++;
        }
        else if (PossuiTunelMapa(mapa) == true)
        {

            if (EntrouTunel(ObtemTunelMapa(mapa), novaPosicao) == true)
            {
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
            }
        }
        else if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
        }

        pacman->nMovimentosCima++;
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        // AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 2)
    {

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) + 1, ObtemColunaPosicao(pacman->posicaoAtual));
        //AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), ' ');

        if (EncontrouComidaMapa(mapa, novaPosicao) == true)
        {
            pacman->nFrutasComidasBaixo++;
            AtualizaItemMapa(mapa, novaPosicao, ' ');

            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
            // pacman->nMovimentosSignificativos++;
        }
        else if (PossuiTunelMapa(mapa) == true)
        {

            if (EntrouTunel(ObtemTunelMapa(mapa), novaPosicao) == true)
            {
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
            }
        }
        else if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
        }

        pacman->nMovimentosBaixo++;
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        // AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 3)
    {

        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) + 1);
        //AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), ' ');

        if (EncontrouComidaMapa(mapa, novaPosicao) == true)
        {
            pacman->nFrutasComidasDireita++;
            AtualizaItemMapa(mapa, novaPosicao, ' ');

            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
            // pacman->nMovimentosSignificativos++;
        }
        else if (PossuiTunelMapa(mapa) == true)
        {

            if (EntrouTunel(ObtemTunelMapa(mapa), novaPosicao) == true)
            {
                EntraTunelMapa(mapa, novaPosicao);
                AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
            }
        }
        else if (EncontrouParedeMapa(mapa, novaPosicao) == true)
        {
        }

        pacman->nMovimentosDireita++;
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        // AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
        DesalocaPosicao(novaPosicao);
    }
}

void MoveClonePacman(tPacman *pacman, tMapa *mapa, COMANDO comando)
{
    if (comando == 0)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) - 1);
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 1)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) - 1, ObtemColunaPosicao(pacman->posicaoAtual));
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 2)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual) + 1, ObtemColunaPosicao(pacman->posicaoAtual));
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        DesalocaPosicao(novaPosicao);
    }
    else if (comando == 3)
    {
        tPosicao *novaPosicao = CriaPosicao(ObtemLinhaPosicao(pacman->posicaoAtual), ObtemColunaPosicao(pacman->posicaoAtual) + 1);
        AtualizaPosicao(pacman->posicaoAtual, novaPosicao);
        DesalocaPosicao(novaPosicao);
    }
}

bool MataFantasma(tlistafantasmas *listaFantasmas, tPacman *pacman, tPacman *pacmanClonado, tlistafantasmas *listaClonada)
{

    for (int i = 0; i < listaFantasmas->quantidadeFantasmas; i++)
    {
        if (SaoIguaisPosicao(pacman->posicaoAtual, listaFantasmas->listaFantasmas[i]->posicaoAtual) == true)
        {
            DesalocaFantasma(listaFantasmas->listaFantasmas[i]);
            int indiceUltimoFantasma = listaFantasmas->quantidadeFantasmas;
            listaFantasmas->listaFantasmas[i] = listaFantasmas->listaFantasmas[indiceUltimoFantasma - 1];
            listaFantasmas->listaFantasmas[indiceUltimoFantasma - 1] = NULL;
            listaFantasmas->quantidadeFantasmas--;
            return true;
            
        }
    }

    for (int i = 0; i < listaFantasmas->quantidadeFantasmas; i++)
    {
        if ((SaoIguaisPosicao(pacman->posicaoAtual, listaClonada->listaFantasmas[i]->posicaoAtual) == true) &&
            (SaoIguaisPosicao(pacmanClonado->posicaoAtual, listaFantasmas->listaFantasmas[i]->posicaoAtual) == true))
        {
            DesalocaFantasma(listaFantasmas->listaFantasmas[i]);
            int indiceUltimoFantasma = listaFantasmas->quantidadeFantasmas;
            listaFantasmas->listaFantasmas[i] = listaFantasmas->listaFantasmas[indiceUltimoFantasma - 1];
            listaFantasmas->listaFantasmas[indiceUltimoFantasma - 1] = NULL;
            listaFantasmas->quantidadeFantasmas--;
            return true;
            break;
        }
    }

return false;
}


