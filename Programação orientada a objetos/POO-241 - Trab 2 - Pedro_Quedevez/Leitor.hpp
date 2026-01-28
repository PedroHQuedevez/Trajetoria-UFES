#ifndef LEITOR_HPP
#define LEITOR_HPP

#include <vector>
#include <string>
#include "Docente.hpp"
#include "Ocorrencia.hpp"
#include "Publicacao.hpp"
#include "Qualis.hpp"
#include "Veiculo.hpp"
#include "Regras.hpp"

class Leitor
{
private:
public:
    static vector<Docente> lerArquivoDocentes(string nomeArquivo);
    static vector<Ocorrencia> lerArquivoOcorrencia(string nomeArquivo);
    static vector<Publicacao> lerArquivoPublicacao(string nomeArquivo);
    static vector<Qualis> lerArquivoQualis(string nomeArquivo);
    static vector<Veiculo> lerArquivoVeiculo(string nomeArquivo);
    static vector<Regras> lerArquivoRegras(string nomeArquivo);
};

#endif