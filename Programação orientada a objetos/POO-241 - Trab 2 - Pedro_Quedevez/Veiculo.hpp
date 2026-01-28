#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>
#include <ctime>
#include <vector>
#include <unordered_set>
#include "Global.hpp"

using namespace std;

class Publicacao; // Solução da dependência circular;

class Veiculo
{
private:
    string sigla;
    string nome;
    string tipo;
    float fatorDeImpacto;
    string issn;
    vector<Publicacao> publicacoes;

public:
    Veiculo();
    Veiculo(string csvline);
    string getSigla();
    string getNome();
    string getTipo();
    float getFatorDeImpacto();
    string getIssn();
    void setSigla(string);
    void setNome(string);
    void setTipo(string);
    void setFatorDeImpacto(float);
    void setIssn(string);
    vector<Publicacao> getPublicacoes();
    void addPublicacao(Publicacao p);
};

ostream &operator<<(ostream &c, Veiculo &d);

#endif