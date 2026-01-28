#include <stdio.h>
#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include "tFantasma.h"
#include "tUtils.h"
#include "tRelatorio.h"

int main(int argc, char *argv[])
{
    int comPoder = 0;
    int movimentosComPoder = 0;
    int comMataFantasmas = 0;
    int movimentosComMataFantasma = 0;

    // cria_pastas(argv[1]);
    if (argv[1] == NULL)
    {
        printf("ERRO: O diretório de arquivos de configuração nao foi informado\n  ");
        exit(1);
    }

    tMapa *mapa = CriaMapa(argv[1]);
    // PrintaMapa(mapa);
    tPosicao *posicaoPacman = ObtemPosicaoItemMapa(mapa, '>');
    tPacman *pacman = CriaPacman(posicaoPacman);
    tPacman *clonePacmanparapoderes = ClonaPacman(pacman);
    CriaTrilhaPacman(pacman, ObtemNumeroLinhasMapa(mapa), ObtemNumeroColunasMapa(mapa));
    
    AtualizaTrilhaPacman(pacman);
    RelatorioInicializacao(mapa, pacman, argv[1]);

    tlistafantasmas *listaFantasmas = CriaListaFantasmas(mapa);

    char comando;
    char path[1001];
    FILE *entrada;
    sprintf(path, "%s/entrada.txt", argv[1]);
    entrada = fopen(path, "r");

    if (entrada == NULL)
    {
        printf("ERRO: nao foi possível ler o arquivo %s", path);
        exit(1);
    }

    FILE *RelatorioSaida = AbreRelatorioSaida(argv[1]);

    while (fscanf(entrada, "%c\n", &comando) != -1)
    {
        // printf("%c\n", comando);
        COMANDO c;
        if (comando == 'a')
        {
            c = 0;
        }
        else if (comando == 'w')
        {
            c = 1;
        }
        else if (comando == 's')
        {
            c = 2;
        }
        else if (comando == 'd')
        {
            c = 3;
        }

        tPacman *pacmanClone = ClonaPacman(pacman);
        tlistafantasmas *listaClonada = ClonaListaFantasmas(listaFantasmas);

        //--------------------------------------------

        AtualizaPosicao(ObtemPosicaoPacman(clonePacmanparapoderes), ObtemPosicaoPacman(pacman));

        MoveClonePacman(clonePacmanparapoderes, mapa, c);

        if (PegouPoderPacman(mapa, ObtemPosicaoPacman(clonePacmanparapoderes)) == true)
        {
            comPoder = 1;
        }

        if (PegouPoderMatadorFantasma(mapa, ObtemPosicaoPacman(clonePacmanparapoderes)) == true) // adiciona o poder após o movimento
        {
            comMataFantasmas = 1;
        }

        // -------------------------------------------

        if (comPoder == 0)
        {
            MovePacman(pacman, mapa, c);
        }
        else if (comPoder == 1)
        {
            MovePacmanComPoder(pacman, mapa, c); // move sem ligar para as paredes do meio do mapa;

            movimentosComPoder++;
            if (movimentosComPoder == 15)
            {
                comPoder = 0;
                movimentosComPoder = 0;
                char item = ObtemItemMapa(mapa, pacman->posicaoAtual);
                if (item == '#') // verifica se no último movimento a posição do pacman representa uma parede;
                {
                    
                    //printf("\nmorreu na parede\n");
                    
                    MoveFantasmas(mapa, listaFantasmas);
                    EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
                    MataPacman(pacman);
                    MoveFantasmas(mapa,listaFantasmas);
                    EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
                    fprintf(RelatorioSaida, "Game over!\nPontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));
                    DesalocaPacman(pacmanClone);
                    DesalocaListaFantasmas(listaClonada);
                    break;
                }
            }
        }

        //--------------------------------------------

        MoveFantasmas(mapa, listaFantasmas);

        //--------------------------------------------

        if (comMataFantasmas == 0)
        {
            // nada pq já movimentou o pac;
        }
        else if (comMataFantasmas == 1)
        {   
            movimentosComMataFantasma++;
            if (MataFantasma(listaFantasmas, pacman, pacmanClone, listaClonada) == true) {
                comMataFantasmas = 0;
                movimentosComMataFantasma = 0;
            } // verifica se está na mesma posição do fantasma e desaloca o fantasma;
            
            if (movimentosComMataFantasma == 15)
            {
                comMataFantasmas = 0;
                movimentosComMataFantasma = 0;
            }
        }

        // -------------------------------------------
        // AdicionaContadorMovimentosPorDirecao(comando, pacman); // se eu deletar os contadores da main o scrip roda;
        //  não posso usar essa função dentro da pacman e nem modificar valores durante a função movepacman por que o script não aceita;

        if ((VerificaPerdeuJogo(mapa, pacman, listaFantasmas, pacmanClone, listaClonada) == true) || EstaVivoPacman(pacman) == 0)
        {
            if (EstaVivoPacman(pacman) == 0)
            {
                pacman->estaVivo = 0;

                InsereNovoMovimentoSignificativoPacman(pacman, c, "fim de jogo por encostar em um fantasma");
                // AdicionaContadorMovimentosSignificatos(pacman);
            }

            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacmanClone), ' ');
            EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
            fprintf(RelatorioSaida, "Game over!\nPontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));
            AtualizaTrilhaPacman(pacman);
            DesalocaPacman(pacmanClone);
            DesalocaListaFantasmas(listaClonada);
            break;
        }

        if (VerificaGanhouJogo(mapa, pacman) == true)
        {

            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacmanClone), ' ');
            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');
            EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
            fprintf(RelatorioSaida, "Voce venceu!\nPontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));
            AtualizaTrilhaPacman(pacman);
            DesalocaPacman(pacmanClone);
            DesalocaListaFantasmas(listaClonada);

            break;
        }

        // AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacmanClone), ' ');
        // AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), '>');

        EscreveRelatorioSaida(RelatorioSaida, comando, mapa, listaFantasmas, pacman);
        AtualizaTrilhaPacman(pacman);

        DesalocaPacman(pacmanClone);
        DesalocaListaFantasmas(listaClonada);
    }

    fclose(entrada);

    FechaRelatorioSaida(RelatorioSaida);

    RelatorioEstatisticas(pacman, argv[1]);

    RelatorioRanking(pacman, argv[1]);

    RelatorioResumo(pacman, argv[1]);

    SalvaTrilhaPacman(pacman);

    DesalocaPacman(clonePacmanparapoderes);
    DesalocaPacman(pacman);
    DesalocaMapa(mapa);
    DesalocaListaFantasmas(listaFantasmas);

    return 0;
}
