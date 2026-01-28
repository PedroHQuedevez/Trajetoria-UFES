#include "tMovimento.h"

tMovimento *CriaMovimento(int numeroDoMovimento, COMANDO comando, const char *acao)
{
    tMovimento *Movimento = (tMovimento *)calloc(1, sizeof(tMovimento));
    Movimento->numeroDoMovimento = numeroDoMovimento;
    Movimento->comando = comando;
    strcpy(Movimento->acao, acao);

    return Movimento;
}

// tMovimento *ClonaMovimento(tMovimento *movimento)
// {
//     tMovimento *MovimentoClonado = (tMovimento *)calloc(1, sizeof(tMovimento));
//     strcpy(MovimentoClonado->acao, movimento->acao);
//     MovimentoClonado->comando = movimento->comando;
//     MovimentoClonado->numeroDoMovimento = movimento->numeroDoMovimento;

//     return MovimentoClonado;
// }

int ObtemNumeroMovimento(tMovimento *movimento)
{
    return movimento->numeroDoMovimento;
}

COMANDO ObtemComandoMovimento(tMovimento *movimento)
{
    return movimento->comando;
}

char *ObtemAcaoMovimento(tMovimento *movimento)
{
    return movimento->acao;
}

void DesalocaMovimento(tMovimento *movimento)
{
    free(movimento); // talvez aqui precise de uma mexida;
}