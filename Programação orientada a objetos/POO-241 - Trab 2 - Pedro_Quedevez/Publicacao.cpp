
#include <iostream>
#include <string>
#include <vector>
#include "StringUtils.hpp"
#include "Tokenizer.hpp"
#include "Publicacao.hpp"
#include "Veiculo.hpp"
#include "Excecao.hpp"
#include "Docente.hpp"

using namespace cpp_util;
using namespace std;

Publicacao::Publicacao(string csvLine)
{

    Tokenizer tokens(csvLine, ';');
    vector<string> campos = tokens.remaining();

    try
    {

        for (int i = 0; i < campos.size(); i++)
        {
            campos[i] = trim(campos[i]);
        }

        this->setAno(stoi(campos[0]));
        if (siglasUtilizadas.find(trim(campos[1])) == siglasUtilizadas.end())
        {
            throw Excecao("Sigla de veículo não definida usada na publicação \"" + campos[2] + "\": " + campos[1] + ".");
        }
        this->setSiglaVeiculo(campos[1]);
        this->setTitulo(campos[2]);
        this->setAutores(campos[3]);

        Tokenizer autores(campos[3], ',');
        vector<string> autoresSeparados = autores.remaining();
        for (int i = 0; i < autoresSeparados.size(); i++)
        {
            if (codigosUtilizados.find(trim(autoresSeparados[i])) == codigosUtilizados.end())
            {
                throw Excecao("Código de docente não definido usado na publicação \"" + campos[2] + "\": " + autoresSeparados[i] + ".");
            }
        }

        this->setNumero(stoi(campos[4]));
        if (campos[5] == "")
        {
            campos[5] = "0";
        }
        this->setVolume(stoi(campos[5]));
        this->setLocalConferecia(campos[6]);
        this->setPaginaInicial(stoi(campos[7]));
        this->setPaginaFinal(stoi(campos[8]));
        this->setQuali("");
    }
    catch (Excecao e)
    {
        throw e;
    }
}

int Publicacao::getAno()
{
    return this->ano;
}
string Publicacao::getSiglaVeiculo()
{
    return this->siglaVeiculo;
}
string Publicacao::getTitulo()
{
    return this->titulo;
}
string Publicacao::getAutores()
{
    return this->autores;
}
int Publicacao::getNumero()
{
    return this->numero;
}
int Publicacao::getVolume()
{
    return this->volume;
}
string Publicacao::getLocalConferecia()
{
    return this->localConferecia;
}
int Publicacao::getPaginaInicial()
{
    return this->paginaInicial;
}
int Publicacao::getPaginaFinal()
{
    return this->paginaFinal;
}
string Publicacao::getQuali()
{
    return this->quali;
}

Veiculo Publicacao::getVeiculo()
{
    return this->V;
}

void Publicacao::setVeiculo(Veiculo v)
{

    this->V = v;
}

void Publicacao::setAno(int i)
{
    this->ano = i;
}
void Publicacao::setSiglaVeiculo(string s)
{
    this->siglaVeiculo = s;
}
void Publicacao::setTitulo(string s)
{
    this->titulo = s;
}
void Publicacao::setAutores(string v)
{
    this->autores = v;
}
void Publicacao::setNumero(int i)
{
    this->numero = i;
}
void Publicacao::setVolume(int i)
{
    this->volume = i;
}
void Publicacao::setLocalConferecia(string s)
{
    this->localConferecia = s;
}
void Publicacao::setPaginaInicial(int i)
{
    this->paginaInicial = i;
}
void Publicacao::setPaginaFinal(int i)
{
    this->paginaFinal = i;
}
void Publicacao::setQuali(string s)
{
    this->quali = s;
}

ostream &operator<<(ostream &c, Publicacao &d)
{
    c << d.getAno() << " " << d.getSiglaVeiculo() << " " << d.getTitulo() << " " << d.getAutores() << " " << d.getNumero() << " " << d.getVolume() << " " << d.getLocalConferecia() << " " << d.getPaginaInicial() << " " << d.getPaginaFinal() << " " << d.getQuali();
    return c;
}