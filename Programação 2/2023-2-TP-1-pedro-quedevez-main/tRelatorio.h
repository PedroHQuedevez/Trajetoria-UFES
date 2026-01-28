#ifndef _RELATORIO_H
#define _RELATORIO_H

void RelatorioInicializacao(tMapa *mapa, tPacman *Pacman, char *caminhoConfig);
void RelatorioEstatisticas(tPacman *pacman, char *caminhoConfig);
FILE *AbreRelatorioSaida(char *caminhoConfig);
void EscreveRelatorioSaida(FILE *RelatorioSaida, char comando, tMapa *mapa, tlistafantasmas *listaFantasmas, tPacman *pacman);
void FechaRelatorioSaida(FILE *RelatorioSaida);
void RelatorioRanking(tPacman *pacman, char *caminhoConfig);
void RelatorioResumo(tPacman *pacman, char *caminhoConfig);
void PrintaMapaSaida(FILE *relatorioSaida, char comando, tMapa *mapa, tlistafantasmas *listaFantasmas, tPacman *pacman);
#endif