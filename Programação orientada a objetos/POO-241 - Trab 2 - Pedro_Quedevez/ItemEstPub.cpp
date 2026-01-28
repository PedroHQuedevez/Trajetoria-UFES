#include <iomanip>
#include "StringUtils.hpp"
#include "ItemEstPub.hpp"
#include "Tokenizer.hpp"

using namespace cpp_util;

ItemEstPub::ItemEstPub(string qualis, float numArtigos, float numArtigosPorDocente)
{
    this->qualis = qualis;
    this->numArtigos = numArtigos;
    this->numArtigosPorDocente = numArtigosPorDocente;
}

vector<ItemEstPub> ItemEstPub::criaListaEstats(vector<Publicacao> publicacoes)
{
    vector<ItemEstPub> lista;

    vector<string> qualis = {"A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "B5", "C"};
    vector<float> numArtigos(qualis.size(), 0.0f);
    vector<float> numAutores(qualis.size(), 0.0f);

    for (size_t i = 0; i < qualis.size(); i++)
    {
        for (Publicacao p : publicacoes)
        {
            if (p.getQuali() == qualis[i])
            {
                numArtigos[i]++;
                Tokenizer splitAutores(p.getAutores(), ',');
                vector<string> autores = splitAutores.remaining();
                float numAutoresTemp = autores.size();
                if (numAutoresTemp != 0)
                {
                    numAutores[i] += (1 / numAutoresTemp);
                }
            }
        }
        lista.push_back(ItemEstPub(qualis[i], numArtigos[i], numAutores[i]));
    }

    return lista;
}

void ItemEstPub::setQualis(string qualis)
{
    this->qualis = qualis;
}

void ItemEstPub::setNumArtigos(float numArtigos)
{
    this->numArtigos = numArtigos;
}

void ItemEstPub::setNumArtigosPorDocente(float numArtigosPorDocente)
{
    this->numArtigosPorDocente = numArtigosPorDocente;
}

string ItemEstPub::getQualis()
{
    return this->qualis;
}

float ItemEstPub::getNumArtigos()
{
    return this->numArtigos;
}

float ItemEstPub::getNumArtigosPorDocente()
{
    return this->numArtigosPorDocente;
}

ostream &operator<<(ostream &c, ItemEstPub &i)
{
    float numArtigosPorDocente = i.getNumArtigosPorDocente();

    stringstream NumArtigosPorDocenteAux;
    NumArtigosPorDocenteAux << fixed << setprecision(2) << numArtigosPorDocente;
    string NumArtigosPorDocenteString = trocarPontoPorVirgula(NumArtigosPorDocenteAux.str());

    c << i.getQualis() << ";" << fixed << setprecision(0) << i.getNumArtigos() << ";" << NumArtigosPorDocenteString;
    return c;
}
