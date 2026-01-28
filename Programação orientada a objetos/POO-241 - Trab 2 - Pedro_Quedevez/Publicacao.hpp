#ifndef PUBLICACAO_HPP
#define PUBLICACAO_HPP

#include <string>
#include <ctime>
#include <vector>
#include "Veiculo.hpp"
#include "Global.hpp"

using namespace std;

class Publicacao
{
private:
    int ano;
    string siglaVeiculo;
    string titulo;
    string autores;
    int numero;
    int volume;
    string localConferecia;
    int paginaInicial;
    int paginaFinal;
    string quali;
    Veiculo V;

public:
    Publicacao(string csvline);
    int getAno();
    string getSiglaVeiculo();
    string getTitulo();
    string getAutores();
    int getNumero();
    int getVolume();
    string getLocalConferecia();
    int getPaginaInicial();
    int getPaginaFinal();
    string getQuali();
    void setAno(int);
    void setSiglaVeiculo(string);
    void setTitulo(string);
    void setAutores(string);
    void setNumero(int);
    void setVolume(int);
    void setLocalConferecia(string);
    void setPaginaInicial(int);
    void setPaginaFinal(int);
    void setQuali(string);
    void setVeiculo(Veiculo v);
    Veiculo getVeiculo();
};

ostream &operator<<(ostream &c, Publicacao &d);

#endif