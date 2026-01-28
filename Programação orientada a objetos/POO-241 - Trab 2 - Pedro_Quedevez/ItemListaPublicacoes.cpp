/*<ano>;<sigla veículo>;<nome veículo>;<Qualis>;<fator de impacto>;<título da
publicação>;<nomes dos docentes>
Este relatório deve ser ordenado por Qualis, em ordem decrescente (A1 primeiro), seguido por
ano (decrescente) por sigla do veículo (crescente) e, por fim, pelo título da publicação (crescente).
O fator de impacto deve ser formatado com 3 casas decimais e o nome dos docentes deve estar
separado por vírgulas. Note que este relatório considera todas as publicações informadas e não
apenas uma quantidade de anos, como no caso do recredenciamento.*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include "Tokenizer.hpp"
#include "Publicacao.hpp"
#include "Docente.hpp"
#include "ItemListaPublicacoes.hpp"
#include "Veiculo.hpp"
#include "StringUtils.hpp"

using namespace std;
using namespace cpp_util;

unordered_map<string, int> ordemQualisMap = {
    {"A1", 0},
    {"A2", 1},
    {"A3", 2},
    {"A4", 3},
    {"B1", 4},
    {"B2", 5},
    {"B3", 6},
    {"B4", 7},
    {"B5", 8},
    {"C", 9}};

int getOrdemQualis(const std::string &qualis)
{
    return ordemQualisMap[qualis];
}

ItemListaPublicacoes::ItemListaPublicacoes(Publicacao p, vector<Docente> docentes, vector<Veiculo> veiculos)
{
    this->ano = p.getAno();
    this->siglaVeiculo = p.getSiglaVeiculo();
    this->qualis = p.getQuali();
    Veiculo v = p.getVeiculo();
    this->fatorImpacto = v.getFatorDeImpacto();
    this->tituloPublicacao = p.getTitulo();

    Tokenizer tokens(p.getAutores(), ',');
    vector<string> autores = tokens.remaining();

    for (Veiculo veiculo : veiculos)
    {
        string siglap = p.getSiglaVeiculo();
        string siglav = veiculo.getSigla();
        if (trim(siglav) == trim(siglap))
        {
            this->nomeVeiculo = veiculo.getNome();
        }
    }

    for (string autor : autores)
    {
        for (Docente d : docentes)
        {
            string codigo = d.getCodigo();
            if (trim(codigo) == trim(autor))
            {
                this->nomesDocentes.push_back(d.getNome());
            }
        }
    }
}

int ItemListaPublicacoes::getAno()
{
    return this->ano;
}
string ItemListaPublicacoes::getSiglaVeiculo()
{
    return this->siglaVeiculo;
}
string ItemListaPublicacoes::getNomeVeiculo()
{
    return this->nomeVeiculo;
}
string ItemListaPublicacoes::getQualis()
{
    return this->qualis;
}
float ItemListaPublicacoes::getFatorImpacto()
{
    return this->fatorImpacto;
}
string ItemListaPublicacoes::getTituloPublicacao()
{
    return this->tituloPublicacao;
}
vector<string> ItemListaPublicacoes::getNomesDocentes()
{
    return this->nomesDocentes;
}

vector<ItemListaPublicacoes> ItemListaPublicacoes::OrdenaListaPublicacoes(vector<ItemListaPublicacoes> lista)
{

    for (int i = 0; i < lista.size(); i++)
    {
        for (int j = i + 1; j < lista.size(); j++)
        {
            if (getOrdemQualis(lista[i].getQualis()) > getOrdemQualis(lista[j].getQualis()))
            {
                ItemListaPublicacoes aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }

            if (getOrdemQualis(lista[i].getQualis()) == getOrdemQualis(lista[j].getQualis()))
            {
                if (lista[i].getAno() < lista[j].getAno())
                {
                    ItemListaPublicacoes aux = lista[i];
                    lista[i] = lista[j];
                    lista[j] = aux;
                }

                if (lista[i].getAno() == lista[j].getAno())
                {
                    if (lista[i].getSiglaVeiculo() > lista[j].getSiglaVeiculo())
                    {
                        ItemListaPublicacoes aux = lista[i];
                        lista[i] = lista[j];
                        lista[j] = aux;
                    }

                    if (lista[i].getSiglaVeiculo() == lista[j].getSiglaVeiculo())
                    {
                        if (lista[i].getTituloPublicacao() > lista[j].getTituloPublicacao())
                        {
                            ItemListaPublicacoes aux = lista[i];
                            lista[i] = lista[j];
                            lista[j] = aux;
                        }
                    }
                }
            }
        }
    }
    return lista;
}

string montaStringNomesDocentes(vector<string> nomesDocentes)
{
    string nomes = "";
    for (int i = 0; i < nomesDocentes.size(); i++)
    {
        nomes += nomesDocentes[i];
        if (i != nomesDocentes.size() - 1)
        {
            nomes += ",";
        }
    }
    return nomes;
}

ostream &operator<<(ostream &c, ItemListaPublicacoes &d)
{
    stringstream fatorImpactoAux;
    fatorImpactoAux << fixed << setprecision(3) << d.getFatorImpacto();
    string fatorImpacto = trocarPontoPorVirgula(fatorImpactoAux.str());

    c << d.getAno() << ";"
      << d.getSiglaVeiculo() << ";"
      << d.getNomeVeiculo() << ";"
      << d.getQualis() << ";"
      << fatorImpacto << ";"
      << d.getTituloPublicacao() << ";" << montaStringNomesDocentes(d.getNomesDocentes());
    return c;
}
