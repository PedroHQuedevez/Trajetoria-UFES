#ifndef DOCENTE_HPP
#define DOCENTE_HPP

#include <string>
#include <ctime>
#include <vector>
#include <unordered_set>
#include "Ocorrencia.hpp"
#include "Publicacao.hpp"
#include "Global.hpp"

using namespace std;

class Docente
{
private:
    string codigo;
    string nome;
    int anoNascimento;
    int anoIngresso;
    time_t dataNascimento;
    time_t dataIngresso;
    vector<Ocorrencia> ocorrencias;
    vector<Publicacao> publicacoes;

public:
    Docente(string csvline);
    string getCodigo();
    string getNome();
    void setCodigo(string);
    void setNome(string);
    time_t getDataNascimento();
    time_t getDataIngresso();
    void setDataNascimento(time_t);
    void setDataIngresso(time_t);
    void setDataNascimento(string);
    void setDataIngresso(string);
    void setAnoNascimento(int);
    void setAnoIngresso(int);
    int getAnoNascimento();
    int getAnoIngresso();
    vector<Ocorrencia> getOcorrencias();
    void addOcorrencia(Ocorrencia);
    vector<Publicacao> getPublicacoes();
    void addPublicacao(Publicacao);
    int idadeDocente(int anoAtual);
    int tempoIngresso(int anoAtual);
};

ostream &operator<<(ostream &c, Docente &d);

#endif