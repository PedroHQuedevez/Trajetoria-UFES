#include <iostream>
#include <string>
#include <vector>
#include "Publicacao.hpp"

using namespace std;

class ItemEstPub
{
private:
    string qualis;
    float numArtigos;
    float numArtigosPorDocente;

public:
    ItemEstPub(string qualis, float numArtigos, float numArtigosPorDocente);
    void setQualis(string qualis);
    void setNumArtigos(float numArtigos);
    void setNumArtigosPorDocente(float numArtigosPorDocente);
    string getQualis();
    float getNumArtigos();
    float getNumArtigosPorDocente();
    static vector<ItemEstPub> criaListaEstats(vector<Publicacao> publicacoes);
};

ostream &operator<<(ostream &c, ItemEstPub &i);
