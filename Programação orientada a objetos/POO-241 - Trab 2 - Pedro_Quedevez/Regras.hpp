#ifndef REGRAS_HPP
#define REGRAS_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Regras
{
private:
    string dataInicio;
    string dataFim;
    vector<string> qualis1;
    vector<string> pontos;
    int qtdeAnosPontos;
    vector<string> qualis2;
    vector<int> quantidadesMinimas;
    int qtdeAnosArtigo;
    float pontuacaoMin;

public:
    Regras();
    Regras(string linhaCsv);
    string getDataInicio();
    string getDataFim();
    vector<string> getQualis1();
    vector<string> getPontos();
    int getQtdeAnosPontos();
    vector<string> getQualis2();
    vector<int> getQuantidadesMinimas();
    int getQtdeAnosArtigo();
    float getPontuacaoMin();
    void setDataInicio(string dataInicio);
    void setDataFim(string dataFim);
    void setQualis1(vector<string> qualis1);
    void setPontos(vector<string> pontos);
    void setQtdeAnosPontos(int qtdeAnosPontos);
    void setQualis2(vector<string> qualis2);
    void setQuantidadesMinimas(vector<int> quantidadesMinimas);
    void setQtdeAnosArtigo(int qtdeAnosArtigo);
    void setPontuacaoMin(float pontuacaoMin);
    static Regras getRegraAtual(vector<Regras> regras, int anoAtual);
};

ostream &operator<<(ostream &r, Regras &regras);

#endif