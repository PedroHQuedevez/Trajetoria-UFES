#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Ocorrencia.hpp"
#include "Leitor.hpp"
#include "Docente.hpp"
#include "Publicacao.hpp"

using namespace std;

vector<Docente> Leitor::lerArquivoDocentes(string nomeArquivo)
{

    vector<Docente> docentes;
    ifstream arquivo(nomeArquivo);
    string linha;
    getline(arquivo, linha);
    while (getline(arquivo, linha))
    {
        Docente docente(linha);
        docentes.push_back(docente);
    }
    arquivo.close();
    return docentes;
};

vector<Ocorrencia> Leitor::lerArquivoOcorrencia(string nomeArquivo)
{
    vector<Ocorrencia> ocorrencias;
    ifstream arquivo(nomeArquivo);
    string linha;
    getline(arquivo, linha);
    while (getline(arquivo, linha))
    {
        Ocorrencia ocorrencia(linha);
        ocorrencias.push_back(ocorrencia);
    }
    arquivo.close();
    return ocorrencias;
};

vector<Publicacao> Leitor::lerArquivoPublicacao(string nomeArquivo)
{
    vector<Publicacao> publicacoes;
    ifstream arquivo(nomeArquivo);
    string linha;
    getline(arquivo, linha);
    while (getline(arquivo, linha))
    {
        Publicacao publicacao(linha);
        publicacoes.push_back(publicacao);
    }
    arquivo.close();
    return publicacoes;
};

vector<Qualis> Leitor::lerArquivoQualis(string nomeArquivo)
{
    vector<Qualis> qualis;
    ifstream arquivo(nomeArquivo);
    string linha;
    getline(arquivo, linha);
    while (getline(arquivo, linha))
    {
        Qualis q(linha);
        qualis.push_back(q);
    }
    arquivo.close();
    return qualis;
};

vector<Veiculo> Leitor::lerArquivoVeiculo(string nomeArquivo)
{
    vector<Veiculo> veiculos;
    ifstream arquivo(nomeArquivo);
    string linha;
    getline(arquivo, linha);
    while (getline(arquivo, linha))
    {
        Veiculo v(linha);
        veiculos.push_back(v);
    }
    arquivo.close();
    return veiculos;
};

vector<Regras> Leitor::lerArquivoRegras(string nomeArquivo)
{
    vector<Regras> regras;
    ifstream arquivo(nomeArquivo);
    string linha;
    getline(arquivo, linha);
    while (getline(arquivo, linha))
    {
        Regras r(linha);
        regras.push_back(r);
    }
    arquivo.close();
    return regras;
};