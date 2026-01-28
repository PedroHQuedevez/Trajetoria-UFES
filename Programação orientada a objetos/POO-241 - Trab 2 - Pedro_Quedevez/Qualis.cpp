#include <iostream>
#include <string>
#include <vector>
#include "StringUtils.hpp"
#include "Qualis.hpp"
#include "Tokenizer.hpp"
#include "DateUtils.hpp"
#include "Excecao.hpp"
#include "Global.hpp"
#include "ItemListaPublicacoes.hpp"

using namespace cpp_util;
using namespace std;

Qualis::Qualis(string csvline)
{
    Tokenizer tokens(csvline, ';');
    vector<string> campos = tokens.remaining();

    for (int i = 0; i < campos.size(); i++)
    {
        campos[i] = trim(campos[i]);
    }

    try
    {

        this->setAno(stoi(campos[0]));
        if (siglasUtilizadas.find(campos[1]) == siglasUtilizadas.end())
        {
            throw Excecao("Sigla de veículo não definida usada na qualificação do ano \"" + campos[0] + "\": " + campos[1] + ".");
        }
        this->setSiglaVeiculo(campos[1]);
        if (ordemQualisMap.find(campos[2]) == ordemQualisMap.end())
        {
            throw Excecao("Qualis desconhecido para qualificação do veículo " + campos[1] + " no ano " + campos[0] + ": " + campos[2] + ".");
        }
        this->setQualis(campos[2]);
    }
    catch (Excecao e)
    {
        throw e;
    }
}

int Qualis::getAno()
{
    return this->ano;
}
string Qualis::getSiglaVeiculo()
{
    return this->siglaVeiculo;
}
string Qualis::getQualis()
{
    return this->qualis;
}
void Qualis::setAno(int i)
{
    this->ano = i;
}
void Qualis::setSiglaVeiculo(string s)
{
    this->siglaVeiculo = s;
}
void Qualis::setQualis(string s)
{
    this->qualis = s;
}

ostream &operator<<(ostream &c, Qualis &d)
{
    c << d.getAno() << " " << d.getSiglaVeiculo() << " " << d.getQualis();
    return c;
}