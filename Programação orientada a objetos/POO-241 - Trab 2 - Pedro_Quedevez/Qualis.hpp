#ifndef QUALIS_HPP
#define QUALIS_HPP

#include <string>
#include <ctime>

using namespace std;

class Qualis
{
private:
    int ano;
    string siglaVeiculo;
    string qualis;

public:
    Qualis(string csvline);
    int getAno();
    string getSiglaVeiculo();
    string getQualis();
    void setAno(int);
    void setSiglaVeiculo(string);
    void setQualis(string);
};

ostream &operator<<(ostream &c, Qualis &d);

#endif