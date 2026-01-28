#ifndef OCORRENCIA_HPP
#define OCORRENCIA_HPP

#include <string>
#include <ctime>
#include "Global.hpp"

using namespace std;

class Ocorrencia
{
private:
    string codigo;
    string evento;
    time_t dataInicio;
    time_t dataFim;

public:
    Ocorrencia(string csvline);
    string getCodigo();
    string getEvento();
    time_t getDataInicio();
    time_t getDataFim();
    void setCodigo(string);
    void setEvento(string);
    void setDataInicio(time_t);
    void setDataFim(time_t);
    void setDataInicio(string);
    void setDataFim(string);
};

ostream &operator<<(ostream &c, Ocorrencia &o);
#endif