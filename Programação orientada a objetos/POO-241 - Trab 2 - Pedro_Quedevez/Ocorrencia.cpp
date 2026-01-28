#include <iostream>
#include <string>
#include <vector>
#include "StringUtils.hpp"
#include "Ocorrencia.hpp"
#include "Tokenizer.hpp"
#include "DateUtils.hpp"
#include "Excecao.hpp"

using namespace cpp_util;
using namespace std;

Ocorrencia::Ocorrencia(string csvline)
{
    Tokenizer tokens(csvline, ';');
    vector<string> campos = tokens.remaining();

    for (int i = 0; i < campos.size(); i++)
    {
        campos[i] = trim(campos[i]);
    }

    try
    {

        if (codigosUtilizados.find(campos[0]) == codigosUtilizados.end())
        {
            throw Excecao("Código de docente não definido usado na ocorrência: " + campos[0] + ":" + campos[1] + ".");
        }
        this->setCodigo(campos[0]);
        this->setEvento(campos[1]);
        this->setDataInicio(campos[2]);
        this->setDataFim(campos[3]);
    }
    catch (Excecao e)
    {
        throw e;
    }
}

string Ocorrencia::getCodigo()
{
    return this->codigo;
}

string Ocorrencia::getEvento()
{
    return this->evento;
}

time_t Ocorrencia::getDataInicio()
{
    return this->dataInicio;
}

time_t Ocorrencia::getDataFim()
{
    return this->dataFim;
}

void Ocorrencia::setCodigo(string s)
{
    this->codigo = s;
}

void Ocorrencia::setEvento(string s)
{
    this->evento = s;
}

void Ocorrencia::setDataInicio(time_t t)
{
    this->dataInicio = t;
}

void Ocorrencia::setDataFim(time_t t)
{
    this->dataFim = t;
}

void Ocorrencia::setDataInicio(string s)
{
    this->dataInicio = cpp_util::parseDate(trim(s), cpp_util::DATE_FORMAT_PT_BR_SHORT);
}

void Ocorrencia::setDataFim(string s)
{
    this->dataFim = cpp_util::parseDate(trim(s), cpp_util::DATE_FORMAT_PT_BR_SHORT);
}

ostream &operator<<(ostream &c, Ocorrencia &o)
{
    c << o.getCodigo() << " " << o.getEvento() << " " << cpp_util::formatDate(o.getDataInicio(), cpp_util::DATE_FORMAT_PT_BR_SHORT) << " " << cpp_util::formatDate(o.getDataFim(), cpp_util::DATE_FORMAT_PT_BR_SHORT);
    return c;
}
