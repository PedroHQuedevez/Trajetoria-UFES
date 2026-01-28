#include <stdio.h>
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include "tFantasma.h"
#include "tUtils.h"
#include "tRelatorio.h"

void RelatorioInicializacao(tMapa *mapa, tPacman *Pacman, char *caminhoConfig)
{
    char path[1001];

    FILE *arq;

    sprintf(path, "inicializacao.txt");

    arq = fopen(path, "w");

    for (int i = 0; i < mapa->nLinhas; i++)
    {
        for (int j = 0; j < mapa->nColunas; j++)
        {
            fprintf(arq, "%c", mapa->grid[i][j]);
        }
        fprintf(arq, "\n");
    }

    fprintf(arq, "Pac-Man comecara o jogo na linha %d e coluna %d\n", (Pacman->posicaoAtual->linha) + 1, (Pacman->posicaoAtual->coluna) + 1);
    fclose(arq);
}

//--------------------------------------------------------------------------------------------------------------------------------------------

void RelatorioEstatisticas(tPacman *pacman, char *caminhoConfig)
{
    char path[1001];

    FILE *arq;

    sprintf(path, "estatisticas.txt");

    arq = fopen(path, "w");

    fprintf(arq, "Numero de movimentos: %d\n", ObtemNumeroAtualMovimentosPacman(pacman));
    fprintf(arq, "Numero de movimentos sem pontuar: %d\n", ObtemNumeroMovimentosSemPontuarPacman(pacman));
    fprintf(arq, "Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(pacman));
    fprintf(arq, "Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(pacman));
    fprintf(arq, "Numero de movimentos para cima: %d\n", ObtemNumeroMovimentosCimaPacman(pacman));
    fprintf(arq, "Numero de movimentos para esquerda: %d\n", ObtemNumeroMovimentosEsquerdaPacman(pacman));
    fprintf(arq, "Numero de movimentos para direita: %d\n", ObtemNumeroMovimentosDireitaPacman(pacman));

    fclose(arq);
}

//--------------------------------------------------------------------------------------------------------------------------------------------

FILE *AbreRelatorioSaida(char *caminhoConfig)
{
    char path[1001];

    FILE *arq;

    sprintf(path, "saida.txt");

    arq = fopen(path, "w");

    return arq;
}

void PrintaMapaSaida(FILE *relatorioSaida, char comando, tMapa *mapa, tlistafantasmas *listaFantasmas, tPacman *pacman)
{

    fprintf(relatorioSaida, "Estado do jogo apos o movimento '%c':\n", comando);
    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++)
    {
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++)
        {
            tPosicao *posicaoVerificar = CriaPosicao(i, j);
            if (PrintaFantasmaMapaRelatorioSaida(mapa, listaFantasmas, i, j, relatorioSaida) == false)
            {
                if ((SaoIguaisPosicao(pacman->posicaoAtual, posicaoVerificar) == true) && (EstaVivoPacman(pacman) == 0))
                {   char item = ObtemItemMapa(mapa,posicaoVerificar);
                    
                    if ( item == '#') 
                    {
                        fprintf(relatorioSaida, "#");    
                    } else 
                    {
                    fprintf(relatorioSaida, " ");
                    }
                    
                }
                else if ((SaoIguaisPosicao(pacman->posicaoAtual, posicaoVerificar) == true) && (EstaVivoPacman(pacman) == 1))
                {
                    fprintf(relatorioSaida, ">");
                }

                else
                {
                    fprintf(relatorioSaida, "%c", mapa->grid[i][j]);
                }
            }
            DesalocaPosicao(posicaoVerificar);
        }
        fprintf(relatorioSaida, "\n");
    }
    fprintf(relatorioSaida, "Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(pacman));
}

void EscreveRelatorioSaida(FILE *RelatorioSaida, char comando, tMapa *mapa, tlistafantasmas *listaFantasmas, tPacman *pacman)
{
    // fprintf(RelatorioSaida, "Estado do jogo apos o movimento '%c':\n", comando);
    PrintaMapaSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
    // fprintf(RelatorioSaida, "Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(pacman));
}

void FechaRelatorioSaida(FILE *RelatorioSaida)
{
    fclose(RelatorioSaida);
}

//--------------------------------------------------------------------------------------------------------------------------------------------

typedef struct ranking
{
    char movimento;
    int comidasPegas;
    int colisoesParede;
    int vezesUtilizado;
} tRanking;

typedef struct rankings
{
    tRanking **listaRankings;
} tRankings;

bool VerificaMaiorRanking(tRanking *r1, tRanking *r2)
{
    if (r1->comidasPegas > r2->comidasPegas)
    {
        return true;
    }
    else if (r1->comidasPegas < r2->comidasPegas)
    {
        return false;
    }

    if (r1->comidasPegas == r2->comidasPegas)
    {
        if (r1->colisoesParede < r2->colisoesParede)
        {
            return true;
        }
        else if (r1->colisoesParede > r2->colisoesParede)
        {
            return false;
        }
    }

    if ((r1->comidasPegas == r2->comidasPegas) && (r1->colisoesParede == r2->colisoesParede))
    {
        if (r1->vezesUtilizado > r2->vezesUtilizado)
        {
            return true;
        }
        else if (r1->vezesUtilizado < r2->vezesUtilizado)
        {
            return false;
        }
    }

    if ((r1->comidasPegas == r2->comidasPegas) && (r1->colisoesParede == r2->colisoesParede) && (r1->vezesUtilizado == r2->vezesUtilizado))
    {
        if (r1->movimento < r2->movimento)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// void TrocaRankingsPosicao(tRanking *r1, tRanking *r2)
// {
//     tRanking *rankingAuxiliar = r1;
//     r1 = r2;
//     r2 = rankingAuxiliar;
// }

void RelatorioRanking(tPacman *pacman, char *caminhoConfig)
{
    char path[1001];

    FILE *arq;

    sprintf(path, "ranking.txt");

    arq = fopen(path, "w");

    tRankings *rankings = (tRankings *)calloc(1, sizeof(tRankings));

    rankings->listaRankings = (tRanking **)calloc(4, sizeof(tRanking *));

    rankings->listaRankings[0] = (tRanking *)calloc(1, sizeof(tRanking));
    rankings->listaRankings[0]->movimento = 's';
    rankings->listaRankings[0]->comidasPegas = ObtemNumeroFrutasComidasBaixoPacman(pacman);
    rankings->listaRankings[0]->colisoesParede = ObtemNumeroColisoesParedeBaixoPacman(pacman);
    rankings->listaRankings[0]->vezesUtilizado = ObtemNumeroMovimentosBaixoPacman(pacman);

    rankings->listaRankings[1] = (tRanking *)calloc(1, sizeof(tRanking));
    rankings->listaRankings[1]->movimento = 'w';
    rankings->listaRankings[1]->comidasPegas = ObtemNumeroFrutasComidasCimaPacman(pacman);
    rankings->listaRankings[1]->colisoesParede = ObtemNumeroColisoesParedeCimaPacman(pacman);
    rankings->listaRankings[1]->vezesUtilizado = ObtemNumeroMovimentosCimaPacman(pacman);

    rankings->listaRankings[2] = (tRanking *)calloc(1, sizeof(tRanking));
    rankings->listaRankings[2]->movimento = 'a';
    rankings->listaRankings[2]->comidasPegas = ObtemNumeroFrutasComidasEsquerdaPacman(pacman);
    rankings->listaRankings[2]->colisoesParede = ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
    rankings->listaRankings[2]->vezesUtilizado = ObtemNumeroMovimentosEsquerdaPacman(pacman);

    rankings->listaRankings[3] = (tRanking *)calloc(1, sizeof(tRanking));
    rankings->listaRankings[3]->movimento = 'd';
    rankings->listaRankings[3]->comidasPegas = ObtemNumeroFrutasComidasDireitaPacman(pacman);
    rankings->listaRankings[3]->colisoesParede = ObtemNumeroColisoesParedeDireitaPacman(pacman);
    rankings->listaRankings[3]->vezesUtilizado = ObtemNumeroMovimentosDireitaPacman(pacman);

    // for (int i = 0; i < 4; i++)
    // {
    //     fprintf(arq, "%c,%d,%d,%d\n", rankings->listaRankings[i]->movimento, rankings->listaRankings[i]->comidasPegas, rankings->listaRankings[i]->colisoesParede, rankings->listaRankings[i]->vezesUtilizado);
    // }
    // fprintf(arq, "\n");

    for (int i = 0; i < 4; i++)
    {
        for (int j = i; j < 4; j++)
        {
            if (VerificaMaiorRanking(rankings->listaRankings[i], rankings->listaRankings[j]) == false)
            {
                tRanking *aux = rankings->listaRankings[i];
                rankings->listaRankings[i] = rankings->listaRankings[j];
                rankings->listaRankings[j] = aux;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        fprintf(arq, "%c,%d,%d,%d\n", rankings->listaRankings[i]->movimento, rankings->listaRankings[i]->comidasPegas, rankings->listaRankings[i]->colisoesParede, rankings->listaRankings[i]->vezesUtilizado);
    }

    for (int i = 0; i < 4; i++)
    {
        free(rankings->listaRankings[i]);
    }
    free(rankings->listaRankings);
    free(rankings);
    fclose(arq);
}

//--------------------------------------------------------------------------------------------------------------------------------------------
char RetornaComandoRelatorioResumo(COMANDO comando)
{
    if (comando == 0)
    {
        return 'a';
    }
    else if (comando == 1)
    {
        return 'w';
    }
    else if (comando == 2)
    {
        return 's';
    }
    else if (comando == 3)
    {
        return 'd';
    }
    return 'a';
}

void RelatorioResumo(tPacman *pacman, char *caminhoConfig)
{
    char path[1001];

    FILE *arq;

    sprintf(path, "resumo.txt");

    arq = fopen(path, "w");

    for (int i = 0; i < ObtemNumeroMovimentosSignificativosPacman(pacman); i++)
    {
        // printf("%s %d\n", pacman->historicoDeMovimentosSignificativos[i]->acao, i);

        if (strcmp(pacman->historicoDeMovimentosSignificativos[i]->acao, "nada") == 0)
        {
            continue;
        }

        if (strcmp(pacman->historicoDeMovimentosSignificativos[i]->acao, "pegou comida") == 0)
        {
            fprintf(arq, "Movimento %d (%c) pegou comida\n", (ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i])+1), RetornaComandoRelatorioResumo(pacman->historicoDeMovimentosSignificativos[i]->comando));
        }

        if (strcmp(pacman->historicoDeMovimentosSignificativos[i]->acao, "colidiu com a parede") == 0)
        {
            fprintf(arq, "Movimento %d (%c) colidiu com a parede\n", (ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i])+1), RetornaComandoRelatorioResumo(pacman->historicoDeMovimentosSignificativos[i]->comando));
        }

        if (strcmp(pacman->historicoDeMovimentosSignificativos[i]->acao, "fim de jogo por encostar em um fantasma") == 0)
        {
            fprintf(arq, "Movimento %d (%c) fim de jogo por encostar em um fantasma\n", (ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i])), RetornaComandoRelatorioResumo(pacman->historicoDeMovimentosSignificativos[i]->comando));
        }
    }

    fclose(arq);
}
