#ifndef ITEMLISTAPUBLICACOES_HPP
#define ITEMLISTAPUBLICACOES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Publicacao.hpp"
#include "Docente.hpp"

using namespace std;

extern unordered_map<string, int> ordemQualisMap;

class ItemListaPublicacoes
{
private:
    int ano;
    string siglaVeiculo;
    string nomeVeiculo;
    string qualis;
    float fatorImpacto;
    string tituloPublicacao;
    vector<string> nomesDocentes;

public:
    ItemListaPublicacoes(Publicacao p, vector<Docente> docentes, vector<Veiculo> veiculos);
    int getAno();
    string getSiglaVeiculo();
    string getNomeVeiculo();
    string getQualis();
    float getFatorImpacto();
    string getTituloPublicacao();
    vector<string> getNomesDocentes();
    static vector<ItemListaPublicacoes> OrdenaListaPublicacoes(vector<ItemListaPublicacoes> lista);
};

ostream &operator<<(ostream &c, ItemListaPublicacoes &d);

#endif