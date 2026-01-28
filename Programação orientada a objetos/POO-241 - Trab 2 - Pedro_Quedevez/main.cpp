#include <iostream>
#include <vector>
#include <string>
#include <locale.h>
#include "Leitor.hpp"
#include "Docente.hpp"
#include "Ocorrencia.hpp"
#include "Publicacao.hpp"
#include "Qualis.hpp"
#include "Veiculo.hpp"
#include "Regras.hpp"
#include "Utils.hpp"
#include "ItemListaPublicacoes.hpp"
#include "ItemEstPub.hpp"
#include "Recredenciamento.hpp"
#include "EscritorCsv.hpp"
#include "Excecao.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string caminho = argv[1];

    vector<ItemListaPublicacoes> listaPublicacoes;
    vector<ItemEstPub> listaEstats;
    vector<Recredenciamento> listaRecredenciamento;

    EscritorCsv::escreveItemEstPub(listaEstats, caminho + "/saida/3-estatisticas.csv");
    EscritorCsv::escreveItemListaPublicacoes(listaPublicacoes, caminho + "/saida/2-publicacoes.csv");
    EscritorCsv::escreveRecredenciamento(listaRecredenciamento, caminho + "/saida/1-recredenciamento.csv");

    try
    {

        setlocale(LC_ALL, "Portuguese");

        int ano;

        scanf("\n%d", &ano);

        string nomeArquivo = caminho + "/regras.csv";
        vector<Regras> regras;
        regras = Leitor::lerArquivoRegras(nomeArquivo);

        nomeArquivo = caminho + "/docentes.csv";
        vector<Docente> docentes;
        docentes = Leitor::lerArquivoDocentes(nomeArquivo);

        nomeArquivo = caminho + "/veiculos.csv";
        vector<Veiculo> veiculos;
        veiculos = Leitor::lerArquivoVeiculo(nomeArquivo);

        nomeArquivo = caminho + "/qualis.csv";
        vector<Qualis> qualis;
        qualis = Leitor::lerArquivoQualis(nomeArquivo);

        nomeArquivo = caminho + "/ocorrencias.csv";
        vector<Ocorrencia> ocorrencias;
        ocorrencias = Leitor::lerArquivoOcorrencia(nomeArquivo);

        nomeArquivo = caminho + "/publicacoes.csv";
        vector<Publicacao> publicacoes;
        publicacoes = Leitor::lerArquivoPublicacao(nomeArquivo);

        Utils::vinculaVeiculaPublicacao(publicacoes, veiculos);
        Utils::vinculaQualisPublicacoes(publicacoes, qualis);
        Utils::vinculaOcorrenciasDocentes(docentes, ocorrencias);
        Utils::vinculaPublicacaoDocentes(docentes, publicacoes);

        for (Publicacao p : publicacoes)
        {
            ItemListaPublicacoes item(p, docentes, veiculos);
            listaPublicacoes.push_back(item);
        }

        listaPublicacoes = ItemListaPublicacoes::OrdenaListaPublicacoes(listaPublicacoes);
        listaEstats = ItemEstPub::criaListaEstats(publicacoes);

        listaRecredenciamento = Recredenciamento::constroiListaRecredenciamento(docentes, regras, ano);
        listaRecredenciamento = Recredenciamento::ordenaListaRecredenciamento(listaRecredenciamento);

        EscritorCsv::escreveItemEstPub(listaEstats, caminho + "/saida/3-estatisticas.csv");
        EscritorCsv::escreveItemListaPublicacoes(listaPublicacoes, caminho + "/saida/2-publicacoes.csv");
        EscritorCsv::escreveRecredenciamento(listaRecredenciamento, caminho + "/saida/1-recredenciamento.csv");
    }
    catch (Excecao &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}