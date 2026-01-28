#ifndef RECREDENCIAMENTO_HPP
#define RECREDENCIAMENTO_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Docente.hpp"
#include "Regras.hpp"
#include "Global.hpp"

class Recredenciamento
{
private:
    string nomeDocente;
    double pontuacao;
    string recrendenciado;

public:
    Recredenciamento(string nomeDocente, double pontuacao, string recrendenciado);
    string getNomeDocente();
    double getPontuacao();
    string getRecrendenciado();
    void setNomeDocente(string nomeDocente);
    void setPontuacao(double pontuacao);
    void setRecrendenciado(string recrendenciado);
    static float calculaPontuacao(vector<float> &vetorPontos, Docente docente, int quantAnos, int anoAtual);
    static vector<float> constroiVetorPontos(vector<Regras> regras, int anoAtual);
    static bool verificaPubMin(vector<Regras> regras, Docente docente, int anoAtual);
    static string verificaEventoRecredenciamento(Docente docente, int anoAtual);
    static vector<Recredenciamento> constroiListaRecredenciamento(vector<Docente> docentes, vector<Regras> regras, int anoAtual);
    static vector<Recredenciamento> ordenaListaRecredenciamento(vector<Recredenciamento> listaRecredenciamento);
};

ostream &operator<<(ostream &o, Recredenciamento &r);

#endif