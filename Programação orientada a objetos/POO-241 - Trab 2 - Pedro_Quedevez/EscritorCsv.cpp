#include <iostream>
#include <fstream>
#include "ItemEstPub.hpp"
#include "EscritorCsv.hpp"
#include "ItemListaPublicacoes.hpp"

void EscritorCsv::escreveItemEstPub(vector<ItemEstPub> listaEstats, string nomeArquivo)
{
    ofstream arquivo;
    arquivo.open(nomeArquivo);
    if (listaEstats.size() != 0)
    {
        arquivo << "Qualis;Qtd. Artigos;Média Artigos / Docente\n";
        for (ItemEstPub item : listaEstats)
        {
            arquivo << item << endl;
        }
    }
    arquivo.close();
}

void EscritorCsv::escreveItemListaPublicacoes(vector<ItemListaPublicacoes> listaPublicacoes, string nomeArquivo)
{
    ofstream arquivo;
    arquivo.open(nomeArquivo);
    if (listaPublicacoes.size() != 0)
    {
        arquivo << "Ano;Sigla Veículo;Veículo;Qualis;Fator de Impacto;Título;Docentes\n";
        for (ItemListaPublicacoes item : listaPublicacoes)
        {
            arquivo << item << endl;
        }
    }

    arquivo.close();
}

void EscritorCsv::escreveRecredenciamento(vector<Recredenciamento> recredenciamentos, string nomeArquivo)
{
    ofstream arquivo;
    arquivo.open(nomeArquivo);
    if (recredenciamentos.size() != 0)
    {
        arquivo << "Docente;Pontuação;Recredenciado?\n";
        for (Recredenciamento r : recredenciamentos)
        {
            arquivo << r << endl;
        }
    }
    arquivo.close();
}