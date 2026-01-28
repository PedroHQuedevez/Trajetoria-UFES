
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "StringUtils.hpp"
#include "Docente.hpp"
#include "Tokenizer.hpp"
#include "DateUtils.hpp"
#include "Excecao.hpp"

using namespace cpp_util;
using namespace std;

Docente::Docente(string csvline)
{
    Tokenizer tokens(csvline, ';');
    vector<string> campos = tokens.remaining();

    for (int i = 0; i < campos.size(); i++)
    {
        campos[i] = trim(campos[i]);
    }

    try
    {

        if (codigosUtilizados.find(trim(campos[0])) != codigosUtilizados.end())
        {
            throw Excecao("Código repetido para docente: " + campos[0] + ".");
        }
        this->setCodigo(trim(campos[0]));
        this->setNome(trim(campos[1]));

        Tokenizer tokens(campos[2], '/');
        vector<string> dataNascimento = tokens.remaining();
        this->setAnoNascimento(stoi(dataNascimento[2]));

        Tokenizer tokens2(campos[3], '/');
        vector<string> dataIngresso = tokens2.remaining();
        this->setAnoIngresso(stoi(dataIngresso[2]));

        this->setDataNascimento(campos[2]);
        this->setDataIngresso(campos[3]);

        this->ocorrencias = vector<Ocorrencia>();
        this->publicacoes = vector<Publicacao>();

        codigosUtilizados.insert(trim(campos[0]));
    }

    catch (Excecao &e)
    {
        throw e;
    }
}

int Docente::idadeDocente(int anoAtual)
{
    int diferencaAnos = anoAtual - this->getAnoNascimento();

    return (diferencaAnos - 1);
}

int Docente::tempoIngresso(int anoAtual)
{

    int diferencaAnos = anoAtual - this->getAnoIngresso();

    return diferencaAnos;
}

void Docente::addOcorrencia(Ocorrencia o)
{
    this->ocorrencias.push_back(o);
}

void Docente::addPublicacao(Publicacao p)
{
    this->publicacoes.push_back(p);
}
string Docente::getCodigo()
{
    return this->codigo;
}
string Docente::getNome()
{
    return this->nome;
}
void Docente::setCodigo(string s)
{
    this->codigo = s;
}
void Docente::setNome(string s)
{
    this->nome = s;
}
time_t Docente::getDataNascimento()
{
    return this->dataNascimento;
}
time_t Docente::getDataIngresso()
{
    return this->dataIngresso;
}
void Docente::setDataNascimento(time_t t)
{
    this->dataNascimento = t;
}
void Docente::setDataIngresso(time_t t)
{
    this->dataIngresso = t;
}

void Docente::setAnoNascimento(int ano)
{
    this->anoNascimento = ano;
}

int Docente::getAnoNascimento()
{
    return this->anoNascimento;
}

void Docente::setAnoIngresso(int ano)
{
    this->anoIngresso = ano;
}

int Docente::getAnoIngresso()
{
    return this->anoIngresso;
}

void Docente::setDataNascimento(string s)
{
    this->dataNascimento = cpp_util::parseDate(trim(s), cpp_util::DATE_FORMAT_PT_BR_SHORT);
}
void Docente::setDataIngresso(string s)
{
    this->dataIngresso = cpp_util::parseDate(trim(s), cpp_util::DATE_FORMAT_PT_BR_SHORT);
}

vector<Ocorrencia> Docente::getOcorrencias()
{
    return this->ocorrencias;
}

vector<Publicacao> Docente::getPublicacoes()
{
    return this->publicacoes;
}

ostream &operator<<(ostream &c, Docente &d)
{
    c << d.getCodigo() << " " << d.getNome() << " " << cpp_util::formatDate(d.getDataNascimento(), cpp_util::DATE_FORMAT_PT_BR_SHORT) << " " << cpp_util::formatDate(d.getDataIngresso(), cpp_util::DATE_FORMAT_PT_BR_SHORT);
    return c;
}
