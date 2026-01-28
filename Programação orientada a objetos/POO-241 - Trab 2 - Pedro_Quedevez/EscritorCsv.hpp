#ifndef ESCRITORCSV_HPP
#define ESCRITORCSV_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Docente.hpp"
#include "Ocorrencia.hpp"
#include "Publicacao.hpp"
#include "Qualis.hpp"
#include "Veiculo.hpp"
#include "Recredenciamento.hpp"

class ItemListaPublicacoes;
class ItemEstPub;

class EscritorCsv
{
public:
    static void escreveItemEstPub(vector<ItemEstPub> listaEstats, string nomeArquivo);
    static void escreveItemListaPublicacoes(vector<ItemListaPublicacoes> listaPublicacoes, string nomeArquivo);
    static void escreveRecredenciamento(vector<Recredenciamento> recredenciamentos, string nomeArquivo);
};

#endif