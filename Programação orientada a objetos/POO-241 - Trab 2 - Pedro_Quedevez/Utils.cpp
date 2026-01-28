#include <iostream>
#include <vector>
#include "StringUtils.hpp"
#include "Tokenizer.hpp"
#include "Utils.hpp"

using namespace std;
using namespace cpp_util;

void Utils::vinculaOcorrenciasDocentes(vector<Docente> &docentes, vector<Ocorrencia> &ocorrencias)
{
    for (Docente &docente : docentes)
    {
        for (Ocorrencia &ocorrencia : ocorrencias)
        {
            if (docente.getCodigo() == ocorrencia.getCodigo())
            {
                docente.addOcorrencia(ocorrencia);
            }
        }
    }
}

void Utils::vinculaPublicacaoDocentes(vector<Docente> &docentes, vector<Publicacao> &publicacoes)
{

    for (Publicacao &publicacao : publicacoes)
    {
        Tokenizer tokens(publicacao.getAutores(), ',');
        vector<string> autores = tokens.remaining();
        for (string &autor : autores)
        {
            for (Docente &docente : docentes)
            {
                if (docente.getCodigo() == autor)
                {
                    docente.addPublicacao(publicacao);
                    break;
                }
            }
        }
    }
}

void Utils::vinculaQualisPublicacoes(vector<Publicacao> &publicacoes, vector<Qualis> &qualis)
{
    for (Publicacao &publicacao : publicacoes)
    {
        for (Qualis &q : qualis)
        {
            if (publicacao.getSiglaVeiculo() == q.getSiglaVeiculo())
            {
                publicacao.setQuali(q.getQualis());
            }
        }
    }
}

void Utils::vinculaVeiculaPublicacao(vector<Publicacao> &publicacoes, vector<Veiculo> &veiculos)
{
    for (Publicacao &publicacao : publicacoes)
    {
        for (Veiculo &veiculo : veiculos)
        {
            if (publicacao.getSiglaVeiculo() == veiculo.getSigla())
            {
                // veiculo.addPublicacao(publicacao);
                publicacao.setVeiculo(veiculo);
            }
        }
    }
}
