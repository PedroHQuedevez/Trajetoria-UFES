#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "StringUtils.hpp"
#include "Veiculo.hpp"
#include "Tokenizer.hpp"
#include "DateUtils.hpp"
#include "Publicacao.hpp"
#include "Excecao.hpp"

using namespace cpp_util;
using namespace std;

Veiculo::Veiculo() //
{
}

Veiculo::Veiculo(string csvline)
{

    Tokenizer tokens(csvline, ';');
    vector<string> campos = tokens.remaining();

    for (int i = 0; i < campos.size(); i++)
    {
        campos[i] = trim(campos[i]);
    }

    try
    {
        if (campos[2] == "P")
        {
            this->setSigla(campos[0]);
            if (siglasUtilizadas.find(campos[0]) != siglasUtilizadas.end())
            {
                throw Excecao("Código repetido para Veículo: " + campos[0] + ".");
            }
            this->setNome(campos[1]);
            this->setTipo(campos[2]);

            if (trim(campos[2]) != "P" && trim(campos[2]) != "C")
            {
                throw Excecao("Tipo de veículo desconhecido para veículo " + campos[0] + ": " + campos[2] + ".");
            }

            campos[3] = trocarVirgulaPorPonto(campos[3]);
            this->setFatorDeImpacto(stof(campos[3]));
            this->setIssn(campos[4]);
            this->publicacoes = vector<Publicacao>();
            siglasUtilizadas.insert(trim(campos[0]));
        }
        else if (campos[2] == "C")
        {
            this->setSigla(campos[0]);
            if (siglasUtilizadas.find(campos[0]) != siglasUtilizadas.end())
            {
                throw Excecao("Código repetido para Veículo: " + campos[0] + ".");
            }
            this->setNome(campos[1]);
            this->setTipo(campos[2]);

            if (trim(campos[2]) != "P" && trim(campos[2]) != "C")
            {
                throw Excecao("Tipo de veículo desconhecido para " + campos[0] + ": " + campos[2] + ".");
            }

            campos[3] = trocarVirgulaPorPonto(campos[3]);
            this->setFatorDeImpacto(stof(campos[3]));
            this->setIssn("");
            this->publicacoes = vector<Publicacao>();
            siglasUtilizadas.insert(trim(campos[0]));
        }
        else
        {
            throw Excecao("Tipo de veículo desconhecido para veículo " + campos[0] + ": " + campos[2] + ".");
        }
    }
    catch (Excecao e)
    {
        throw e;
    }
}

void Veiculo::addPublicacao(Publicacao p)
{
    this->publicacoes.push_back(p);
}

string Veiculo::getSigla()
{
    return this->sigla;
}
string Veiculo::getNome()
{
    return this->nome;
}
string Veiculo::getTipo()
{
    return this->tipo;
}
float Veiculo::getFatorDeImpacto()
{
    return this->fatorDeImpacto;
}
string Veiculo::getIssn()
{
    return this->issn;
}
void Veiculo::setSigla(string s)
{
    this->sigla = s;
}
void Veiculo::setNome(string s)
{
    this->nome = s;
}
void Veiculo::setTipo(string s)
{
    this->tipo = s;
}
void Veiculo::setFatorDeImpacto(float d)
{
    this->fatorDeImpacto = d;
}
void Veiculo::setIssn(string s)
{
    this->issn = s;
}

ostream &operator<<(ostream &c, Veiculo &d)
{
    stringstream fatorImpactoAux;
    fatorImpactoAux << fixed << setprecision(3) << d.getFatorDeImpacto();
    string fatorImpacto = trocarPontoPorVirgula(fatorImpactoAux.str());

    c << d.getSigla() << " " << d.getNome() << " " << d.getTipo() << " " << fatorImpacto << " " << d.getIssn();
    return c;
}