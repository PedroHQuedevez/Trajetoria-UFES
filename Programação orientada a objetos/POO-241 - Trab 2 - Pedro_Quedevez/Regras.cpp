#include <iostream>
#include "Tokenizer.hpp"
#include "Regras.hpp"
#include "Excecao.hpp"
#include "ItemListaPublicacoes.hpp"

using namespace std;
using namespace cpp_util;

Regras::Regras()
{
}

Regras::Regras(string linhaCsv)
{
    Tokenizer tokens(linhaCsv, ';');
    vector<string> campos = tokens.remaining();
    try
    {

        this->setDataInicio(campos[0]);
        this->setDataFim(campos[1]);

        Tokenizer tokensQualis1(campos[2], '-');
        vector<string> qualis1 = tokensQualis1.remaining();
        for (string q : qualis1)
        {
            if (ordemQualisMap.find(q) == ordemQualisMap.end())
            {
                throw Excecao("Qualis desconhecido para regras de " + campos[0] + ": " + q + ".");
            }
        }
        this->setQualis1(qualis1);

        Tokenizer tokensPontos(campos[3], '-');
        vector<string> pontos = tokensPontos.remaining();
        this->setPontos(pontos);

        this->setQtdeAnosPontos(stoi(campos[4]));

        Tokenizer tokensQualis2(campos[5], '-');
        vector<string> qualis2 = tokensQualis2.remaining();
        this->setQualis2(qualis2);

        Tokenizer tokensQuantidadesMinimas(campos[6], '-');
        vector<string> quantidadesMinimas = tokensQuantidadesMinimas.remaining();
        vector<int> quantidadesMinimasInt;

        for (string s : quantidadesMinimas)
        {
            quantidadesMinimasInt.push_back(stoi(s));
        }

        this->setQuantidadesMinimas(quantidadesMinimasInt);
        this->setQtdeAnosArtigo(stoi(campos[7]));
        this->setPontuacaoMin(stof(campos[8]));
    }
    catch (Excecao e)
    {
        throw e;
    }
};

Regras Regras::getRegraAtual(vector<Regras> regras, int anoAtual)
{

    for (Regras r : regras)
    {
        Tokenizer tokensInicio(r.getDataInicio(), '/');
        vector<string> dataInicio = tokensInicio.remaining();
        Tokenizer tokensFim(r.getDataFim(), '/');
        vector<string> dataFim = tokensFim.remaining();

        if (anoAtual >= stoi(dataInicio[2]) && anoAtual <= stoi(dataFim[2]))
        {
            return r;
        }
    }

    Regras regrasNull = Regras();
    return regrasNull;
}

string Regras::getDataInicio()
{
    return this->dataInicio;
};

string Regras::getDataFim()
{
    return this->dataFim;
};

vector<string> Regras::getQualis1()
{
    return this->qualis1;
};

vector<string> Regras::getPontos()
{
    return this->pontos;
};

int Regras::getQtdeAnosPontos()
{
    return this->qtdeAnosPontos;
};

vector<string> Regras::getQualis2()
{
    return this->qualis2;
};

vector<int> Regras::getQuantidadesMinimas()
{
    return this->quantidadesMinimas;
};

int Regras::getQtdeAnosArtigo()
{
    return this->qtdeAnosArtigo;
};

float Regras::getPontuacaoMin()
{
    return this->pontuacaoMin;
};

void Regras::setDataInicio(string dataInicio)
{
    this->dataInicio = dataInicio;
};

void Regras::setDataFim(string dataFim)
{
    this->dataFim = dataFim;
};

void Regras::setQualis1(vector<string> qualis1)
{
    this->qualis1 = qualis1;
};

void Regras::setPontos(vector<string> pontos)
{
    this->pontos = pontos;
};

void Regras::setQtdeAnosPontos(int qtdeAnosPontos)
{
    this->qtdeAnosPontos = qtdeAnosPontos;
};

void Regras::setQualis2(vector<string> qualis2)
{
    this->qualis2 = qualis2;
};

void Regras::setQuantidadesMinimas(vector<int> quantidadesMinimas)
{
    this->quantidadesMinimas = quantidadesMinimas;
};

void Regras::setQtdeAnosArtigo(int qtdeAnosArtigo)
{
    this->qtdeAnosArtigo = qtdeAnosArtigo;
};

void Regras::setPontuacaoMin(float pontuacaoMin)
{
    this->pontuacaoMin = pontuacaoMin;
};

ostream &operator<<(ostream &r, Regras &regras)
{
    r << "Data Inicio: " << regras.getDataInicio() << endl;
    r << "Data Fim: " << regras.getDataFim() << endl;
    r << "Qualis1: ";
    for (string q : regras.getQualis1())
    {
        r << q << " ";
    }
    r << endl;
    r << "Pontos: ";
    for (string p : regras.getPontos())
    {
        r << p << " ";
    }
    r << endl;
    r << "Qtde Anos Pontos: " << regras.getQtdeAnosPontos() << endl;
    r << "Qualis2: ";
    for (string q : regras.getQualis2())
    {
        r << q << " ";
    }
    r << endl;
    r << "Quantidades Minimas: ";
    for (int q : regras.getQuantidadesMinimas())
    {
        r << q << " ";
    }
    r << endl;
    r << "Qtde Anos Artigo: " << regras.getQtdeAnosArtigo() << endl;
    r << "Pontuacao Min: " << regras.getPontuacaoMin() << endl;
    return r;
};