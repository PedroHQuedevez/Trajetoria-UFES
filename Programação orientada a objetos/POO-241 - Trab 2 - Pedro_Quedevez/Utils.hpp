#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include "Docente.hpp"
#include "Ocorrencia.hpp"
#include "Publicacao.hpp"
#include "Qualis.hpp"
#include "Veiculo.hpp"

using namespace std;

class Utils
{
private:
public:
    static void vinculaOcorrenciasDocentes(vector<Docente> &docentes, vector<Ocorrencia> &ocorrencias);
    static void vinculaPublicacaoDocentes(vector<Docente> &docentes, vector<Publicacao> &publicacoes);
    static void vinculaQualisPublicacoes(vector<Publicacao> &publicacoes, vector<Qualis> &qualis);
    static void vinculaVeiculaPublicacao(vector<Publicacao> &publicacoes, vector<Veiculo> &veiculos);
};

#endif